/****************************************************************************
** Meta object code from reading C++ file 'AppInstallerWatch.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/AppInstallerWatch/AppInstallerWatch.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppInstallerWatch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AppInstallerWatch[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      38,   19,   18,   18, 0x05,
      70,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AppInstallerWatch[] = {
    "AppInstallerWatch\0\0appName,thisAppMap\0"
    "addThisApp(QString,QVariantMap)\0"
    "initDone()\0onPpsFileReady(QVariantMap)\0"
};

void AppInstallerWatch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AppInstallerWatch *_t = static_cast<AppInstallerWatch *>(_o);
        switch (_id) {
        case 0: _t->addThisApp((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2]))); break;
        case 1: _t->initDone(); break;
        case 2: _t->onPpsFileReady((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AppInstallerWatch::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AppInstallerWatch::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AppInstallerWatch,
      qt_meta_data_AppInstallerWatch, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AppInstallerWatch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AppInstallerWatch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AppInstallerWatch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AppInstallerWatch))
        return static_cast<void*>(const_cast< AppInstallerWatch*>(this));
    return QObject::qt_metacast(_clname);
}

int AppInstallerWatch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AppInstallerWatch::addThisApp(const QString & _t1, const QVariantMap & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AppInstallerWatch::initDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
