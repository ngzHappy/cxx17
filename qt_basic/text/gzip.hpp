#ifndef __GZIP_TEXT_Q_HPP_0x786354
#define __GZIP_TEXT_Q_HPP_0x786354

#include <QtCore/qbytearray.h>
#include "../qt_basic_global.hpp"

namespace text {

QByteArray QT_BASICSHARED_EXPORT gzip(const char*,const char*);
QByteArray QT_BASICSHARED_EXPORT ungzip(const char *,const char *);

}/**/


#endif



