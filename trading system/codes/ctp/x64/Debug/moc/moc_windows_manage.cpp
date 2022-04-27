/****************************************************************************
** Meta object code from reading C++ file 'windows_manage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../inc/windows_manage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windows_manage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_windows_manage_t {
    QByteArrayData data[13];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_windows_manage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_windows_manage_t qt_meta_stringdata_windows_manage = {
    {
QT_MOC_LITERAL(0, 0, 14), // "windows_manage"
QT_MOC_LITERAL(1, 15, 21), // "send_ins_process_init"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "mode"
QT_MOC_LITERAL(4, 43, 22), // "send_pair_process_init"
QT_MOC_LITERAL(5, 66, 17), // "get_md_login_data"
QT_MOC_LITERAL(6, 84, 15), // "get_md_login_ok"
QT_MOC_LITERAL(7, 100, 17), // "get_td_login_data"
QT_MOC_LITERAL(8, 118, 15), // "get_td_login_ok"
QT_MOC_LITERAL(9, 134, 17), // "init_pair_trading"
QT_MOC_LITERAL(10, 152, 24), // "load_config_pair_trading"
QT_MOC_LITERAL(11, 177, 9), // "file_path"
QT_MOC_LITERAL(12, 187, 19) // "get_pair_quit_event"

    },
    "windows_manage\0send_ins_process_init\0"
    "\0mode\0send_pair_process_init\0"
    "get_md_login_data\0get_md_login_ok\0"
    "get_td_login_data\0get_td_login_ok\0"
    "init_pair_trading\0load_config_pair_trading\0"
    "file_path\0get_pair_quit_event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_windows_manage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   63,    2, 0x0a /* Public */,
       6,    0,   66,    2, 0x0a /* Public */,
       7,    1,   67,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QStringList,    2,

       0        // eod
};

void windows_manage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<windows_manage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_ins_process_init((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->send_pair_process_init(); break;
        case 2: _t->get_md_login_data((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->get_md_login_ok(); break;
        case 4: _t->get_td_login_data((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 5: _t->get_td_login_ok(); break;
        case 6: _t->init_pair_trading((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->load_config_pair_trading((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->get_pair_quit_event((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (windows_manage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&windows_manage::send_ins_process_init)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (windows_manage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&windows_manage::send_pair_process_init)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject windows_manage::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_windows_manage.data,
    qt_meta_data_windows_manage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *windows_manage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *windows_manage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_windows_manage.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int windows_manage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void windows_manage::send_ins_process_init(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void windows_manage::send_pair_process_init()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
