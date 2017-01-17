#ifndef _BOTAN_EXCEPTION_0x19923
#define _BOTAN_EXCEPTION_0x19923

#include <exception>
#include <stdexcept>

//#if defined(_MSC_VER)
//#pragma warning(disable : 4275)
//#endif

inline Botan::Exception::Exception():
    _Super("std::runtime_error") {
}

inline Botan::Exception::Exception(const containers::string &arg) :
    _Super(""){
    _pm_data=memory::make_shared<containers::string>(arg);
}

inline Botan::Exception::Exception(containers::string &&arg) :
    _Super(""){
    _pm_data=memory::make_shared<containers::string>(std::move(arg));
}

inline const char * Botan::Exception::what() const noexcept(true) {
    if (_pm_data) { return reinterpret_cast<
        containers::string *>( _pm_data.get() )->c_str(); }
    return _Super::what();
}

inline Botan::Invalid_Argument::Invalid_Argument() :
    _Super("Invalid_Argument"){
}

inline Botan::Invalid_Argument::Invalid_Argument(const containers::string &arg):
    _Super("") {
    _pm_data=memory::make_shared<containers::string>(arg);
}

inline Botan::Invalid_Argument::Invalid_Argument(containers::string &&arg):
    _Super("") {
    _pm_data=memory::make_shared<containers::string>(std::move(arg));
}

inline const char * Botan::Invalid_Argument::what() const noexcept(true) {
    if (_pm_data) { return reinterpret_cast<
        containers::string *>( _pm_data.get() )->c_str(); }
    return _Super::what();
}

#endif

