#ifndef QAPPLICATIONWATCHER_HPP
#define QAPPLICATIONWATCHER_HPP

#include <memory>
#include <type_traits>
#include "qt_basic_global.hpp"

namespace qappwatcher{
QT_BASICSHARED_EXPORT void beginConstructQApplication();
QT_BASICSHARED_EXPORT void endConstructQApplication();
QT_BASICSHARED_EXPORT void beginDestructQApplication();
QT_BASICSHARED_EXPORT void endDestructQApplication();
}/*qappwatcher*/

template<typename _T_>
class QApplicationWatcher{
    _T_ * _p_application;
    using _t_AppData=std::aligned_storage_t<sizeof(_T_),alignof(_T_)>;
    _t_AppData _p_data_application;
public:
    template<typename ... Args>
    QApplicationWatcher(Args && ...);
    ~QApplicationWatcher();

    _T_ * operator->(){ return _p_application; }
    const _T_ * operator->() const{ return _p_application; }

    _T_ & operator*(){ return *_p_application; }
    const _T_ & operator*() const { return *_p_application; }

    _T_ * get() { return _p_application; }
    const _T_ * get() const { return _p_application; }
private:
    CPLUSPLUS_OBJECT(QApplicationWatcher)
};

template<typename _T_>
template<typename ... Args>
QApplicationWatcher<_T_>::QApplicationWatcher(Args && ...args){
    class Locker{
    public:
        Locker(){  qappwatcher::beginConstructQApplication(); }
        ~Locker(){ qappwatcher::endConstructQApplication();  }
    };
    Locker locker;
    _p_application = ::new (&_p_data_application) _T_(
                std::forward<Args>(args)...);
}

template<typename _T_>
QApplicationWatcher<_T_>::~QApplicationWatcher(){
    class Locker{
    public:
        Locker(){  qappwatcher::beginDestructQApplication(); }
        ~Locker(){ qappwatcher::endDestructQApplication();  }
    };
    Locker locker;
    _p_application->~_T_();
}

#endif // QAPPLICATIONWATCHER_HPP
