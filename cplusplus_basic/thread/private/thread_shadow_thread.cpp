#include <list>
#include <atomic>
#include <chrono>
#include <cassert>
#include <cinttypes>
#include <condition_variable>
#include "thread_shadow_thread.hpp"
#include "../../private/SpinMutex.hpp"

namespace thread {

namespace  ____ShadowThread {
/*this will not be deleted*/
static memory::StaticData<ShadowThread> _data;
}/*____ShadowThread*/

ShadowThread * ShadowThread::instance() {
    static memory::StaticPointer<ShadowThread> ans(
        ____ShadowThread::_data);
    return ans.pointer();
}

namespace {

namespace ___ShadowThread {

template<typename T>
class List :public std::list<T,memory::Allocator<T>> {
private:
};

}/*____ShadowThread*/
}/*namespace*/

class  ShadowThread::_PrivateShadowThread :
    public std::enable_shared_from_this<_PrivateShadowThread> {
public:
    using light_mutex=_pm_file::spin_mutex;
    std::thread __m_thread;
    light_mutex __m_mutex;
    std::atomic<bool> __m_quit_{ false };
    std::condition_variable_any __m_cv_functions;
    std::atomic<std::size_t> __m_functions_count{ 0 };
    using _t_pvsf=___ShadowThread::List<std::pair<TypePlainVoidStarFunction,void*>>;
    using _t_pcvsf=___ShadowThread::List<std::pair<TypePlainConstVoidStarFunction,const void*>>;
    
    light_mutex _m_m_plain_voidstar_functions;
    _t_pvsf __m_plain_voidstar_functions;
    
    light_mutex _m_m_plain_constvoidstar_functions;
    _t_pcvsf __m_plain_constvoidstar_functions;
    
    light_mutex _m_m_stdfunctions;
    ___ShadowThread::List<TypeStdFunction> __m_stdfunctions;
    
    light_mutex _m_m_plainfunctions;
    ___ShadowThread::List<TypePlainFunction> __m_plainfunctions;

    void quit() {
        {
            std::unique_lock<light_mutex> _{ __m_mutex };
            if (__m_quit_) { return; }
            __m_quit_=true;
        }
        __m_thread.detach();
        __m_cv_functions.notify_all();
    }

    void start() {
        auto _thisp=this->shared_from_this();
        __m_thread=std::thread([_thisp]() {
            auto thisp=_thisp.get();
            for (;;) {

                {/*读临界区*/
                    std::unique_lock<light_mutex> varLock{ thisp->__m_mutex };

                    while ((thisp->__m_functions_count)<1) {
                        if (thisp->__m_quit_) { return; }
                        using namespace std::chrono_literals;
                        thisp->__m_cv_functions.wait_for(varLock,1s);
                    }
                }

                while ((thisp->__m_functions_count)>0) {
                    if (thisp->__m_quit_) { return; }
                    thisp->do_plain_functions();
                    thisp->do_plain_void_star_functions();
                    thisp->do_plain_const_void_star_functions();
                    thisp->do_std_functions();
                }

            }
        });
    }

    void do_std_functions() noexcept(true) {

        ___ShadowThread::List<TypeStdFunction> varFunctions;

        {
            /*获得资源锁*/
            std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_stdfunctions };
            if (__m_stdfunctions.empty()) {
                return;
            }

            varFunctions=std::move(__m_stdfunctions);
            assert(__m_stdfunctions.size()==0);
        }

        {
            /*写临界区*/
            std::unique_lock<light_mutex> varLock{ __m_mutex };
            __m_functions_count-=varFunctions.size();
        }


        for (auto & varI:varFunctions) {
            try {
                varI();
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
        }

    }

    void do_plain_functions() noexcept(true) {

        ___ShadowThread::List<TypePlainFunction> varFunctions;

        {
            std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_plainfunctions };
            if (__m_plainfunctions.empty()) {
                return;
            }

            varFunctions=std::move(__m_plainfunctions);
            assert(__m_plainfunctions.size()==0);
        }

        {
            std::unique_lock<light_mutex> varLock{ __m_mutex };
            __m_functions_count-=varFunctions.size();
        }


        for (auto & varI:varFunctions) {
            try {
                varI();
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
        }

    }

    void do_plain_const_void_star_functions() noexcept(true) {

        _t_pcvsf varFunctions;


        {
            std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_plain_constvoidstar_functions };

            if (__m_plain_constvoidstar_functions.empty()) {
                return;
            }

            varFunctions=std::move(__m_plain_constvoidstar_functions);
            assert(__m_plain_constvoidstar_functions.size()==0);
        }

        {
            std::unique_lock<light_mutex> varLock{ __m_mutex };
            __m_functions_count-=varFunctions.size();
        }


        for (auto & varI:varFunctions) {
            try {
                varI.first(varI.second);
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
        }

    }

    void do_plain_void_star_functions() noexcept(true) {

        _t_pvsf varFunctions;

        {
            std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_plain_voidstar_functions };

            if (__m_plain_voidstar_functions.empty()) {
                return;
            }

            varFunctions=std::move(__m_plain_voidstar_functions);
            assert(__m_plain_voidstar_functions.size()==0);
        }

        {
            std::unique_lock<light_mutex> varLock{ __m_mutex };
            __m_functions_count-=varFunctions.size();
        }

        for (auto & varI:varFunctions) {
            try {
                varI.first(varI.second);
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
        }

    }

    void run_plain_function(TypePlainFunction arg) {
        {
            std::unique_lock<light_mutex> varLock{ __m_mutex };
            if (__m_quit_) { return; }
            ++__m_functions_count;
        }

        {
            std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_plainfunctions };
            __m_plainfunctions.push_back(arg);
        }
        __m_cv_functions.notify_all();
    }

    void _p_run_std_function(TypeStdFunction && arg) {
        {
            std::unique_lock<light_mutex> varLock{ __m_mutex };
            if (__m_quit_) { return; }
            ++__m_functions_count;
        }

        {
            std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_stdfunctions };
            __m_stdfunctions.push_back(std::move(arg));
        }
        __m_cv_functions.notify_all();
    }

    void _p_run_plain_constvoidstar_function(TypePlainConstVoidStarFunction arg,
        const void * argData) {
            {
                std::unique_lock<light_mutex> varLock{ __m_mutex };
                if (__m_quit_) { return; }
                ++__m_functions_count;
            }

            {
                std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_plain_constvoidstar_functions };
                __m_plain_constvoidstar_functions.emplace_back(arg,argData);
            }
            __m_cv_functions.notify_all();
    }

    void _p_run_plain_voidstar_function(TypePlainVoidStarFunction arg,
        void * argData) {
            {
                std::unique_lock<light_mutex> varLock{ __m_mutex };
                if (__m_quit_) { return; }
                ++__m_functions_count;
            }

            {
                std::unique_lock<light_mutex> /*Ⓛ*/\u24c1{ _m_m_plain_voidstar_functions };
                __m_plain_voidstar_functions.emplace_back(arg,argData);
            }
            __m_cv_functions.notify_all();
    }

private:
    CPLUSPLUS_OBJECT(_PrivateShadowThread)
};

ShadowThread::ShadowThread() {
    auto varThisp=::new(&__m_thisp)
        auto(memory::make_shared<_PrivateShadowThread>());
    (*varThisp)->start();
}

ShadowThread::~ShadowThread() {
    thisp()->quit();
    thisp().~shared_ptr();
}

std::thread::id ShadowThread::getThreadID()const {
    return thisp()->__m_thread.get_id();
}

std::shared_ptr<ShadowThread::_PrivateShadowThread> & ShadowThread::thisp() {
    return (std::shared_ptr<ShadowThread::_PrivateShadowThread> &)(__m_thisp);
}

std::shared_ptr<const ShadowThread::_PrivateShadowThread> & ShadowThread::thisp()const {
    return (std::shared_ptr<const ShadowThread::_PrivateShadowThread> &)(__m_thisp);
}

void ShadowThread::_p_run_plain_function(TypePlainFunction arg) {
    if (arg==nullptr) { return; }
    thisp()->run_plain_function(arg);
}

void ShadowThread::_p_run_std_function(TypeStdFunction arg) {
    if (false==bool(arg)) { return; }
    thisp()->_p_run_std_function(std::move(arg));
}

void ShadowThread::_p_run_plain_voidstar_function(
    TypePlainVoidStarFunction arg,void * argData) {
    if (arg==nullptr) { return; }
    thisp()->_p_run_plain_voidstar_function(arg,argData);
}

void ShadowThread::_p_run_plain_constvoidstar_function(
    TypePlainConstVoidStarFunction arg,const void * argData) {
    if (arg==nullptr) { return; }
    thisp()->_p_run_plain_constvoidstar_function(arg,argData);
}

void ShadowThread::quit() {
    thisp()->quit();
}

}/*thread*/






