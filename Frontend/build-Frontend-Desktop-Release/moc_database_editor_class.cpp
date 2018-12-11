/****************************************************************************
** Meta object code from reading C++ file 'database_editor_class.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Framework-for-analysis-and-automatic-code-generation-of-Clock-Syncronization-Algorithmus/database_editor_class.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database_editor_class.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Database_Editor_Class_t {
    QByteArrayData data[14];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Database_Editor_Class_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Database_Editor_Class_t qt_meta_stringdata_Database_Editor_Class = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Database_Editor_Class"
QT_MOC_LITERAL(1, 22, 26), // "on_tableWidget_cellClicked"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 3), // "row"
QT_MOC_LITERAL(4, 54, 6), // "column"
QT_MOC_LITERAL(5, 61, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(6, 93, 4), // "arg1"
QT_MOC_LITERAL(7, 98, 24), // "on_init_database_clicked"
QT_MOC_LITERAL(8, 123, 25), // "on_add_db_element_clicked"
QT_MOC_LITERAL(9, 149, 28), // "on_delete_db_element_clicked"
QT_MOC_LITERAL(10, 178, 28), // "on_update_db_element_clicked"
QT_MOC_LITERAL(11, 207, 15), // "on_load_clicked"
QT_MOC_LITERAL(12, 223, 15), // "reload_database"
QT_MOC_LITERAL(13, 239, 15) // "on_copy_clicked"

    },
    "Database_Editor_Class\0on_tableWidget_cellClicked\0"
    "\0row\0column\0on_comboBox_currentIndexChanged\0"
    "arg1\0on_init_database_clicked\0"
    "on_add_db_element_clicked\0"
    "on_delete_db_element_clicked\0"
    "on_update_db_element_clicked\0"
    "on_load_clicked\0reload_database\0"
    "on_copy_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Database_Editor_Class[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x08 /* Private */,
       5,    1,   64,    2, 0x08 /* Private */,
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,
      12,    0,   72,    2, 0x08 /* Private */,
      13,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Database_Editor_Class::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Database_Editor_Class *_t = static_cast<Database_Editor_Class *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_tableWidget_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_init_database_clicked(); break;
        case 3: _t->on_add_db_element_clicked(); break;
        case 4: _t->on_delete_db_element_clicked(); break;
        case 5: _t->on_update_db_element_clicked(); break;
        case 6: _t->on_load_clicked(); break;
        case 7: _t->reload_database(); break;
        case 8: _t->on_copy_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Database_Editor_Class::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Database_Editor_Class.data,
      qt_meta_data_Database_Editor_Class,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Database_Editor_Class::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Database_Editor_Class::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Database_Editor_Class.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Database_Editor_Class::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
