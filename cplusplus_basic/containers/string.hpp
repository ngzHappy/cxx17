#ifndef _string_HASH_CONTAINERS_HPP_0x1222
#define _string_HASH_CONTAINERS_HPP_0x1222

#include <string>
#include "../cplusplus_basic.hpp"

namespace containers {

using string=std::basic_string<char,std::char_traits<char>,memory::Allocator<char>>;
using u16string=std::basic_string<char16_t,std::char_traits<char16_t>,memory::Allocator<char16_t>>;
using u32string=std::basic_string<char32_t,std::char_traits<char32_t>,memory::Allocator<char32_t>>;
using wstring=std::basic_string<wchar_t,std::char_traits<wchar_t>,memory::Allocator<wchar_t>>;

}/*containers*/

#endif

