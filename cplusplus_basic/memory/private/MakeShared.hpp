#ifndef _m_MAKE_SHARED_CPP_HPP
#define _m_MAKE_SHARED_CPP_HPP() 1

#include "../Memory.hpp"
#include "Allocator.hpp"

namespace memory {

template<typename _m_T_,typename ... _m_Args_>
std::shared_ptr<_m_T_> make_shared(_m_Args_ &&...args) {
    using _T_=std::remove_cv_t<_m_T_>;
    using __T_=std::aligned_storage_t<sizeof(_T_),alignof(_T_)>;
    try {
        memory::Allocator< std::shared_ptr<_m_T_> > _m_alloc_{};

        auto * _tmp_=memory::malloc(sizeof(__T_));
        if (_tmp_==nullptr) { return{}; }

        try {
            ::new(_tmp_) _T_(std::forward<_m_Args_>(args)...);
        }
        catch (...) {
            memory::free(_tmp_);
            return{};
        }

        return std::shared_ptr<_m_T_>(
            reinterpret_cast<_T_ *>(_tmp_),
            [](_m_T_ * arg) {arg->~_T_(); memory::free(arg); },
            std::move(_m_alloc_));

    }
    catch (...) {
        return{};
    }
    return{};
}

template<typename _m_T_,typename ... _m_Args_>
std::shared_ptr<_m_T_> instance_shared(_m_Args_ &&...args) {
    using _T_=std::remove_cv_t<_m_T_>;
    using __T_=std::aligned_storage_t<sizeof(_T_),alignof(_T_)>;
    try {
        memory::Allocator< std::shared_ptr<_m_T_> > _m_alloc_{};

        auto * _tmp_=memory::malloc(sizeof(__T_));
        if (_tmp_==nullptr) { return{}; }

        try {
            ::new(_tmp_) _T_{ std::forward<_m_Args_>(args)... };
        }
        catch (...) {
            memory::free(_tmp_);
            return{};
        }

        return std::shared_ptr<_m_T_>(
            reinterpret_cast<_T_ *>(_tmp_),
            [](_m_T_ * arg) {arg->~_T_(); memory::free(arg); },
            std::move(_m_alloc_));

    }
    catch (...) {
        return{};
    }
    return{};
}

}/*memory*/


#endif
