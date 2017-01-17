#ifndef QNOTIFYOBJECT_HPP
#define QNOTIFYOBJECT_HPP

#include <QtCore/qobject.h>
#include "qt_basic_global.hpp"

class QT_BASICSHARED_EXPORT QNotifyObject :public QObject{
    Q_OBJECT
public:
    QNotifyObject();
    ~QNotifyObject();
public:
    Q_SIGNAL void notify();
private:
    using ___Super=QObject;
    using ___Super::setParent;
    using ___Super::parent;
private:
    CPLUSPLUS_OBJECT(QNotifyObject)
};

#endif // QNOTIFYOBJECT_HPP



