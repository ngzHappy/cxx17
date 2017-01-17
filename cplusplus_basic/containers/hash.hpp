#ifndef __HASH_CONTAINERS_HPP_0x1222
#define __HASH_CONTAINERS_HPP_0x1222

#include <utility>
#include <functional>
#include <type_traits>

#if defined(QT_CORE_LIB)
#include <QtCore/qhash.h>
class QUrl;
class QTime;
class QDate;
class QDateTime;
#endif

namespace containers {

#if defined(QT_CORE_LIB)

template<typename T>
class MixHash :public std::hash<T> {};

class QMixHash {
public:
    template<typename T>
    size_t operator()(const T &arg)const {
        return qHash(arg);
    }
};

template<>
class MixHash<QString> :public QMixHash {
};

template<>
class MixHash<QStringRef> :public QMixHash {
};

template<>
class MixHash<QChar> :public QMixHash {
};

template<>
class MixHash<QBitArray> :public QMixHash {
};

template<>
class MixHash<QByteArray> :public QMixHash {
};

template<>
class MixHash<QLatin1String> :public QMixHash {
};

template<>
class MixHash<QTime> :public QMixHash {
};

template<>
class MixHash<QUrl> :public QMixHash {
};

template<>
class MixHash<QDateTime> :public QMixHash {
};

template<>
class MixHash<QDate> :public QMixHash {
};

template<typename T,typename U>
class MixHash<QPair<T,U>> :public QMixHash {
};

#else

template<typename T>
using MixHash=std::hash<T>;

#endif

}/*containers*/

#endif


