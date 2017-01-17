#include "../Memory.hpp"
#include "../../thread/ShadowThread.hpp"
#include "MemoryApplication.hpp"
#include <atomic>

namespace memory {

namespace {
namespace __cpp_file{
std::atomic<bool> _msp_is_main_quit/*false*/;
std::atomic<bool> _msp_is_main_construct/*false*/;
}/*__cpp_file*/
}/**/

void Application::_p_setMainConstruct() { __cpp_file::_msp_is_main_construct.store(true); }
void Application::_p_clearMainConstruct() { __cpp_file::_msp_is_main_construct.store(false); }
void Application::_p_setMainQuit() { __cpp_file::_msp_is_main_quit.store(true); }
void Application::_p_clearMainQuit() { __cpp_file::_msp_is_main_quit.store(false); }

bool Application::isMainConstruct() { return __cpp_file::_msp_is_main_construct.load(); }
bool Application::isMainQuit() { return __cpp_file::_msp_is_main_quit.load(); }

void Application::_p_main_construct() {
    thread::ShadowThread::instance();
}

void Application::_p_main_destruct() {
    thread::ShadowThread::instance()->quit();
}

}/*memory*/



