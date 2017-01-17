#include "../gumbo.h"
#include "../../cplusplus_basic.hpp"
#include <list>
#include <string>

namespace gumbo {

typedef std::basic_string<char,std::char_traits<char>,memory::Allocator<char>> string;
typedef std::list<string,memory::Allocator<string>> string_list;

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT GumboOptions * defaultOptions();
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT string_list getAllJavaScript(const char*,const char*);

}/*gumbo*/

