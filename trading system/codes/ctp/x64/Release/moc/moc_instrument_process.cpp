/****************************************************************************
** Meta object code from reading C++ file 'instrument_process.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../inc/instrument_process.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'instrument_process.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_instrument_process_t {
    QByteArrayData data[28];
    char stringdata0[455];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_instrument_process_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_instrument_process_t qt_meta_stringdata_instrument_process = {
    {
QT_MOC_LITERAL(0, 0, 18), // "instrument_process"
QT_MOC_LITERAL(1, 19, 13), // "send_dataToUI"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 14), // "send_ZJdata_ui"
QT_MOC_LITERAL(4, 49, 14), // "send_CCdata_ui"
QT_MOC_LITERAL(5, 64, 14), // "send_WTdata_ui"
QT_MOC_LITERAL(6, 79, 14), // "send_CJdata_ui"
QT_MOC_LITERAL(7, 94, 15), // "send_ctp_status"
QT_MOC_LITERAL(8, 110, 4), // "init"
QT_MOC_LITERAL(9, 115, 15), // "receive_hq_data"
QT_MOC_LITERAL(10, 131, 30), // "CThostFtdcDepthMarketDataField"
QT_MOC_LITERAL(11, 162, 10), // "MarketData"
QT_MOC_LITERAL(12, 173, 17), // "add_hq_instrument"
QT_MOC_LITERAL(13, 191, 20), // "delete_hq_instrument"
QT_MOC_LITERAL(14, 212, 15), // "receive_HY_data"
QT_MOC_LITERAL(15, 228, 15), // "receive_ZJ_data"
QT_MOC_LITERAL(16, 244, 29), // "CThostFtdcTradingAccountField"
QT_MOC_LITERAL(17, 274, 15), // "receive_CC_data"
QT_MOC_LITERAL(18, 290, 31), // "CThostFtdcInvestorPositionField"
QT_MOC_LITERAL(19, 322, 7), // "cc_data"
QT_MOC_LITERAL(20, 330, 15), // "receive_WT_data"
QT_MOC_LITERAL(21, 346, 20), // "CThostFtdcOrderField"
QT_MOC_LITERAL(22, 367, 7), // "wt_data"
QT_MOC_LITERAL(23, 375, 15), // "receive_CJ_data"
QT_MOC_LITERAL(24, 391, 20), // "CThostFtdcTradeField"
QT_MOC_LITERAL(25, 412, 7), // "cj_data"
QT_MOC_LITERAL(26, 420, 21), // "receive_trading_order"
QT_MOC_LITERAL(27, 442, 12) // "update_event"

    },
    "instrument_process\0send_dataToUI\0\0"
    "send_ZJdata_ui\0send_CCdata_ui\0"
    "send_WTdata_ui\0send_CJdata_ui\0"
    "send_ctp_status\0init\0receive_hq_data\0"
    "CThostFtdcDepthMarketDataField\0"
    "MarketData\0add_hq_instrument\0"
    "delete_hq_instrument\0receive_HY_data\0"
    "receive_ZJ_data\0CThostFtdcTradingAccountField\0"
    "receive_CC_data\0CThostFtdcInvestorPositionField\0"
    "cc_data\0receive_WT_data\0CThostFtdcOrderField\0"
    "wt_data\0receive_CJ_data\0CThostFtdcTradeField\0"
    "cj_data\0receive_trading_order\0"
    "update_event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_instrument_process[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       3,    1,  102,    2, 0x06 /* Public */,
       4,    1,  105,    2, 0x06 /* Public */,
       5,    1,  108,    2, 0x06 /* Public */,
       6,    1,  111,    2, 0x06 /* Public */,
       7,    1,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  117,    2, 0x0a /* Public */,
       9,    1,  120,    2, 0x0a /* Public */,
      12,    1,  123,    2, 0x0a /* Public */,
      13,    1,  126,    2, 0x0a /* Public */,
      14,    1,  129,    2, 0x0a /* Public */,
      15,    1,  132,    2, 0x0a /* Public */,
      17,    1,  135,    2, 0x0a /* Public */,
      20,    1,  138,    2, 0x0a /* Public */,
      23,    1,  141,    2, 0x0a /* Public */,
      26,    1,  144,    2, 0x0a /* Public */,
      27,    0,  147,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QStringList,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void,

       0        // eod
};

void instrument_process::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<instrument_process *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_dataToUI((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->send_ZJdata_ui((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->send_CCdata_ui((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->send_WTdata_ui((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->send_CJdata_ui((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->send_ctp_status((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 6: _t->init((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->receive_hq_data((*reinterpret_cast< CThostFtdcDepthMarketDataField(*)>(_a[1]))); break;
        case 8: _t->add_hq_instrument((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->delete_hq_instrument((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->receive_HY_data((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->receive_ZJ_data((*reinterpret_cast< CThostFtdcTradingAccountField(*)>(_a[1]))); break;
        case 12: _t->receive_CC_data((*reinterpret_cast< CThostFtdcInvestorPositionField(*)>(_a[1]))); break;
        case 13: _t->receive_WT_data((*reinterpret_cast< CThostFtdcOrderField(*)>(_a[1]))); break;
        case 14: _t->receive_CJ_data((*reinterpret_cast< CThostFtdcTradeField(*)>(_a[1]))); break;
        case 15: _t->receive_trading_order((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 16: _t->update_event(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (instrument_process::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&instrument_process::send_dataToUI)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (instrument_process::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&instrument_process::send_ZJdata_ui)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (instrument_process::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&instrument_process::send_CCdata_ui)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (instrument_process::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&instrument_process::send_WTdata_ui)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (instrument_process::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&instrument_process::send_CJdata_ui)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (instrument_process::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&instrument_process::send_ctp_status)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject instrument_process::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_instrument_process.data,
    qt_meta_data_instrument_process,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *instrument_process::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *instrument_process::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_instrument_process.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int instrument_process::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void instrument_process::send_dataToUI(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void instrument_process::send_ZJdata_ui(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void instrument_process::send_CCdata_ui(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void instrument_process::send_WTdata_ui(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void instrument_process::send_CJdata_ui(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void instrument_process::send_ctp_status(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
