/****************************************************************************
** Meta object code from reading C++ file 'pair_trading.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../inc/pair_trading.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pair_trading.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_edit_position_t {
    QByteArrayData data[5];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_edit_position_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_edit_position_t qt_meta_stringdata_edit_position = {
    {
QT_MOC_LITERAL(0, 0, 13), // "edit_position"
QT_MOC_LITERAL(1, 14, 17), // "send_new_position"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 21), // "position_table_row_UI"
QT_MOC_LITERAL(4, 55, 10) // "save_event"

    },
    "edit_position\0send_new_position\0\0"
    "position_table_row_UI\0save_event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_edit_position[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void edit_position::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<edit_position *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_new_position((*reinterpret_cast< position_table_row_UI(*)>(_a[1]))); break;
        case 1: _t->save_event(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (edit_position::*)(position_table_row_UI );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&edit_position::send_new_position)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject edit_position::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_edit_position.data,
    qt_meta_data_edit_position,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *edit_position::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *edit_position::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_edit_position.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int edit_position::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void edit_position::send_new_position(position_table_row_UI _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_pair_trading_t {
    QByteArrayData data[55];
    char stringdata0[838];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pair_trading_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pair_trading_t qt_meta_stringdata_pair_trading = {
    {
QT_MOC_LITERAL(0, 0, 12), // "pair_trading"
QT_MOC_LITERAL(1, 13, 14), // "send_buy_event"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "QList<double>"
QT_MOC_LITERAL(4, 43, 19), // "send_trading_action"
QT_MOC_LITERAL(5, 63, 20), // "send_position_action"
QT_MOC_LITERAL(6, 84, 16), // "send_close_event"
QT_MOC_LITERAL(7, 101, 15), // "send_close_data"
QT_MOC_LITERAL(8, 117, 18), // "send_position_edit"
QT_MOC_LITERAL(9, 136, 21), // "position_table_row_UI"
QT_MOC_LITERAL(10, 158, 18), // "update_price_value"
QT_MOC_LITERAL(11, 177, 11), // "price_group"
QT_MOC_LITERAL(12, 189, 7), // "price_A"
QT_MOC_LITERAL(13, 197, 7), // "price_B"
QT_MOC_LITERAL(14, 205, 12), // "price_group2"
QT_MOC_LITERAL(15, 218, 11), // "receive_log"
QT_MOC_LITERAL(16, 230, 4), // "data"
QT_MOC_LITERAL(17, 235, 12), // "dataReceived"
QT_MOC_LITERAL(18, 248, 13), // "dataReceived2"
QT_MOC_LITERAL(19, 262, 6), // "value1"
QT_MOC_LITERAL(20, 269, 4), // "max1"
QT_MOC_LITERAL(21, 274, 4), // "min1"
QT_MOC_LITERAL(22, 279, 6), // "value2"
QT_MOC_LITERAL(23, 286, 4), // "max2"
QT_MOC_LITERAL(24, 291, 4), // "min2"
QT_MOC_LITERAL(25, 296, 4), // "time"
QT_MOC_LITERAL(26, 301, 9), // "buy_event"
QT_MOC_LITERAL(27, 311, 29), // "reveive_add_trading_table_row"
QT_MOC_LITERAL(28, 341, 20), // "trading_table_row_UI"
QT_MOC_LITERAL(29, 362, 32), // "reveive_update_trading_table_row"
QT_MOC_LITERAL(30, 395, 3), // "row"
QT_MOC_LITERAL(31, 399, 33), // "reveive_delete_trading_table_..."
QT_MOC_LITERAL(32, 433, 5), // "index"
QT_MOC_LITERAL(33, 439, 14), // "trading_action"
QT_MOC_LITERAL(34, 454, 15), // "position_action"
QT_MOC_LITERAL(35, 470, 30), // "reveive_add_position_table_row"
QT_MOC_LITERAL(36, 501, 33), // "reveive_update_position_table..."
QT_MOC_LITERAL(37, 535, 34), // "reveive_update_position_table..."
QT_MOC_LITERAL(38, 570, 33), // "reveive_delete_position_table..."
QT_MOC_LITERAL(39, 604, 29), // "receive_add_history_table_row"
QT_MOC_LITERAL(40, 634, 23), // "history_position_status"
QT_MOC_LITERAL(41, 658, 17), // "auto_process_show"
QT_MOC_LITERAL(42, 676, 12), // "setting_show"
QT_MOC_LITERAL(43, 689, 14), // "set_spd_models"
QT_MOC_LITERAL(44, 704, 19), // "QStandardItemModel*"
QT_MOC_LITERAL(45, 724, 3), // "spd"
QT_MOC_LITERAL(46, 728, 5), // "spd_A"
QT_MOC_LITERAL(47, 734, 5), // "spd_B"
QT_MOC_LITERAL(48, 740, 14), // "OnPositionMenu"
QT_MOC_LITERAL(49, 755, 2), // "pt"
QT_MOC_LITERAL(50, 758, 17), // "OnPosition_delete"
QT_MOC_LITERAL(51, 776, 15), // "OnPosition_edit"
QT_MOC_LITERAL(52, 792, 25), // "receive_Position_edit_ret"
QT_MOC_LITERAL(53, 818, 11), // "leg_warning"
QT_MOC_LITERAL(54, 830, 7) // "message"

    },
    "pair_trading\0send_buy_event\0\0QList<double>\0"
    "send_trading_action\0send_position_action\0"
    "send_close_event\0send_close_data\0"
    "send_position_edit\0position_table_row_UI\0"
    "update_price_value\0price_group\0price_A\0"
    "price_B\0price_group2\0receive_log\0data\0"
    "dataReceived\0dataReceived2\0value1\0"
    "max1\0min1\0value2\0max2\0min2\0time\0"
    "buy_event\0reveive_add_trading_table_row\0"
    "trading_table_row_UI\0"
    "reveive_update_trading_table_row\0row\0"
    "reveive_delete_trading_table_rows\0"
    "index\0trading_action\0position_action\0"
    "reveive_add_position_table_row\0"
    "reveive_update_position_table_row\0"
    "reveive_update_position_table_days\0"
    "reveive_delete_position_table_row\0"
    "receive_add_history_table_row\0"
    "history_position_status\0auto_process_show\0"
    "setting_show\0set_spd_models\0"
    "QStandardItemModel*\0spd\0spd_A\0spd_B\0"
    "OnPositionMenu\0pt\0OnPosition_delete\0"
    "OnPosition_edit\0receive_Position_edit_ret\0"
    "leg_warning\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pair_trading[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  159,    2, 0x06 /* Public */,
       4,    1,  162,    2, 0x06 /* Public */,
       5,    4,  165,    2, 0x06 /* Public */,
       6,    0,  174,    2, 0x06 /* Public */,
       7,    1,  175,    2, 0x06 /* Public */,
       8,    3,  178,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    4,  185,    2, 0x0a /* Public */,
      15,    1,  194,    2, 0x0a /* Public */,
      17,    7,  197,    2, 0x0a /* Public */,
      18,    7,  212,    2, 0x0a /* Public */,
      26,    0,  227,    2, 0x0a /* Public */,
      27,    1,  228,    2, 0x0a /* Public */,
      29,    1,  231,    2, 0x0a /* Public */,
      31,    1,  234,    2, 0x0a /* Public */,
      33,    0,  237,    2, 0x0a /* Public */,
      34,    0,  238,    2, 0x0a /* Public */,
      35,    1,  239,    2, 0x0a /* Public */,
      36,    1,  242,    2, 0x0a /* Public */,
      37,    1,  245,    2, 0x0a /* Public */,
      38,    1,  248,    2, 0x0a /* Public */,
      39,    1,  251,    2, 0x0a /* Public */,
      41,    0,  254,    2, 0x0a /* Public */,
      42,    0,  255,    2, 0x0a /* Public */,
      43,    3,  256,    2, 0x0a /* Public */,
      48,    1,  263,    2, 0x0a /* Public */,
      50,    0,  266,    2, 0x0a /* Public */,
      51,    0,  267,    2, 0x0a /* Public */,
      52,    1,  268,    2, 0x0a /* Public */,
      53,    1,  271,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, 0x80000000 | 9,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QDateTime,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QDateTime,   19,   20,   21,   22,   23,   24,   25,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,    2,
    QMetaType::Void, 0x80000000 | 28,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   30,
    QMetaType::Void, 0x80000000 | 9,   30,
    QMetaType::Void, 0x80000000 | 9,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, 0x80000000 | 40,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 44, 0x80000000 | 44, 0x80000000 | 44,   45,   46,   47,
    QMetaType::Void, QMetaType::QPoint,   49,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   16,
    QMetaType::Void, QMetaType::QString,   54,

       0        // eod
};

void pair_trading::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<pair_trading *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_buy_event((*reinterpret_cast< QList<double>(*)>(_a[1]))); break;
        case 1: _t->send_trading_action((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->send_position_action((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->send_close_event(); break;
        case 4: _t->send_close_data((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 5: _t->send_position_edit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< position_table_row_UI(*)>(_a[3]))); break;
        case 6: _t->update_price_value((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3])),(*reinterpret_cast< QStringList(*)>(_a[4]))); break;
        case 7: _t->receive_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->dataReceived((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< QDateTime(*)>(_a[7]))); break;
        case 9: _t->dataReceived2((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< QDateTime(*)>(_a[7]))); break;
        case 10: _t->buy_event(); break;
        case 11: _t->reveive_add_trading_table_row((*reinterpret_cast< trading_table_row_UI(*)>(_a[1]))); break;
        case 12: _t->reveive_update_trading_table_row((*reinterpret_cast< trading_table_row_UI(*)>(_a[1]))); break;
        case 13: _t->reveive_delete_trading_table_rows((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->trading_action(); break;
        case 15: _t->position_action(); break;
        case 16: _t->reveive_add_position_table_row((*reinterpret_cast< position_table_row_UI(*)>(_a[1]))); break;
        case 17: _t->reveive_update_position_table_row((*reinterpret_cast< position_table_row_UI(*)>(_a[1]))); break;
        case 18: _t->reveive_update_position_table_days((*reinterpret_cast< position_table_row_UI(*)>(_a[1]))); break;
        case 19: _t->reveive_delete_position_table_row((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->receive_add_history_table_row((*reinterpret_cast< history_position_status(*)>(_a[1]))); break;
        case 21: _t->auto_process_show(); break;
        case 22: _t->setting_show(); break;
        case 23: _t->set_spd_models((*reinterpret_cast< QStandardItemModel*(*)>(_a[1])),(*reinterpret_cast< QStandardItemModel*(*)>(_a[2])),(*reinterpret_cast< QStandardItemModel*(*)>(_a[3]))); break;
        case 24: _t->OnPositionMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 25: _t->OnPosition_delete(); break;
        case 26: _t->OnPosition_edit(); break;
        case 27: _t->receive_Position_edit_ret((*reinterpret_cast< position_table_row_UI(*)>(_a[1]))); break;
        case 28: _t->leg_warning((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (pair_trading::*)(QList<double> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pair_trading::send_buy_event)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (pair_trading::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pair_trading::send_trading_action)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (pair_trading::*)(int , double , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pair_trading::send_position_action)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (pair_trading::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pair_trading::send_close_event)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (pair_trading::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pair_trading::send_close_data)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (pair_trading::*)(int , bool , position_table_row_UI );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pair_trading::send_position_edit)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject pair_trading::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_pair_trading.data,
    qt_meta_data_pair_trading,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *pair_trading::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pair_trading::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pair_trading.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int pair_trading::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void pair_trading::send_buy_event(QList<double> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void pair_trading::send_trading_action(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void pair_trading::send_position_action(int _t1, double _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void pair_trading::send_close_event()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void pair_trading::send_close_data(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void pair_trading::send_position_edit(int _t1, bool _t2, position_table_row_UI _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
