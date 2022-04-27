/****************************************************************************
** Meta object code from reading C++ file 'tdspi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../inc/tdspi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tdspi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tdspi_t {
    QByteArrayData data[14];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tdspi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tdspi_t qt_meta_stringdata_Tdspi = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Tdspi"
QT_MOC_LITERAL(1, 6, 20), // "td_send_login_status"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "td_send_login_result"
QT_MOC_LITERAL(4, 49, 11), // "send_HYdata"
QT_MOC_LITERAL(5, 61, 11), // "send_ZJdata"
QT_MOC_LITERAL(6, 73, 29), // "CThostFtdcTradingAccountField"
QT_MOC_LITERAL(7, 103, 11), // "send_CCdata"
QT_MOC_LITERAL(8, 115, 31), // "CThostFtdcInvestorPositionField"
QT_MOC_LITERAL(9, 147, 11), // "send_WTdata"
QT_MOC_LITERAL(10, 159, 20), // "CThostFtdcOrderField"
QT_MOC_LITERAL(11, 180, 11), // "send_CJdata"
QT_MOC_LITERAL(12, 192, 20), // "CThostFtdcTradeField"
QT_MOC_LITERAL(13, 213, 10) // "time_event"

    },
    "Tdspi\0td_send_login_status\0\0"
    "td_send_login_result\0send_HYdata\0"
    "send_ZJdata\0CThostFtdcTradingAccountField\0"
    "send_CCdata\0CThostFtdcInvestorPositionField\0"
    "send_WTdata\0CThostFtdcOrderField\0"
    "send_CJdata\0CThostFtdcTradeField\0"
    "time_event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tdspi[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    0,   57,    2, 0x06 /* Public */,
       4,    1,   58,    2, 0x06 /* Public */,
       5,    1,   61,    2, 0x06 /* Public */,
       7,    1,   64,    2, 0x06 /* Public */,
       9,    1,   67,    2, 0x06 /* Public */,
      11,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 12,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Tdspi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tdspi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->td_send_login_status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->td_send_login_result(); break;
        case 2: _t->send_HYdata((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->send_ZJdata((*reinterpret_cast< CThostFtdcTradingAccountField(*)>(_a[1]))); break;
        case 4: _t->send_CCdata((*reinterpret_cast< CThostFtdcInvestorPositionField(*)>(_a[1]))); break;
        case 5: _t->send_WTdata((*reinterpret_cast< CThostFtdcOrderField(*)>(_a[1]))); break;
        case 6: _t->send_CJdata((*reinterpret_cast< CThostFtdcTradeField(*)>(_a[1]))); break;
        case 7: _t->time_event(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Tdspi::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tdspi::td_send_login_status)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Tdspi::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tdspi::td_send_login_result)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Tdspi::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tdspi::send_HYdata)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Tdspi::*)(CThostFtdcTradingAccountField );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tdspi::send_ZJdata)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Tdspi::*)(CThostFtdcInvestorPositionField );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tdspi::send_CCdata)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Tdspi::*)(CThostFtdcOrderField );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tdspi::send_WTdata)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Tdspi::*)(CThostFtdcTradeField );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tdspi::send_CJdata)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Tdspi::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Tdspi.data,
    qt_meta_data_Tdspi,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tdspi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tdspi::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tdspi.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CThostFtdcTraderSpi"))
        return static_cast< CThostFtdcTraderSpi*>(this);
    return QObject::qt_metacast(_clname);
}

int Tdspi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Tdspi::td_send_login_status(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Tdspi::td_send_login_result()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Tdspi::send_HYdata(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Tdspi::send_ZJdata(CThostFtdcTradingAccountField _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Tdspi::send_CCdata(CThostFtdcInvestorPositionField _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Tdspi::send_WTdata(CThostFtdcOrderField _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Tdspi::send_CJdata(CThostFtdcTradeField _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
