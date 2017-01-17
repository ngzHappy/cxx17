#ifndef QTBASICLIBRARY_HPP
#define QTBASICLIBRARY_HPP

#include "qt_basic_global.hpp"

class QT_BASICSHARED_EXPORT QtBasicLibrary{
public:
    QtBasicLibrary();
    virtual ~QtBasicLibrary();
private:
    CPLUSPLUS_OBJECT(QtBasicLibrary)
};

#include "QRunOnce.hpp"
#include "QNotifyObject.hpp"
#include "QObjectsWatcher.hpp"
#include "QSingleThreadPool.hpp"
#include "QApplicationWatcher.hpp"

#endif // QTBASICLIBRARY_HPP






