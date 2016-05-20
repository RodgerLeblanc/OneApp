/****************************************************************************
** Meta object code from reading C++ file 'DeviceActive.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/DeviceActive/DeviceActive.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeviceActive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DeviceActive[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   40,   13,   13, 0x08,
     100,   82,   13,   13, 0x08,
     160,   13,   13,   13, 0x08,

 // properties: name, type, flags
     221,  216, 0x01495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

static const char qt_meta_stringdata_DeviceActive[] = {
    "DeviceActive\0\0deviceActiveChanged(bool)\0"
    "newValue\0onBedsideModeActiveChanged(bool)\0"
    "userActivityState\0"
    "onActivityStateChanged(bb::device::UserActivityState::Type)\0"
    "onLockStateChanged(bb::platform::DeviceLockState::Type)\0"
    "bool\0deviceActive\0"
};

void DeviceActive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DeviceActive *_t = static_cast<DeviceActive *>(_o);
        switch (_id) {
        case 0: _t->deviceActiveChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->onBedsideModeActiveChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: _t->onActivityStateChanged((*reinterpret_cast< bb::device::UserActivityState::Type(*)>(_a[1]))); break;
        case 3: _t->onLockStateChanged((*reinterpret_cast< bb::platform::DeviceLockState::Type(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DeviceActive::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DeviceActive::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DeviceActive,
      qt_meta_data_DeviceActive, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DeviceActive::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DeviceActive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DeviceActive::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceActive))
        return static_cast<void*>(const_cast< DeviceActive*>(this));
    return QObject::qt_metacast(_clname);
}

int DeviceActive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = getDeviceActive(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDeviceActive(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceActive::deviceActiveChanged(const bool & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
