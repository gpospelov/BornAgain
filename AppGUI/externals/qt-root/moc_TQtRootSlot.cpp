/****************************************************************************
** Meta object code from reading C++ file 'TQtRootSlot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inc/TQtRootSlot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TQtRootSlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TQtRootSlot_t {
    QByteArrayData data[10];
    char stringdata[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TQtRootSlot_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TQtRootSlot_t qt_meta_stringdata_TQtRootSlot = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 5),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 5),
QT_MOC_LITERAL(4, 25, 11),
QT_MOC_LITERAL(5, 37, 11),
QT_MOC_LITERAL(6, 49, 9),
QT_MOC_LITERAL(7, 59, 9),
QT_MOC_LITERAL(8, 69, 6),
QT_MOC_LITERAL(9, 76, 16)
    },
    "TQtRootSlot\0Error\0\0error\0ProcessLine\0"
    "const char*\0EndOfLine\0Terminate\0status\0"
    "TerminateAndQuit\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TQtRootSlot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a,
       4,    1,   55,    2, 0x0a,
       6,    0,   58,    2, 0x0a,
       7,    1,   59,    2, 0x0a,
       7,    0,   62,    2, 0x0a,
       9,    0,   63,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TQtRootSlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TQtRootSlot *_t = static_cast<TQtRootSlot *>(_o);
        switch (_id) {
        case 0: _t->Error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ProcessLine((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->ProcessLine((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->EndOfLine(); break;
        case 4: _t->Terminate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->Terminate(); break;
        case 6: _t->TerminateAndQuit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TQtRootSlot::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TQtRootSlot::Error)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TQtRootSlot::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TQtRootSlot.data,
      qt_meta_data_TQtRootSlot,  qt_static_metacall, 0, 0}
};


const QMetaObject *TQtRootSlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TQtRootSlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TQtRootSlot.stringdata))
        return static_cast<void*>(const_cast< TQtRootSlot*>(this));
    return QObject::qt_metacast(_clname);
}

int TQtRootSlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TQtRootSlot::Error(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
