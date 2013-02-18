/****************************************************************************
** Meta object code from reading C++ file 'TQtWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inc/TQtWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TQtWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TQtWidget_t {
    QByteArrayData data[21];
    char stringdata[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TQtWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TQtWidget_t qt_meta_stringdata_TQtWidget = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 13),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 5),
QT_MOC_LITERAL(4, 31, 2),
QT_MOC_LITERAL(5, 34, 18),
QT_MOC_LITERAL(6, 53, 8),
QT_MOC_LITERAL(7, 62, 8),
QT_MOC_LITERAL(8, 71, 5),
QT_MOC_LITERAL(9, 77, 8),
QT_MOC_LITERAL(10, 86, 1),
QT_MOC_LITERAL(11, 88, 2),
QT_MOC_LITERAL(12, 91, 12),
QT_MOC_LITERAL(13, 104, 10),
QT_MOC_LITERAL(14, 115, 7),
QT_MOC_LITERAL(15, 123, 4),
QT_MOC_LITERAL(16, 128, 8),
QT_MOC_LITERAL(17, 137, 11),
QT_MOC_LITERAL(18, 149, 6),
QT_MOC_LITERAL(19, 156, 7),
QT_MOC_LITERAL(20, 164, 9)
    },
    "TQtWidget\0CanvasPainted\0\0Saved\0ok\0"
    "RootEventProcessed\0TObject*\0selected\0"
    "event\0TCanvas*\0c\0cd\0subpadnumber\0"
    "Disconnect\0Refresh\0Save\0fileName\0"
    "const char*\0format\0quality\0RefreshCB\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TQtWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x05,
       3,    1,   85,    2, 0x05,
       5,    3,   88,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      11,    0,   95,    2, 0x0a,
      11,    1,   96,    2, 0x0a,
      13,    0,   99,    2, 0x0a,
      14,    0,  100,    2, 0x0a,
      15,    1,  101,    2, 0x0a,
      15,    1,  104,    2, 0x0a,
      15,    3,  107,    2, 0x0a,
      15,    2,  114,    2, 0x2a,
      15,    3,  119,    2, 0x0a,
      15,    2,  126,    2, 0x2a,
      20,    0,  131,    2, 0x09,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::UInt, 0x80000000 | 9,    7,    8,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   16,
    QMetaType::Bool, 0x80000000 | 17,   16,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 17, QMetaType::Int,   16,   18,   19,
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 17,   16,   18,
    QMetaType::Bool, 0x80000000 | 17, 0x80000000 | 17, QMetaType::Int,   16,   18,   19,
    QMetaType::Bool, 0x80000000 | 17, 0x80000000 | 17,   16,   18,
    QMetaType::Void,

       0        // eod
};

void TQtWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TQtWidget *_t = static_cast<TQtWidget *>(_o);
        switch (_id) {
        case 0: _t->CanvasPainted(); break;
        case 1: _t->Saved((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->RootEventProcessed((*reinterpret_cast< TObject*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< TCanvas*(*)>(_a[3]))); break;
        case 3: _t->cd(); break;
        case 4: _t->cd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->Disconnect(); break;
        case 6: _t->Refresh(); break;
        case 7: { bool _r = _t->Save((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->Save((*reinterpret_cast< const char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->Save((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->Save((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->Save((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->Save((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->RefreshCB(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TQtWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TQtWidget::CanvasPainted)) {
                *result = 0;
            }
        }
        {
            typedef void (TQtWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TQtWidget::Saved)) {
                *result = 1;
            }
        }
        {
            typedef void (TQtWidget::*_t)(TObject * , unsigned int , TCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TQtWidget::RootEventProcessed)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject TQtWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TQtWidget.data,
      qt_meta_data_TQtWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *TQtWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TQtWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TQtWidget.stringdata))
        return static_cast<void*>(const_cast< TQtWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TQtWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TQtWidget::CanvasPainted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TQtWidget::Saved(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TQtWidget::RootEventProcessed(TObject * _t1, unsigned int _t2, TCanvas * _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
