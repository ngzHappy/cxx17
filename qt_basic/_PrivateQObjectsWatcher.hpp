#ifndef QObjectsWatcher_HPP_0x99811
#define QObjectsWatcher_HPP_0x99811

#include <set>
#include <atomic>
#include <memory>
#include <QtCore/qobject.h>
#include "qt_basic_global.hpp"
#include <thread/SpinMutex.hpp>

class QObjectsWatcher;
class _PrivateQObjectsWatcher : public QObject {
    Q_OBJECT
public:
    using light_mutex=thread::SpinMutex;
    _PrivateQObjectsWatcher(QObjectsWatcher *);
    virtual ~_PrivateQObjectsWatcher();
    class ObjectItem {
    public:
        QObject * objectData;
        QMetaObject::Connection connectData;
        ObjectItem(QObject * a,const QMetaObject::Connection & b):
            objectData(a),connectData(b) {}
        ObjectItem(const QMetaObject::Connection & b,QObject * a):
            objectData(a),connectData(b) {}
        ObjectItem():objectData(nullptr) {}
        friend bool operator<(const ObjectItem &l,const ObjectItem &r) {
            return l.objectData<r.objectData;
        }
        friend bool operator<(const ObjectItem &l,const QObject *r) {
            return l.objectData<r;
        }
        friend bool operator<(const QObject *l,const ObjectItem &r) {
            return l<r.objectData;
        }
        class Less {
        public:
            class is_transparent {};
            template<typename L,typename R>
            bool operator()(const L &l,const R &r)const {
                return l<r;
            }
        };
    };
    std::atomic<bool> isQuit{ false };
    std::atomic<bool> isDeleteOnFinished{ true };
    QObjectsWatcher * super;
    std::set<ObjectItem,ObjectItem::Less,memory::Allocator<ObjectItem>> objectItems;
    std::shared_ptr<light_mutex> objectItemsMutex;
    class LockerType {
        std::shared_ptr<light_mutex> _data;
        std::unique_lock<light_mutex> _lock_data;
    public:
        LockerType(const std::shared_ptr<light_mutex> & arg):_data(arg),
            _lock_data(*arg) {
        }
    };
    auto getObjectItemsLock() { return LockerType{ objectItemsMutex }; }
public:
    Q_SLOT void quit();
    Q_SLOT void add(QObject *);
    Q_SLOT void remove(QObject *);
private:
    void do_quit();
private:
    CPLUSPLUS_OBJECT(_PrivateQObjectsWatcher)
};

#endif // QObjectsWatcher_HPP



