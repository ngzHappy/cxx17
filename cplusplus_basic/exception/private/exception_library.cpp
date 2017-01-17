#include "../Exception.hpp"
#include "../../lua/private/lua_exception.hpp"
#include <mutex>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <shared_mutex>

namespace exception {

namespace {
inline namespace _exception_private {

/************************************************************************/
inline void _p_exit() { return std::exit(-1); }
inline void _p_quick_exit() { return memory::quick_exit(); }

using _string_t=std::basic_string<char,std::char_traits<char>,memory::Allocator<char>>;
inline _string_t operator""_s(const char *arg,std::size_t argl) {
    return _string_t(arg,argl);
}

class light_recursive_mutex :std::recursive_mutex {
private:
    using _Super=std::recursive_mutex;
public:
    light_recursive_mutex()=default;
    using _Super::try_lock;
    using _Super::unlock;
    void lock(){
        while(false==try_lock()){}
    }
};

class _ExceptionHandle final :public exception::ExceptionHandle {
    typedef light_recursive_mutex _mutex_t;
    typedef std::unique_lock<_mutex_t> _lock_t;
    using _sstream_t=std::basic_stringstream<char,std::char_traits<char>,memory::Allocator<char>>;
    static char _psm_mutex[sizeof(_mutex_t)];
    static _mutex_t & _p_mutex() {
        /*never delete*/
        static auto var=::new (_psm_mutex) _mutex_t;
        return *var;
    }
    bool _pm_exit_=true;
    int _pm_line;
    const char *_pm_functionname;
    const char *_pm_filename;
    template<typename _T_,int _N_>
    static void _p_write(_T_&argO,const char(&arg)[_N_]) {
        argO.write(arg,(_N_-1));
    }
    template<typename _T_,typename _U_>
    static void _p_write(_T_&argO,_U_&&argD) {
        argO<<std::forward<_U_>(argD);
    }
    void __p_write(_sstream_t&arg) {
        _lock_t _{ _p_mutex() };
        std::cout<<arg.rdbuf();
    }
public:

    _ExceptionHandle(
                int argLine,
                const char *argFunc,
                const char *argFile
    ):_pm_line(argLine),_pm_functionname(argFunc),_pm_filename(argFile) {
    }

    void bad_exception_handle() noexcept(true) {
        try {
            print_error("bad_exception_handle");
        }
        catch (...) {}
        this->quick_exit();
    }

    void std_exception_handle(const std::exception &e) noexcept(true) {

        try {
            _string_t var="std::exception "_s+e.what();
            print_information(var.data(),var.size());
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            print_exception(_pm_exit_);
        }

    }

    void std_logic_error_handle(const std::logic_error &e) noexcept(true) {

        try {
            _string_t var="std::logic_error "_s+e.what();
            if (_pm_exit_) {
                print_error(var.data(),var.size());
            }
            else {
                print_information(var.data(),var.size());
            }
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            print_exception(_pm_exit_);
        }

    }

    virtual void _do_print_exception(bool argExit) noexcept(true) override {
        _pm_exit_=argExit;
        try {
            std::rethrow_exception(std::current_exception());
        }
        catch (const std::bad_alloc&) {
            print_error("bad_alloc");
        }
        catch (const lua_exception&) {
            /*ignore lua exception*/
            return;
        }
        catch (const std::logic_error&e) {
            std_logic_error_handle(e);
        }
        catch (const std::exception &e) {
            std_exception_handle(e);
        }
        catch (...) {

            try {
                if (argExit) {
                    print_error("unknow exception ");
                }
                else {
                    print_information("unknow exception ");
                }
            }
            catch (...) {
                bad_exception_handle();
            }

        }
    }

    virtual void _do_print_information(const char* arg,size_t argl) noexcept(true) override {
        if (arg&&(argl>0)) {
            try {
                _sstream_t varStream;
                _p_write(varStream,"information : ");
                if (_pm_filename&&_pm_functionname) {
                    _p_write(varStream,"@line : ");
                    _p_write(varStream,_pm_line);
                    _p_write(varStream," @function_name : ");
                    _p_write(varStream,_pm_functionname);
                    _p_write(varStream," @file_name : ");
                    _p_write(varStream,_pm_filename);
                }
                _p_write(varStream,"\n");
                varStream.write(arg,argl);
                _p_write(varStream,"\n");
                __p_write(varStream);
            }
            catch (...) {/*?????*/
                this->quick_exit();
            }
        }
    }

    virtual void _do_print_error(const char* arg,size_t argl) noexcept(true) override {
        if (arg&&(argl>0)) {
            try {
                _sstream_t varStream;
                _p_write(varStream,"error : ");
                if (_pm_filename&&_pm_functionname) {
                    _p_write(varStream,"@line : ");
                    _p_write(varStream,_pm_line);
                    _p_write(varStream," @function_name : ");
                    _p_write(varStream,_pm_functionname);
                    _p_write(varStream," @file_name : ");
                    _p_write(varStream,_pm_filename);
                }
                _p_write(varStream,"\n");
                varStream.write(arg,argl);
                _p_write(varStream,"\n");
                __p_write(varStream);
            }
            catch (...) {}
        }
        this->quick_exit();
    }

    void _do_quick_exit() noexcept(true) override {
        _p_quick_exit();
    }

private:
    MEMORY_CLASS_NEW_DELETE
};

char _ExceptionHandle::_psm_mutex[sizeof(_ExceptionHandle::_mutex_t)];
/************************************************************************/

class __CreateExceptionHandleFunction {
    typedef std::shared_timed_mutex _mutex_t;
    typedef std::shared_lock<_mutex_t> _slock_t;
    typedef std::unique_lock<_mutex_t> _ulock_t;
    CreateExceptionHandleFunction _pm_function;
    _mutex_t _pm_mutex;
public:
    __CreateExceptionHandleFunction():_pm_function(
                                          [](int a1,const char *a2,const char *a3)->std::unique_ptr<ExceptionHandle> {
        try {
            ExceptionHandle *var=new _ExceptionHandle{ a1,a2,a3 };
            return std::unique_ptr<ExceptionHandle>{var};
        }
        catch (...) {/*?????*/
            _p_quick_exit();
        }
        return nullptr;
    }
    ) {
    }
    CreateExceptionHandleFunction get() {
        _slock_t _{ _pm_mutex };
        return _pm_function;
    }
    CreateExceptionHandleFunction set(CreateExceptionHandleFunction arg) {
        _ulock_t _{ _pm_mutex };
        auto varOld=_pm_function;
        _pm_function=arg;
        return varOld;
    }
};

char _sd_CreateExceptionHandleFunction[sizeof(__CreateExceptionHandleFunction)];
inline __CreateExceptionHandleFunction *get_CreateExceptionHandleFunction() {
    /*never delete*/
    static auto var=::new (_sd_CreateExceptionHandleFunction) __CreateExceptionHandleFunction;
    return var;
}

}/*_private*/
}/*namespace*/


CreateExceptionHandleFunction getCreateExceptionHandleFunction() {
    return get_CreateExceptionHandleFunction()->get();
}

CreateExceptionHandleFunction setCreateExceptionHandleFunction(
        CreateExceptionHandleFunction arg) {
    if (arg==nullptr) { return getCreateExceptionHandleFunction(); }
    return get_CreateExceptionHandleFunction()->set(arg);
}

void exception_handle(
    bool a_exit,
    int a_line,
    const char * a_functionName,
    const char * a_fileName) noexcept(true) {

    try {
        auto var=getCreateExceptionHandleFunction()(a_line,a_functionName,a_fileName);
        var->print_exception(a_exit);
    }
    catch (...) {
        _p_quick_exit();
    }

}

void information_handle(
    const char * a_info,int a_len,
    int a_line,
    const char * a_functionName,
    const char * a_fileName) noexcept(true) {
    try {
        auto var=getCreateExceptionHandleFunction()(a_line,a_functionName,a_fileName);
        var->print_information(a_info,a_len);
    }
    catch (...) {
        _p_quick_exit();
    }
}

void error_handle(
    const char * a_error,int a_len,
    int a_line,
    const char * a_functionName,
    const char * a_fileName) noexcept(true) {
    try {
        auto var=getCreateExceptionHandleFunction()(a_line,a_functionName,a_fileName);
        var->print_error(a_error,a_len);
    }
    catch (...) {
        _p_quick_exit();
    }
}

namespace {
namespace __private {
thread_local char tmp_char_s[256];
class string_view_t {
public:
    const char * data=nullptr;
    std::size_t length=0;
};
inline string_view_t int_string(int arg) {
    auto endl=&tmp_char_s[200];
    string_view_t ans;

    if (arg==0) {
        *endl='0';
        ans.data=endl;
        ans.length=1;
        return ans;
    }

    bool is_negative=false;
    if (arg<0) {
        arg=-arg;
        is_negative=true;
    }
    
    auto tmp=std::div(arg,10);
    *endl=char(tmp.rem+'0');
    ++ans.length;

    while (tmp.quot!=0) {
        arg=tmp.quot;
        tmp=std::div(arg,10);
        --endl;
        *endl=char(tmp.rem+'0');
        ++ans.length;
    }

    if (is_negative) {
        --endl;
        *endl='-';
        ++ans.length;
    }

    ans.data=endl;
    return ans;
}

}/*__private*/
}/**/
string create_string(
    const char * argD,int argl,
    int a_line,
    const char * a_functionName,
    const char * a_fileName) {
    try {
        if (argD&&(argl>0)) {
            string varAns{ argD, static_cast<std::size_t>(argl) };
            if (a_functionName&&a_fileName) {
                {
                    auto str=__private::int_string(a_line);
                    varAns.append("@from: ",7);
                    varAns.append(str.data,str.length);
                    varAns.append("@from: ",7);
                    varAns.append(a_functionName);
                    varAns.append("@from: ",7);
                    varAns.append(a_fileName);
                }
            }
            return std::move(varAns);
        }
    }
    catch (...) {}
    return{};
}

}/*exception*/



