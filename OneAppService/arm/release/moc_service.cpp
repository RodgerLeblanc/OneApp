/****************************************************************************
** Meta object code from reading C++ file 'service.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/service.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Service[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      49,    8,    8,    8, 0x08,
      77,    8,    8,    8, 0x08,
     105,    8,    8,    8, 0x08,
     126,    8,    8,    8, 0x08,
     152,    8,    8,    8, 0x08,
     178,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Service[] = {
    "Service\0\0handleInvoke(bb::system::InvokeRequest)\0"
    "onDeviceActiveChanged(bool)\0"
    "onFullscreenPidChanged(int)\0"
    "onNotificationDone()\0onNotificationPublished()\0"
    "onPlusButtonLongPressed()\0"
    "onPowerDownAttempt()\0"
};

void Service::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Service *_t = static_cast<Service *>(_o);
        switch (_id) {
        case 0: _t->handleInvoke((*reinterpret_cast< const bb::system::InvokeRequest(*)>(_a[1]))); break;
        case 1: _t->onDeviceActiveChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: _t->onFullscreenPidChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->onNotificationDone(); break;
        case 4: _t->onNotificationPublished(); break;
        case 5: _t->onPlusButtonLongPressed(); break;
        case 6: _t->onPowerDownAttempt(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Service::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Service::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Service,
      qt_meta_data_Service, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Service::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Service::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Service::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Service))
        return static_cast<void*>(const_cast< Service*>(this));
    return QObject::qt_metacast(_clname);
}

int Service::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
