#ifndef QRUNONCE_HPP
#define QRUNONCE_HPP

#include <tuple>
#include <utility>
#include <type_traits>
#include <QtCore/qobject.h>
#include <cplusplus_basic.hpp>

namespace _private_QRunOnce_ {

template<typename T,bool=(std::is_base_of<QObject,T>::value)||
(std::is_pointer<T>::value&&std::is_convertible<T,QObject *>::value)>
class Item {
public:
    Item(QObject &o) { o.deleteLater(); }
    Item(QObject *o) { o->deleteLater(); }

    constexpr void destruct() const {}

    Item()=default;
    Item(const Item &)=default;
    Item&operator=(const Item &)=default;
    Item(Item &&)=default;
    Item&operator=(Item &&)=default;
};

template<typename T>
class Item<T,false> {
    T __xobject/*a copy of data*/;
public:

    Item(T&&o):__xobject(std::move(o)) {
    }

    Item(const T&&)=delete;
    Item(const T&)=delete;
    Item(T&)=delete;

    void destruct() {
        __xobject.reset();
    }

    Item()=default;
    Item(const Item &)=default;
    Item&operator=(const Item &)=default;
    Item(Item &&)=default;
    Item&operator=(Item &&)=default;
};

/*rewrite in c++17*/
template<typename T>
void destruct(std::tuple<T> & arg) {
    std::get<0>(arg).destruct();
}

template<typename T0,typename T1>
void destruct(std::tuple<T0,T1> & arg) {
    std::get<0>(arg).destruct();
    std::get<1>(arg).destruct();
}

template<typename T0,typename T1,typename T2>
void destruct(std::tuple<T0,T1,T2> & arg) {
    std::get<0>(arg).destruct();
    std::get<1>(arg).destruct();
    std::get<2>(arg).destruct();
}

template<typename T0,typename T1,typename T2,typename T3>
void destruct(std::tuple<T0,T1,T2,T3> & arg) {
    std::get<0>(arg).destruct();
    std::get<1>(arg).destruct();
    std::get<2>(arg).destruct();
    std::get<3>(arg).destruct();
}

template<typename T0,typename T1,typename T2,typename T3,
    typename T4>
    void destruct(std::tuple<T0,T1,T2,T3,T4> & arg) {
    std::get<0>(arg).destruct();
    std::get<1>(arg).destruct();
    std::get<2>(arg).destruct();
    std::get<3>(arg).destruct();
    std::get<4>(arg).destruct();
}

template<typename T0,typename T1,typename T2,typename T3,
    typename T4,typename T5>
    void destruct(std::tuple<T0,T1,T2,T3,T4,T5> & arg) {
    std::get<0>(arg).destruct();
    std::get<1>(arg).destruct();
    std::get<2>(arg).destruct();
    std::get<3>(arg).destruct();
    std::get<4>(arg).destruct();
    std::get<5>(arg).destruct();
}

template<typename T0,typename T1,typename T2,typename T3,
    typename T4,typename T5,typename T6>
    void destruct(std::tuple<T0,T1,T2,T3,T4,T5,T6> & arg) {
    std::get<0>(arg).destruct();
    std::get<1>(arg).destruct();
    std::get<2>(arg).destruct();
    std::get<3>(arg).destruct();
    std::get<4>(arg).destruct();
    std::get<5>(arg).destruct();
    std::get<6>(arg).destruct();
}

template<typename T0,typename T1,typename T2,typename T3,
    typename T4,typename T5,typename T6,typename T7>
    void destruct(std::tuple<T0,T1,T2,T3,T4,T5,T6,T7> & arg) {
    std::get<0>(arg).destruct();
    std::get<1>(arg).destruct();
    std::get<2>(arg).destruct();
    std::get<3>(arg).destruct();
    std::get<4>(arg).destruct();
    std::get<5>(arg).destruct();
    std::get<6>(arg).destruct();
    std::get<7>(arg).destruct();
}

/*rewrite in c++17*/
//template<typename T0,typename T1,typename T2,typename T3,
//         typename T4,typename T5,typename T6,typename T7,
//         typename T8,typename ... T>
//void destruct(std::tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T...> & arg){
//    std::get<0>(arg).destruct();
//    std::get<1>(arg).destruct();
//    std::get<2>(arg).destruct();
//    std::get<3>(arg).destruct();
//    std::get<4>(arg).destruct();
//    std::get<5>(arg).destruct();
//    std::get<6>(arg).destruct();
//    std::get<7>(arg).destruct();
//    std::get<8>(arg).destruct();
//}

}/*_private_QRunOnce_*/

template<typename ... T >
class QRunOnce : public std::tuple< _private_QRunOnce_::Item<T>... > {
    using _Super=std::tuple< _private_QRunOnce_::Item<T>... >;
    void * _p_this_not_moved;
    void _p_destruct() {
        if (_p_this_not_moved) {
            _private_QRunOnce_::destruct(*this);
            _p_this_not_moved=nullptr;
        }
    }
public:
    QRunOnce() { _p_this_not_moved=nullptr; }
    template<typename ... U>
    QRunOnce(U &&...args):_Super(std::forward<U>(args) ...) {
        _p_this_not_moved=this;
    }
    ~QRunOnce() { _p_destruct(); }

    QRunOnce(const QRunOnce &)=delete;
    QRunOnce&operator=(const QRunOnce &)=delete;
    QRunOnce&operator=(QRunOnce &&)=delete;

    QRunOnce(QRunOnce && arg):_Super(std::move(arg)) {
        this->_p_this_not_moved=arg._p_this_not_moved;
        arg._p_this_not_moved=nullptr;
    }

private:
    CPLUSPLUS_OBJECT(QRunOnce)
};

template<typename ... T>
inline QRunOnce< std::remove_reference_t<T> ...> makeQRunOnce(T &&...args) {
    return QRunOnce<std::remove_reference_t<T>...>(std::forward<T>(args) ...);
}

#endif // QRUNONCE_HPP
