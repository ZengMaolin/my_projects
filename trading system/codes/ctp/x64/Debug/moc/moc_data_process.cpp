/****************************************************************************
** Meta object code from reading C++ file 'data_process.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../inc/data_process.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'data_process.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_data_process_t {
    QByteArrayData data[13];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_data_process_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_data_process_t qt_meta_stringdata_data_process = {
    {
QT_MOC_LITERAL(0, 0, 12), // "data_process"
QT_MOC_LITERAL(1, 13, 17), // "send_pair_setting"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "trading_setting"
QT_MOC_LITERAL(4, 48, 17), // "send_history_data"
QT_MOC_LITERAL(5, 66, 23), // "history_position_status"
QT_MOC_LITERAL(6, 90, 18), // "start_data_process"
QT_MOC_LITERAL(7, 109, 12), // "update_event"
QT_MOC_LITERAL(8, 122, 20), // "delete_position_file"
QT_MOC_LITERAL(9, 143, 18), // "sync_position_file"
QT_MOC_LITERAL(10, 162, 15), // "position_status"
QT_MOC_LITERAL(11, 178, 21), // "recieve_setting_value"
QT_MOC_LITERAL(12, 200, 20) // "receive_history_data"

    },
    "data_process\0send_pair_setting\0\0"
    "trading_setting\0send_history_data\0"
    "history_position_status\0start_data_process\0"
    "update_event\0delete_position_file\0"
    "sync_position_file\0position_status\0"
    "recieve_setting_value\0receive_history_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_data_process[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   60,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x0a /* Public */,
       8,    1,   62,    2, 0x0a /* Public */,
       9,    1,   65,    2, 0x0a /* Public */,
      11,    1,   68,    2, 0x0a /* Public */,
      12,    1,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void data_process::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<data_process *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_pair_setting((*reinterpret_cast< trading_setting(*)>(_a[1]))); break;
        case 1: _t->send_history_data((*reinterpret_cast< history_position_status(*)>(_a[1]))); break;
        case 2: _t->start_data_process(); break;
        case 3: _t->update_event(); break;
        case 4: _t->delete_position_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sync_position_file((*reinterpret_cast< position_status(*)>(_a[1]))); break;
        case 6: _t->recieve_setting_value((*reinterpret_cast< trading_setting(*)>(_a[1]))); break;
        case 7: _t->receive_history_data((*reinterpret_cast< history_position_status(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (data_process::*)(trading_setting );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&data_process::send_pair_setting)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (data_process::*)(history_position_status );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&data_process::send_history_data)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject data_process::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_data_process.data,
    qt_meta_data_data_process,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *data_process::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *data_process::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_data_process.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int data_process::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void data_process::send_pair_setting(trading_setting _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void data_process::send_history_data(history_position_status _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
