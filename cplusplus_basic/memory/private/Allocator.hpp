#ifndef _m_MEMORY_ALLOCATOR_HPP_NEW_
#define _m_MEMORY_ALLOCATOR_HPP_NEW_() 1

#include "../Memory.hpp"
#include <exception>
#include <stdexcept>

namespace memory {

template<typename T>
class Allocator {
    typedef T _Ty;
public:

    static_assert(!std::is_const<_Ty>::value,
        "The C++ Standard forbids containers of const elements "
        "because allocator<const T> is ill-formed.");

    //typedef void _Not_user_specialized;
    typedef _Ty value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;

    template <typename U>
    class rebind {
    public:
        typedef Allocator<U> other;
    };

    Allocator()=default;
    Allocator(const Allocator&)=default;
    Allocator(Allocator&&)=default;
    Allocator&operator=(const Allocator&)=default;
    Allocator&operator=(Allocator&&)=default;
    ~Allocator()=default;

    template<typename U>
    Allocator(const Allocator<U>&) {/*do nothing*/ }
    template<typename U>
    Allocator(Allocator<U>&&) {/*do nothing*/ }

    template<typename U>
    Allocator&operator=(const Allocator<U>&) {/*do nothing*/return *this; }
    template<typename U>
    Allocator&operator=(Allocator<U>&&) {/*do nothing*/return *this; }

    void deallocate(pointer arg,size_type) {
        return memory::free(arg);
    }

private:
    pointer _do_allocate(size_type arg) noexcept(false) {
        if (arg<=0) { return nullptr; }
        auto ans=
            static_cast<pointer>(memory::malloc(arg*sizeof(value_type)));
        if (ans==nullptr) {
            throw std::bad_alloc{};
        }
        return ans;
    }

public:
    pointer allocate(size_type arg) {
        return _do_allocate(arg);
    }

    pointer allocate(size_type arg,const void *) {
        return _do_allocate(arg);
    }

    template<typename _Objty,
        typename... _Types>
        void construct(_Objty *_Ptr,_Types&&... _Args) {
        ::new ((void *)_Ptr) _Objty(std::forward<_Types>(_Args)...);
    }

    template<typename _U_>
    void destroy(_U_ *arg) { arg->~_U_(); return; (void)arg; }

    size_t max_size() const noexcept(true) {
        return ((size_t)(-1)/sizeof(_Ty));
    }

    pointer address(reference _Val) const noexcept(true) {
        return (std::addressof(_Val));
    }

    const_pointer address(const_reference _Val) const noexcept(true) {
        return (std::addressof(_Val));
    }

};

template<>
class Allocator<void> {
public:

    typedef void _Not_user_specialized;
    typedef void value_type;
    typedef void *pointer;
    typedef const void *const_pointer;

    Allocator()=default;
    Allocator(const Allocator&)=default;
    Allocator(Allocator&&)=default;
    Allocator&operator=(const Allocator&)=default;
    Allocator&operator=(Allocator&&)=default;
    ~Allocator()=default;

    template<class _Other>
    class rebind {
    public:
        typedef Allocator<_Other> other;
    };

    template<typename U>
    Allocator(const Allocator<U>&) {/*do nothing*/ }
    template<typename U>
    Allocator(Allocator<U>&&) {/*do nothing*/ }

    template<typename U>
    Allocator&operator=(const Allocator<U>&) {/*do nothing*/return *this; }
    template<typename U>
    Allocator&operator=(Allocator<U>&&) {/*do nothing*/return *this; }

};

template<typename T,typename U>
constexpr inline bool operator==(const Allocator<T>&,const Allocator<U>&) { return false; }

template<typename T,typename U>
constexpr inline bool operator!=(const Allocator<T>&,const Allocator<U>&) { return true; }

template<typename T>
constexpr inline bool operator==(const Allocator<T>&,const Allocator<T>&) { return true; }

template<typename T>
constexpr inline bool operator!=(const Allocator<T>&,const Allocator<T>&) { return false; }

}

#endif



