/****************************************************************************
** Meta object code from reading C++ file 'formulaview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../formulaview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formulaview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormulaView_t {
    QByteArrayData data[13];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FormulaView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FormulaView_t qt_meta_stringdata_FormulaView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FormulaView"
QT_MOC_LITERAL(1, 12, 10), // "setFormula"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "setFontSize"
QT_MOC_LITERAL(4, 36, 17), // "setTransformation"
QT_MOC_LITERAL(5, 54, 14), // "transformation"
QT_MOC_LITERAL(6, 69, 8), // "setScale"
QT_MOC_LITERAL(7, 78, 5), // "scale"
QT_MOC_LITERAL(8, 84, 11), // "setRotation"
QT_MOC_LITERAL(9, 96, 13), // "setDrawFrames"
QT_MOC_LITERAL(10, 110, 10), // "drawFrames"
QT_MOC_LITERAL(11, 121, 9), // "setColors"
QT_MOC_LITERAL(12, 131, 6) // "colors"

    },
    "FormulaView\0setFormula\0\0setFontSize\0"
    "setTransformation\0transformation\0"
    "setScale\0scale\0setRotation\0setDrawFrames\0"
    "drawFrames\0setColors\0colors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormulaView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       3,    1,   52,    2, 0x0a /* Public */,
       4,    1,   55,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      11,    1,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   12,

       0        // eod
};

void FormulaView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormulaView *_t = static_cast<FormulaView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFormula((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setFontSize((*reinterpret_cast< const qreal(*)>(_a[1]))); break;
        case 2: _t->setTransformation((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 3: _t->setScale((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 4: _t->setRotation((*reinterpret_cast< const qreal(*)>(_a[1]))); break;
        case 5: _t->setDrawFrames((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 6: _t->setColors((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FormulaView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormulaView.data,
      qt_meta_data_FormulaView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FormulaView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormulaView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FormulaView.stringdata0))
        return static_cast<void*>(const_cast< FormulaView*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormulaView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
