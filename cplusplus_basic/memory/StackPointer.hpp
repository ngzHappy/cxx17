#ifndef STACK_POINTER_HPP_0x79213a5
#define STACK_POINTER_HPP_0x79213a5

#include "../cplusplus_basic.hpp"
#include <type_traits>

namespace memory {

template<typename _T_>
class StackPointer {
    _T_ * user_;
    _T_ * owner_;
public:
    constexpr StackPointer(_T_* arg):user_(arg),owner_(arg) {}
    constexpr StackPointer():StackPointer(nullptr) {}
    ~StackPointer() { delete owner_; }
    _T_* release() { owner_=nullptr; return user_; }
    _T_* release(_T_* arg) { auto ans=user_; owner_=arg;  user_=arg; return ans; }
    void reset(_T_* arg) { owner_=arg; user_=arg; }
    _T_* pointer() { return user_; }
    constexpr const _T_* pointer()const { return user_; }
    _T_* operator->() { return pointer(); }
    constexpr const _T_* operator->()const { return pointer(); }
    _T_& operator*() { return *pointer(); }
    constexpr const _T_& operator*()const { return *pointer(); }
    operator _T_* () { return pointer(); }
    constexpr operator const _T_* ()const { return pointer(); }
    constexpr explicit operator bool()const { return pointer()!=nullptr; }
    StackPointer& operator=(_T_* arg) { reset(arg); return *this; }
    auto toStdPointer() { return std::unique_ptr<_T_>{ this->release() }; }
    auto toConstStdPointer() { return std::unique_ptr<const _T_>{ this->release() }; }
protected:
    StackPointer(StackPointer&&arg):user_(arg.user_),owner_(arg.owner_) {
        arg.owner_=nullptr;
    }
    StackPointer&operator=(StackPointer&&arg) {
        user_=arg.user_; owner_=arg.owner_; arg.owner_=nullptr;
    }
    StackPointer(const StackPointer&)=delete;
    StackPointer&operator=(const StackPointer&)=delete;
    template<typename _1T_,typename ..._1_Args>
    friend StackPointer<_1T_> makeStackPointer(_1_Args&&...);

};

namespace /*Ⓟ*/\u24c5_memory_makeStackPointer_select_
{

template<typename T,bool=false>
class Select {
public:
    typedef T type;
};

template<typename _T_>
class VirtualWrap :public _T_ {
public:
    using _T_::_T_;
    VirtualWrap() {}
    VirtualWrap(const _T_&arg):_T_(arg) {}
    VirtualWrap(const _T_&&arg):_T_(arg) {}
    VirtualWrap(_T_&arg):_T_(arg) {}
    VirtualWrap(_T_&&arg):_T_(std::move(arg)) {}
private:
    CPLUSPLUS_OBJECT(VirtualWrap)
};

template<typename T>
class Select<T,true> {
public:
    typedef VirtualWrap<T> type;
};

}/*\u24c5_memory_makeStackPointer_select_*/

template<typename _T_,typename ...Args>
StackPointer<_T_> makeStackPointer(Args&&...args) {
    constexpr bool _isvd_=(std::has_virtual_destructor<_T_>::value)&&
        (std::is_final<_T_>::value==false);
    using __T_=typename \
        \u24c5_memory_makeStackPointer_select_::Select<_T_,_isvd_>::type;
    /*rewrite in c++17*/
    return new __T_(std::forward<Args>(args)...);
}

}/*memory*/

#endif


