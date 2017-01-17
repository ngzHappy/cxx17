#ifndef QT_BASIC_GLOBAL_HPP
#define QT_BASIC_GLOBAL_HPP

#include <QtCore/qglobal.h>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include <cplusplus_basic.hpp>

#if defined(QT_BASIC_LIBRARY)
#  define QT_BASICSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QT_BASICSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QT_BASIC_GLOBAL_HPP
