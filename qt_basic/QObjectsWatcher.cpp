#include <mutex>
#include <cassert>
#include <type_traits>
#include <shared_mutex>
#include <QtCore/qdebug.h>
#include <QtCore/qtimer.h>
#include <QtCore/qthread.h>
#include "QObjectsWatcher.hpp"
#include "QApplicationWatcher.hpp"
#include <QtCore/qcoreapplication.h>
#include "_PrivateQObjectsWatcher.hpp"

namespace qappwatcher {
extern std::shared_timed_mutex * getMutex();
}

QObjectsWatcher::QObjectsWatcher(QObject *arg):QObject(arg) {
    _pm_data=new _PrivateQObjectsWatcher(this);
}

QObjectsWatcher::~QObjectsWatcher() {
    auto _pm_old=_pm_data;
    delete _pm_old;

    _pm_data=nullptr;
}

_PrivateQObjectsWatcher::_PrivateQObjectsWatcher(QObjectsWatcher *s):super(s) {
    objectItemsMutex=memory::make_shared<light_mutex>();
    this->add(super);
}

_PrivateQObjectsWatcher::~_PrivateQObjectsWatcher() {

}

static QObject * _delete_in_qapp=nullptr;
static void _s_delete_in_qapp() {
    _delete_in_qapp=new QObject;
}
Q_COREAPP_STARTUP_FUNCTION(_s_delete_in_qapp)

void _PrivateQObjectsWatcher::do_quit() {
    isQuit=true;

    try {
        super->finished();
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }

    if (isDeleteOnFinished) {
     
        if (_delete_in_qapp==nullptr) {
            delete super;
        }
        else {
            /*延迟10ms后删除*/
            QTimer::singleShot(10,_delete_in_qapp,[super=this->super]() {
                //qDebug()<<"delete do_quit"<<super;
                delete super; 
            });
        }
    }
}

void _PrivateQObjectsWatcher::quit() {
    if (isQuit) { return; }

    auto varLock=getObjectItemsLock();
    if (isQuit) { return; }
    isQuit=true;

    {
        auto varPos=objectItems.find(super);
        if (varPos!=objectItems.end()) {
            this->disconnect(varPos->connectData);
            objectItems.erase(varPos);
        }
    }

    /*really quit*/
    if (objectItems.empty()==true) {
        do_quit();
    }

}

void _PrivateQObjectsWatcher::add(QObject *arg) {
    if (arg==nullptr) { return; }

    auto varLock=getObjectItemsLock();

    if (isQuit) {
        assert("this is a logical error"&&false);
        delete arg;
        return;
    }

    if (objectItems.count(arg)>0) { return; }
    objectItems.emplace(arg,connect(arg,&QObject::destroyed,
        this,&_PrivateQObjectsWatcher::remove));

}

void _PrivateQObjectsWatcher::remove(QObject *arg) {
    if (arg==nullptr) { return; }
    auto varLock=getObjectItemsLock();

    {
        auto pos=objectItems.find(arg);
        if (pos==objectItems.end()) { return; }

        this->disconnect(pos->connectData);

        objectItems.erase(pos);
    }

    /*really quit*/
    if ((isQuit)&&(objectItems.empty()==true)) {
        do_quit();
    }

}

void QObjectsWatcher::quit() {
    pData()->quit();
}

void QObjectsWatcher::add(QObject *arg) {
    pData()->add(arg);
}

void QObjectsWatcher::remove(QObject *arg) {
    pData()->remove(arg);
}

bool QObjectsWatcher::isOnFinishedDelete()const {
    return pData()->isDeleteOnFinished;
}

void QObjectsWatcher::setOnFinishedDelete(bool arg) {
    pData()->isDeleteOnFinished=arg;
}

namespace {

bool _p_isQAppQuited() {
    if (QCoreApplication::closingDown()) { return true; }
    if (QCoreApplication::startingUp()) { return false; }
    return QCoreApplication::instance()==nullptr;
}

}

bool QObjectsWatcher::isQAppQuited() {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    return _p_isQAppQuited();
}

namespace {

std::shared_ptr<QEventLoopLocker> getMainLocker() {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) {
        return{};
    }
    return memory::make_shared<QEventLoopLocker>();
}

}/*namespace*/

QObjectsWatcher::LockType::LockType(
    std::shared_ptr<QObjectsWatcher> && arg,
    std::shared_ptr<QEventLoopLocker> && b):
    _data(std::move(arg)) {
    if (bool(_data)==false) { return; }
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { _data.reset(); return; }
    _qapp_data=std::move(b);
}

QObjectsWatcher::LockType::LockType(std::shared_ptr<QObjectsWatcher> &&arg):
    _data(std::move(arg)) {
    if (bool(_data)==false) { return; }
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { _data.reset(); return; }
    if (_qapp_data) {
        return;
    }
    _qapp_data=getMainLocker();
}

QObjectsWatcher::LockType
QObjectsWatcher::lock(std::weak_ptr<QObjectsWatcher>&arg,std::shared_ptr<QEventLoopLocker> b) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    return{ arg.lock() ,std::move(b) };
}

QObjectsWatcher::LockType QObjectsWatcher::lock(std::weak_ptr<QObjectsWatcher>&&arg,std::shared_ptr<QEventLoopLocker>b) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    return{ arg.lock() ,std::move(b) };
}

QObjectsWatcher::LockType QObjectsWatcher::lock(const std::shared_ptr<QObjectsWatcher>&arg,std::shared_ptr<QEventLoopLocker>b) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    auto var=arg;
    return{ std::move(var) ,std::move(b) };
}

QObjectsWatcher::LockType QObjectsWatcher::lock(std::shared_ptr<QObjectsWatcher>&&arg,std::shared_ptr<QEventLoopLocker>b) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    return{ std::move(arg),std::move(b) };
}

QObjectsWatcher::LockType
QObjectsWatcher::lock(std::weak_ptr<QObjectsWatcher>&arg) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    return arg.lock();
}

QObjectsWatcher::LockType QObjectsWatcher::lock(std::weak_ptr<QObjectsWatcher>&&arg) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    return arg.lock();
}

QObjectsWatcher::LockType QObjectsWatcher::lock(const std::shared_ptr<QObjectsWatcher>&arg) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    auto var=arg;
    return std::move(var);
}

QObjectsWatcher::LockType QObjectsWatcher::lock(std::shared_ptr<QObjectsWatcher>&&arg) {
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return{}; }
    return std::move(arg);
}

std::shared_ptr<QObjectsWatcher>
QObjectsWatcher::instance() {
    return _p_instance();
}

std::shared_ptr<QObjectsWatcher>
QObjectsWatcher::_p_instance() {
    using _T_=QObjectsWatcher;
    using _m_T_=QObjectsWatcher;

    try {
        memory::Allocator< std::shared_ptr<_m_T_> > _m_alloc_{};

        auto * varAns=new _T_;

        auto var=std::shared_ptr<_m_T_>(
                    varAns,
                    [](_m_T_ * arg) {  arg->quit(); },
                std::move(_m_alloc_));

        varAns->_pm_this=var;
        return std::move(var);
    }
    catch (...) {
        return{};
    }

    return{};
}

#include "QSingleThreadPool.hpp"
QSingleThreadPool::LockType::LockType(std::shared_ptr<QSingleThreadPool>&&arg) {
    if (false==bool(arg)) { return; }
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return; }
    _data_pool=std::move(arg);
    _data_qapp=memory::make_shared<QEventLoopLocker>();
}

QSingleThreadPool::LockType::LockType(std::shared_ptr<QSingleThreadPool>&&arg,std::shared_ptr<QEventLoopLocker>&&b) {
    if (false==bool(arg)) { return; }
    std::shared_lock<std::shared_timed_mutex> _lock_{ *qappwatcher::getMutex() };
    if (_p_isQAppQuited()) { return; }
    _data_pool=std::move(arg);
    _data_qapp=std::move(b);
}

/*End Of The File.*/
