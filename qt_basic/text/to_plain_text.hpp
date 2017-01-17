#ifndef __TOPLAINTEXT_hpp_0x00
#define __TOPLAINTEXT_hpp_0x00

#include <memory>
#include <iterator>
#include "../qt_basic_global.hpp"

namespace text {

class ToPlainTextAns {
    union __Data {
        QByteArray new_data;
        struct {
            const char * old_data_begin;
            const char * old_data_end;
        };
        __Data() {}
        ~__Data() {}
    };
    __Data _m_Data;
    bool _m_is_old_data;
    using __rit=std::reverse_iterator<const char*>;
public:
    ToPlainTextAns();
    ToPlainTextAns(const char*,const char*);
    ToPlainTextAns(const QByteArray&);
    ToPlainTextAns(QByteArray&&);
    const char * data()const;
    int size()const;
    bool isQByteArray()const { return !_m_is_old_data; }
    QByteArray toQByteArray()const;
    operator bool()const;
public:
    const char *begin() const;
    const char *end() const;
    const char *cbegin() const { return begin(); }
    const char *cend() const { return end(); }
    auto rbegin() const { return __rit{ end() }; }
    auto rend() const { return __rit{ begin() }; }
    auto crbegin() const { return __rit{ end() }; }
    auto crend() const { return __rit{ begin() }; }
public:
    ToPlainTextAns(const ToPlainTextAns&);
    ToPlainTextAns(ToPlainTextAns&&);
    ToPlainTextAns&operator=(const ToPlainTextAns&);
    ToPlainTextAns&operator=(ToPlainTextAns&&);
    ~ToPlainTextAns();
};

/*
 * if text begin with utf8-bom remove it
 * if text is gzip ungzip and remove utf8-bom
*/
QT_BASICSHARED_EXPORT ToPlainTextAns to_plain_text(const char *,const char *);

inline ToPlainTextAns::ToPlainTextAns():_m_is_old_data(true) {
    _m_Data.old_data_begin=nullptr;
    _m_Data.old_data_end=nullptr;
}

inline ToPlainTextAns::ToPlainTextAns(const char*argB,const char*argE):_m_is_old_data(true) {
    _m_Data.old_data_begin=argB;
    _m_Data.old_data_end=argE;
}

inline ToPlainTextAns::ToPlainTextAns(const QByteArray&arg):_m_is_old_data(false) {
    ::new (&_m_Data.new_data) QByteArray(arg);
}

inline ToPlainTextAns::ToPlainTextAns(QByteArray&&arg):_m_is_old_data(false) {
    ::new (&_m_Data.new_data) QByteArray(std::move(arg));
}

inline ToPlainTextAns::~ToPlainTextAns() {
    if (_m_is_old_data) { return; }
    _m_Data.new_data.~QByteArray();
}

inline ToPlainTextAns::ToPlainTextAns(const ToPlainTextAns&arg):_m_is_old_data(arg._m_is_old_data) {
    if (_m_is_old_data==false) {
        ::new (&_m_Data.new_data) QByteArray(arg._m_Data.new_data);
    }
    else {
        _m_Data.old_data_begin=arg._m_Data.old_data_begin;
        _m_Data.old_data_end=arg._m_Data.old_data_end;
    }
}

inline ToPlainTextAns::ToPlainTextAns(ToPlainTextAns&&arg):_m_is_old_data(arg._m_is_old_data) {
    if (_m_is_old_data==false) {
        ::new (&_m_Data.new_data) QByteArray(std::move(arg._m_Data.new_data));
    }
    else {
        _m_Data.old_data_begin=arg._m_Data.old_data_begin;
        _m_Data.old_data_end=arg._m_Data.old_data_end;
    }
}

inline ToPlainTextAns&ToPlainTextAns::operator=(const ToPlainTextAns&arg) {
    if (this==&arg) { return *this; }
    if (arg._m_is_old_data) {
        if (this->_m_is_old_data) {
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }
        else {
            this->_m_is_old_data=true;
            this->_m_Data.new_data.~QByteArray();
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }
    }
    else {
        if (this->_m_is_old_data) {
            this->_m_is_old_data=false;
            ::new (&_m_Data.new_data) QByteArray(arg._m_Data.new_data);
        }
        else {
            this->_m_Data.new_data=arg._m_Data.new_data;
        }
    }
    return *this;
}

inline ToPlainTextAns&ToPlainTextAns::operator=(ToPlainTextAns&&arg) {
    if (this==&arg) { return *this; }
    if (arg._m_is_old_data) {
        if (this->_m_is_old_data) {
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }
        else {
            this->_m_is_old_data=true;
            this->_m_Data.new_data.~QByteArray();
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }
    }
    else {
        if (this->_m_is_old_data) {
            this->_m_is_old_data=false;
            ::new (&_m_Data.new_data) QByteArray(std::move(arg._m_Data.new_data));
        }
        else {
            this->_m_Data.new_data=std::move(arg._m_Data.new_data);
        }
    }
    return *this;
}

inline const char * ToPlainTextAns::data()const {
    if (this->_m_is_old_data) { return this->_m_Data.old_data_begin; }
    else {
        return static_cast<const QByteArray&>(_m_Data.new_data).data();
    }
}

inline int ToPlainTextAns::size()const {
    if (this->_m_is_old_data) {
        return static_cast<int>(_m_Data.old_data_end-_m_Data.old_data_begin);
    }
    else {
        return static_cast<const QByteArray&>(_m_Data.new_data).size();
    }
}

inline QByteArray ToPlainTextAns::toQByteArray()const {
    if (isQByteArray()) { return _m_Data.new_data; }
    return QByteArray(data(),
       static_cast<int>(_m_Data.old_data_end-_m_Data.old_data_begin));
}

inline ToPlainTextAns::operator bool()const {
    if (_m_is_old_data) {
        return _m_Data.old_data_end>_m_Data.old_data_begin;
    }
    else {
        return !(_m_Data.new_data.isEmpty());
    }
}

inline const char *ToPlainTextAns::begin() const {
    return _m_is_old_data?_m_Data.old_data_begin:_m_Data.new_data.cbegin();
}

inline const char *ToPlainTextAns::end() const {
    return _m_is_old_data?_m_Data.old_data_end:_m_Data.new_data.cend();
}

}/*text*/

#endif

