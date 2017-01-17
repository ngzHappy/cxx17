#ifndef QSINGLETHREADPOOL_HPP
#define QSINGLETHREADPOOL_HPP

#include <functional>
#include <type_traits>
#include <shared_mutex>
#include <QtCore/QEvent>
#include <QtCore/qobject.h>
#include "QObjectsWatcher.hpp"
#include "QApplicationWatcher.hpp"

class QT_BASICSHARED_EXPORT QSingleThreadPool :public QObject {
    Q_OBJECT
private:
    static QEvent::Type eventID();
    class private_construct {};
    friend QT_BASICSHARED_EXPORT void qappwatcher::beginConstructQApplication();
    friend QT_BASICSHARED_EXPORT void qappwatcher::endConstructQApplication();
    friend QT_BASICSHARED_EXPORT void qappwatcher::beginDestructQApplication();
    friend QT_BASICSHARED_EXPORT void qappwatcher::endDestructQApplication();
public:
    QSingleThreadPool(const private_construct &);
    QSingleThreadPool(QObject * /**/=nullptr);
    ~QSingleThreadPool();

    void run(void(*)(void),int=Qt::NormalEventPriority);
    void run(void(*)(void*),void *,int=Qt::NormalEventPriority);
    void run(void(*)(const void*),const void *,int=Qt::NormalEventPriority);
    void run(void(*)(const std::shared_ptr<void>&),std::shared_ptr<void>,int=Qt::NormalEventPriority);
    void run(void(*)(const std::shared_ptr<const void>&),std::shared_ptr<const void>,int=Qt::NormalEventPriority);
    void runStdFunction(std::function<void(void)>,int=Qt::NormalEventPriority);
    template<typename T>void runLambda(T &&,int=Qt::NormalEventPriority);

    class Runable {
    protected:
        virtual void do_run()=0;
    public:
        virtual ~Runable()=default;
    };

    class RunableEvent :
        public QEvent,
        public Runable {
    public:
        RunableEvent():QEvent(eventID()) {}
        inline void run() {
            try { do_run(); }
            catch (...) { CPLUSPLUS_EXCEPTION(false); }
        }
    };

    void addWatcher(QObject *);
    void removeWatcher(QObject *);
    std::shared_ptr<QObjectsWatcher> getWatcher()const { return watcher_; }
    template<typename ...T>
    QObjectsWatcher::LockType lock(T&&...args) {
        return QObjectsWatcher::lock(getWatcher(),std::forward<T>(args)...);
    }

    static std::weak_ptr<QSingleThreadPool> currentQSingleThreadPool();
    static std::shared_ptr<QSingleThreadPool> qAppQSingleThreadPool();
    static std::weak_ptr<QSingleThreadPool> qAppQSingleThreadPoolWatcher();

    class QT_BASICSHARED_EXPORT LockType {
        friend class QSingleThreadPool;
        std::shared_ptr<QSingleThreadPool> _data_pool;
        std::shared_ptr<QEventLoopLocker> _data_qapp;
        QSingleThreadPool * _p_get() { return _data_pool.get(); }
        const QSingleThreadPool * _p_get() const { return _data_pool.get(); }
    protected:
        LockType()=default;
        LockType(const LockType&)=default;
        LockType&operator=(const LockType&)=default;
        LockType(LockType&&)=default;
        LockType&operator=(LockType&&)=default;
        LockType(std::shared_ptr<QSingleThreadPool>&&);
        LockType(std::shared_ptr<QSingleThreadPool>&&,std::shared_ptr<QEventLoopLocker>&&);
    public:
        operator bool() const { return bool(_data_pool); }
        QSingleThreadPool * operator->() { return _p_get(); }
        const QSingleThreadPool * operator->() const { return _p_get(); }
        QSingleThreadPool &operator*() { return *_p_get(); }
        const QSingleThreadPool &operator*()const { return *_p_get(); }
    };

    template<typename ...T>
    static LockType lockWithQApp(std::weak_ptr<QSingleThreadPool>&&arg,T&&...t) {
        return LockType{ arg.lock() ,std::forward<T>(t)... };
    }
    template<typename ...T>
    static LockType lockWithQApp(std::weak_ptr<QSingleThreadPool>&arg,T&&...t) {
        return LockType{ arg.lock(),std::forward<T>(t)... };
    }
    template<typename ...T>
    static LockType lockWithQApp(const std::weak_ptr<QSingleThreadPool>&arg,T&&...t) {
        return LockType{ arg.lock(),std::forward<T>(t)... };
    }

    QThread * getQThread()const{ return thread_object_->thread(); }

private:
    std::shared_ptr<QObjectsWatcher> watcher_;
    std::shared_ptr<QSingleThreadPool> children_;
    QObject * thread_object_;
    class _Thread;
    void _p_run(RunableEvent *,int);
    using QObject::thread;
    using QObject::moveToThread;
    using QObject::parent;
    using QObject::setParent;
private:
    CPLUSPLUS_OBJECT(QSingleThreadPool)
};

template<typename T>
void QSingleThreadPool::runLambda(T && arg,int p) {
    using U=std::remove_reference_t<T>;
    class _RunableEvent :public RunableEvent {
        U fun_;
    public:
        _RunableEvent(T &&arg):fun_(std::forward<T>(arg)) {}
        void do_run()override { fun_(); }
    private:
        CPLUSPLUS_OBJECT(_RunableEvent)
    };
    _p_run(new _RunableEvent(std::forward<T>(arg)),p);
}

Q_DECLARE_METATYPE(std::shared_ptr<void>)

#endif // QSINGLETHREADPOOL_HPP
