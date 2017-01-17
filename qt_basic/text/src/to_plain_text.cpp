#include "../to_plain_text.hpp"
#include "../gzip.hpp"

namespace text {

namespace __private_text_to_plain_text {
namespace {
bool _has_utf8_bom(const char * arg) {
    if (*arg==char(0x00EF)) {
        ++arg;
        if (*arg==char(0x00BB)) {
            ++arg;
            return (*arg==char(0x00BF));
        }
    }
    return false;
}

ToPlainTextAns _remove_bom_and_to_utf8(QByteArray&&arg) {
    if (arg.isEmpty()) { return{}; }
    if (arg.size()<3) { return std::move(arg); }
    if (_has_utf8_bom(arg.cbegin())) {
        arg.remove(0,3);
    }
    return std::move(arg);
}

ToPlainTextAns _remove_bom_and_to_utf8(const char *argBegin,const char *argEnd) {
    if (_has_utf8_bom(argBegin)) {
        argBegin+=3;
        if (argEnd>argBegin) { return{ argBegin,argEnd }; }
        return{ nullptr,nullptr };
    }
    return{ argBegin,argEnd };
}

}/*namespace*/
}/*namespace __private_text_to_plain_text*/

ToPlainTextAns to_plain_text(const char *argBegin,const char *argEnd) {
    auto varLength=argEnd-argBegin;

    if (varLength<=0) {
        return{ nullptr,nullptr };
    }

    if (varLength==1) {
        return{ argBegin,argEnd };
    }

    /*zgip::31 (0x1F)，ID2 = 139(0x8B)*/
    constexpr char __zgip_0=char(0x001F);
    constexpr char __zgip_1=char(0x008B);

    if ((*argBegin==__zgip_0)&&(*(argBegin+1)==__zgip_1)) {
        QByteArray varAns=text::ungzip(argBegin,argEnd);
        return __private_text_to_plain_text::_remove_bom_and_to_utf8(
        std::move(varAns));
    }

    if (varLength==2) {
        return{ argBegin,argEnd };
    }

    return __private_text_to_plain_text::_remove_bom_and_to_utf8(
        argBegin,argEnd);

}

}/**/








