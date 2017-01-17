#ifndef _EXCEPTION_HPP_0x325678
#define _EXCEPTION_HPP_0x325678

#include "../memory/Memory.hpp"
#include <string>
#include <exception>
#include <stdexcept>

namespace exception {

using string=std::basic_string<char,std::char_traits<char>,memory::Allocator<char>>;
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT string create_string(
const char *,int,
int a_line=-1,
const char * a_functionName=nullptr,
const char * a_fileName=nullptr);

class RuntimeError :public std::exception {
    std::shared_ptr<const string> _pm_data;
public:
    RuntimeError(const char *a,int al,
        int a_line=-1,
        const char * a_functionName=nullptr,
        const char * a_fileName=nullptr):std::exception(),
        _pm_data(
            memory::make_shared<const string>(
            create_string(a,al,a_line,a_functionName,a_fileName))){}

    const char * what() const noexcept(true) override { return _pm_data->c_str(); }
};

class LogicError :public std::logic_error {
    std::shared_ptr<const string> _pm_data;
public:
    LogicError(const char *a,int al,
        int a_line=-1,
        const char * a_functionName=nullptr,
        const char * a_fileName=nullptr):std::logic_error(nullptr),
        _pm_data(
            memory::make_shared<const string>(
            create_string(a,al,a_line,a_functionName,a_fileName))){}

    const char * what() const noexcept(true) override { return _pm_data->c_str(); }
};

#define throw_runtime_error(_s_,_sl_)  throw exception::RuntimeError((_s_),(_sl_),__LINE__,__func__,__FILE__)
#define throw_logic_error(_s_,_sl_)  throw exception::LogicError((_s_),(_sl_),__LINE__,__func__,__FILE__)

class ExceptionHandle {
    ExceptionHandle&operator=(const ExceptionHandle&)=delete;
    ExceptionHandle&operator=(ExceptionHandle&&)=delete;
    ExceptionHandle(const ExceptionHandle&)=delete;
    ExceptionHandle(ExceptionHandle&&)=delete;
public:
    using size_t=std::size_t;
    using isize_t=std::make_signed_t<size_t>;
    virtual ~ExceptionHandle()=default;
    ExceptionHandle()=default;
protected:
    virtual void _do_print_exception(bool argExit) noexcept(true)=0;
    virtual void _do_print_information(const char*,size_t) noexcept(true)=0;
    virtual void _do_print_error(const char*,size_t) noexcept(true)=0;
    virtual void _do_quick_exit() noexcept(true)=0;
public:
    template<typename _C_T_>
    inline void print_information(const _C_T_ * const &arg,isize_t argl) noexcept(true) {
        _do_print_information(arg,static_cast<size_t>(argl));
    }
    template<typename _C_T_>
    inline void print_information(const _C_T_ * const &arg,size_t argl) noexcept(true) {
        _do_print_information(arg,argl);
    }
    template<typename _C_T_,int _N_>
    inline void print_information(_C_T_(&arg)[_N_]) {
        _do_print_information(arg,static_cast<size_t>(_N_-1));
    }

    template<typename _C_T_>
    inline void print_error(const _C_T_ * const &arg,isize_t argl) noexcept(true) {
        _do_print_error(arg,static_cast<size_t>(argl));
    }
    template<typename _C_T_>
    inline void print_error(const _C_T_ * const &arg,size_t argl) noexcept(true) {
        _do_print_error(arg,argl);
    }
    template<typename _C_T_,int _N_>
    inline void print_error(_C_T_(&arg)[_N_]) {
        _do_print_error(arg,static_cast<size_t>(_N_-1));
    }

    inline void print_exception(bool argExit=true) noexcept(true) {
        _do_print_exception(argExit);
    }
    inline void quick_exit() noexcept(true) { _do_quick_exit(); }
};

typedef std::unique_ptr<ExceptionHandle>(*CreateExceptionHandleFunction)(int/*line*/,const char * /*func*/,const char * /*file*/);
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT CreateExceptionHandleFunction getCreateExceptionHandleFunction();
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT CreateExceptionHandleFunction setCreateExceptionHandleFunction(CreateExceptionHandleFunction);

}/*exception*/

namespace exception {

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void exception_handle(
    bool a_exit=true,
    int a_line=0,
    const char * a_functionName=nullptr,
    const char * a_fileName=nullptr) noexcept(true);

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void information_handle(
    const char * a_info,int a_len,
    int a_line=0,
    const char * a_functionName=nullptr,
    const char * a_fileName=nullptr) noexcept(true);

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void error_handle(
    const char * a_error,int a_len,
    int a_line=0,
    const char * a_functionName=nullptr,
    const char * a_fileName=nullptr) noexcept(true);

}/*exception*/

#endif


