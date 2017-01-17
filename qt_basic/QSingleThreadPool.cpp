#include <map>
#include <mutex>
#include <tuple>
#include <future>
#include <thread>
#include <shared_mutex>
#include <QtCore/QEvent>
#include <QtCore/qtimer.h>
#include <QtCore/qdebug.h>
#include <QtCore/qthread.h>
#include "cplusplus_basic.hpp"
#include <QtCore/qeventloop.h>
#include "QSingleThreadPool.hpp"
#include "QApplicationWatcher.hpp"
#include <QtCore/qcoreapplication.h>

//#define THREAD_DEBUG
#if defined(THREAD_DEBUG)
#include <QtCore/qdebug.h>
#endif

namespace qappwatcher {
extern std::shared_timed_mutex * getMutex();
}

namespace {
namespace _current_threads {

class Data {
public:
    std::shared_timed_mutex mutex;
    std::map<std::thread::id,std::weak_ptr<QSingleThreadPool>> threads;
private:
    CPLUSPLUS_OBJECT(Data)
};

Data * getData() {
    static Data * data_=new Data;
    return data_;
}

void add(std::thread::id a,std::weak_ptr<QSingleThreadPool> b) {
    auto data=getData();
    std::unique_lock<std::shared_timed_mutex> _lock_{ data->mutex };
    data->threads[a]=std::move(b);
}


void remove(std::thread::id a) {
    auto data=getData();
    std::unique_lock<std::shared_timed_mutex> _lock_{ data->mutex };
    data->threads.erase(a);
}

std::weak_ptr<QSingleThreadPool> find(std::thread::id a) {
    if (QObjectsWatcher::isQAppQuited()) { return{}; }
    auto data=getData();
    std::shared_lock<std::shared_timed_mutex> _lock_{ data->mutex };
    auto var=data->threads.find(a);
    if (var==data->threads.end()) { return{}; }
    return var->second;
}

}
}

namespace {

static auto eventType() {
    static auto ans=static_cast<QEvent::Type>(
                QEvent::registerEventType());
    return ans;
}

}/*namespace*/

QEvent::Type QSingleThreadPool::eventID() {
    return eventType();
}

namespace {

using _RunableEvent=QSingleThreadPool::RunableEvent;

class _ThreadObjectRunableEvent : public QObject {
public:

    bool event(QEvent *e) override {

        if (e->type()==eventType()) {
            static_cast<_RunableEvent *>(e)->run();
            return true;
        }

        return QObject::event(e);
    }

private:
    CPLUSPLUS_OBJECT(_RunableEvent)
};

using _p_thread_data_t=std::tuple<
    _ThreadObjectRunableEvent *,
    std::thread::id
>;

}/*namespace*/


class QSingleThreadPool::_Thread : public QThread {
public:
    std::promise<_p_thread_data_t> * promise_;

    _Thread(std::promise<_p_thread_data_t> *arg)
        :promise_(arg) {}

    void run() {
        try {
            _ThreadObjectRunableEvent _eventDispatcher;
#if defined(THREAD_DEBUG)
            qDebug()<<"create a thread"<<QThread::currentThread();
#endif
            /**/
            promise_->set_value(std::make_tuple(
                &_eventDispatcher,
                std::this_thread::get_id()));
            promise_=nullptr;
            /**/

            this->exec();
        }
        catch (...) {}

    }
private:
    CPLUSPLUS_OBJECT(_RunableEvent)
};


namespace {

std::atomic< QObject * > staticDelateLaterObject;

}/*namespace*/

namespace {

/*quit in the same thread*/
static void toQuitQThread(_ThreadObjectRunableEvent * obj,QThread *arg) {

    class Event :public _RunableEvent {
        void(*_fun)(_ThreadObjectRunableEvent *,QThread*);
        _ThreadObjectRunableEvent * _obj;
        QThread * _data;
    public:
        Event(void(*f)(_ThreadObjectRunableEvent *,QThread*),
              _ThreadObjectRunableEvent*a,QThread*d):
            _fun(f),
            _obj(a),
            _data(d) {
        }
        void do_run() override { _fun(_obj,_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };

    /*move to it's thread and quit it*/
    QCoreApplication::postEvent(
                obj,
                new Event([](_ThreadObjectRunableEvent * obj,QThread *arg) {
        assert(arg==QThread::currentThread());
        QTimer::singleShot(64,obj,
        [arg]() {
#if defined(THREAD_DEBUG)
            qDebug()<<"quit a thread"<<arg;
#endif
            arg->quit();
        });
    },obj,arg));

}

/*QThread delete before main may be a bug*/
static void toDeleteQThread(QThread *arg) {

    if (staticDelateLaterObject.load()==nullptr) {
        return arg->deleteLater();
    }

    class Event :public _RunableEvent {
        void(*_fun)(QThread*);
        QThread * _data;
    public:
        Event(void(*f)(QThread*),QThread*d):_fun(f),_data(d) {}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };

    /*move to main thread and delete it*/
    QCoreApplication::postEvent(
                staticDelateLaterObject.load(),
                new Event([](QThread *arg) {
        QTimer::singleShot(10,staticDelateLaterObject.load(),
        [arg]() {
#if defined(THREAD_DEBUG)
            qDebug()<<"destroy a thread"<<arg;
#endif
            delete arg;
        });
    },arg));

}

}/*namespace*/

QSingleThreadPool::QSingleThreadPool(const private_construct &) {

}

QSingleThreadPool::QSingleThreadPool(QObject *p):QObject(p) {
    watcher_=QObjectsWatcher::instance();

    std::promise<_p_thread_data_t> varPromise;
    auto varThread=new _Thread(&varPromise);

    connect(varThread,&QThread::finished,
            [varThread]() {toDeleteQThread(varThread); });

    varThread->start();

    /*get thread data*/
    auto varThreadData=varPromise.get_future().get();
    auto varObject=std::get<0>(varThreadData);
    auto varThreadID=std::get<1>(varThreadData);
    this->thread_object_=varObject;

    this->children_=memory::make_shared<QSingleThreadPool>(private_construct{});
    this->children_->watcher_=this->watcher_;
    this->children_->thread_object_=this->thread_object_;

    _current_threads::add(varThreadID,this->children_);

    connect(watcher_.get(),
            &QObjectsWatcher::finished,
            varThread,
            [varThread,varThreadID,varObject]() {
        /*删除观察者*/
        _current_threads::remove(varThreadID);
        /*延迟quit，以消除某些deleteLater的bug*/
        toQuitQThread(varObject,varThread);
    });

}

QSingleThreadPool::~QSingleThreadPool() {

}

void QSingleThreadPool::run(void(*f)(void),int p) {
    if (f==nullptr) { return; }
    class Event :public _RunableEvent {
        void(*_fun)(void);
    public:
        Event(void(*f)(void)):_fun(f) {}
        void do_run() override { _fun(); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    _p_run(new Event(f),p);
}

void QSingleThreadPool::run(void(*f)(void*),void *d,int p) {
    if (f==nullptr) { return; }
    class Event :public _RunableEvent {
        void(*_fun)(void*);
        void * _data;
    public:
        Event(void(*f)(void*),void*d):_fun(f),_data(d) {}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    _p_run(new Event(f,d),p);
}

void QSingleThreadPool::run(void(*f)(const void*),const void *d,int p) {
    if (f==nullptr) { return; }
    class Event :public _RunableEvent {
        void(*_fun)(const void*);
        const void * _data;
    public:
        Event(void(*f)(const void*),const void*d):_fun(f),_data(d) {}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    _p_run(new Event(f,d),p);
}

void QSingleThreadPool::run(
        void(*f)(const std::shared_ptr<void> &),
        std::shared_ptr<void> d,int p) {
    if (f==nullptr) { return; }
    class Event :public _RunableEvent {
        void(*_fun)(const std::shared_ptr<void> &);
        std::shared_ptr<void> _data;
    public:
        Event(void(*f)(const std::shared_ptr<void>&),std::shared_ptr<void>&&d):
            _fun(f),
            _data(std::move(d)) {
        }
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    _p_run(new Event(f,std::move(d)),p);
}

void QSingleThreadPool::run(
        void(*f)(const std::shared_ptr<const void> &),
        std::shared_ptr<const void> d,int p) {
    if (f==nullptr) { return; }
    class Event :public _RunableEvent {
        void(*_fun)(const std::shared_ptr<const void> &);
        std::shared_ptr<const void> _data;
    public:
        Event(void(*f)(const std::shared_ptr<const void>&),std::shared_ptr<const void>&&d):
            _fun(f),
            _data(std::move(d)) {
        }
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    _p_run(new Event(f,std::move(d)),p);
}

void QSingleThreadPool::runStdFunction(std::function<void(void)> f,int p) {
    if (bool(f)==false) { return; }
    class Event :public _RunableEvent {
        std::function<void(void)> _fun;
    public:
        Event(std::function<void(void)>&&f):_fun(std::move(f)) {}
        void do_run() override { _fun(); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    _p_run(new Event(std::move(f)),p);
}

void QSingleThreadPool::addWatcher(QObject *arg) {
    watcher_->add(arg);
}

void QSingleThreadPool::removeWatcher(QObject *arg) {
    watcher_->remove(arg);
}

void QSingleThreadPool::_p_run(RunableEvent *arg,int p) {
    QCoreApplication::postEvent(thread_object_,arg,p);
}

namespace qappwatcher {

namespace {
_ThreadObjectRunableEvent * qapp_events_loop;
std::shared_ptr<QSingleThreadPool> qapp_thread_pool;
std::weak_ptr<QSingleThreadPool> qapp_thread_pool_watcher;
}/*namespace*/

void beginConstructQApplication() {
    staticDelateLaterObject.store(new _ThreadObjectRunableEvent);
    getMutex()->lock();
    assert(qapp_events_loop==nullptr);
    qapp_events_loop=new _ThreadObjectRunableEvent;
    qapp_thread_pool=
        memory::make_shared<QSingleThreadPool>(QSingleThreadPool::private_construct{});
    qapp_thread_pool->thread_object_=qapp_events_loop;
    qapp_thread_pool->watcher_=QObjectsWatcher::instance();
    qapp_thread_pool_watcher=qapp_thread_pool;
    _current_threads::add(std::this_thread::get_id(),qapp_thread_pool);
}

void endConstructQApplication() {
    getMutex()->unlock();
}

void beginDestructQApplication() {
    getMutex()->lock();
    qapp_thread_pool.reset();
    _current_threads::remove(std::this_thread::get_id());
}

void endDestructQApplication() {
    getMutex()->unlock();
}

}/*qappwatcher*/

std::weak_ptr<QSingleThreadPool> QSingleThreadPool::currentQSingleThreadPool() {
    return _current_threads::find(std::this_thread::get_id());
}

std::shared_ptr<QSingleThreadPool> QSingleThreadPool::qAppQSingleThreadPool() {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    auto app=qApp;
    if (app&&(app->closingDown()==false)) {
        return qappwatcher::qapp_thread_pool;
    }
    return{};
}

std::weak_ptr<QSingleThreadPool> qAppQSingleThreadPoolWatcher() {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    auto app=qApp;
    if (app&&(app->closingDown()==false)) {
        return qappwatcher::qapp_thread_pool_watcher;
    }
    return{};
}









