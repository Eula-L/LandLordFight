/****************************************************************************
** Meta object code from reading C++ file 'maindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LandLordFight/maindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainDialog_t {
    QByteArrayData data[17];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainDialog_t qt_meta_stringdata_MainDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainDialog"
QT_MOC_LITERAL(1, 11, 24), // "on_pb_quickStart_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 20), // "on_pb_goHome_clicked"
QT_MOC_LITERAL(4, 58, 20), // "on_pb_next_2_clicked"
QT_MOC_LITERAL(5, 79, 18), // "on_pb_test_clicked"
QT_MOC_LITERAL(6, 98, 18), // "slot_setBackGround"
QT_MOC_LITERAL(7, 117, 17), // "slot_startOneGame"
QT_MOC_LITERAL(8, 135, 23), // "slot_refreshAllCardList"
QT_MOC_LITERAL(9, 159, 22), // "on_pb_playCard_clicked"
QT_MOC_LITERAL(10, 182, 28), // "slot_deleteAllPlayerOutCards"
QT_MOC_LITERAL(11, 211, 28), // "slot_deleteOnePlayerOutCards"
QT_MOC_LITERAL(12, 240, 6), // "player"
QT_MOC_LITERAL(13, 247, 18), // "slot_showPlayCards"
QT_MOC_LITERAL(14, 266, 4), // "flag"
QT_MOC_LITERAL(15, 271, 17), // "slot_showCallLord"
QT_MOC_LITERAL(16, 289, 18) // "on_pb_pass_clicked"

    },
    "MainDialog\0on_pb_quickStart_clicked\0"
    "\0on_pb_goHome_clicked\0on_pb_next_2_clicked\0"
    "on_pb_test_clicked\0slot_setBackGround\0"
    "slot_startOneGame\0slot_refreshAllCardList\0"
    "on_pb_playCard_clicked\0"
    "slot_deleteAllPlayerOutCards\0"
    "slot_deleteOnePlayerOutCards\0player\0"
    "slot_showPlayCards\0flag\0slot_showCallLord\0"
    "on_pb_pass_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    1,   88,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      15,    1,   94,    2, 0x08 /* Private */,
      16,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void MainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pb_quickStart_clicked(); break;
        case 1: _t->on_pb_goHome_clicked(); break;
        case 2: _t->on_pb_next_2_clicked(); break;
        case 3: _t->on_pb_test_clicked(); break;
        case 4: _t->slot_setBackGround(); break;
        case 5: _t->slot_startOneGame(); break;
        case 6: _t->slot_refreshAllCardList(); break;
        case 7: _t->on_pb_playCard_clicked(); break;
        case 8: _t->slot_deleteAllPlayerOutCards(); break;
        case 9: _t->slot_deleteOnePlayerOutCards((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_showPlayCards((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->slot_showCallLord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_pb_pass_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_MainDialog.data,
    qt_meta_data_MainDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
