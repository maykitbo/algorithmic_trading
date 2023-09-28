/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../view/main_window/main_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_s21__MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_s21__MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_s21__MainWindow_t qt_meta_stringdata_s21__MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "s21::MainWindow"
QT_MOC_LITERAL(1, 16, 23), // "InterpolationHideButton"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 24), // "InterpolationClearButton"
QT_MOC_LITERAL(4, 66, 23), // "InterpolationFileButton"
QT_MOC_LITERAL(5, 90, 17), // "CubicSplineButton"
QT_MOC_LITERAL(6, 108, 22), // "NewtonPolynomialButton"
QT_MOC_LITERAL(7, 131, 24), // "InterpolationGraphRemove"
QT_MOC_LITERAL(8, 156, 10), // "GraphName*"
QT_MOC_LITERAL(9, 167, 4), // "name"
QT_MOC_LITERAL(10, 172, 23), // "InterpolationCalcButton"
QT_MOC_LITERAL(11, 196, 23), // "ApproximationHideButton"
QT_MOC_LITERAL(12, 220, 24), // "ApproximationClearButton"
QT_MOC_LITERAL(13, 245, 23), // "ApproximationFileButton"
QT_MOC_LITERAL(14, 269, 17), // "ApproximateButton"
QT_MOC_LITERAL(15, 287, 24) // "ApproximationGraphRemove"

    },
    "s21::MainWindow\0InterpolationHideButton\0"
    "\0InterpolationClearButton\0"
    "InterpolationFileButton\0CubicSplineButton\0"
    "NewtonPolynomialButton\0InterpolationGraphRemove\0"
    "GraphName*\0name\0InterpolationCalcButton\0"
    "ApproximationHideButton\0"
    "ApproximationClearButton\0"
    "ApproximationFileButton\0ApproximateButton\0"
    "ApproximationGraphRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_s21__MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    1,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void s21::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->InterpolationHideButton(); break;
        case 1: _t->InterpolationClearButton(); break;
        case 2: _t->InterpolationFileButton(); break;
        case 3: _t->CubicSplineButton(); break;
        case 4: _t->NewtonPolynomialButton(); break;
        case 5: _t->InterpolationGraphRemove((*reinterpret_cast< GraphName*(*)>(_a[1]))); break;
        case 6: _t->InterpolationCalcButton(); break;
        case 7: _t->ApproximationHideButton(); break;
        case 8: _t->ApproximationClearButton(); break;
        case 9: _t->ApproximationFileButton(); break;
        case 10: _t->ApproximateButton(); break;
        case 11: _t->ApproximationGraphRemove((*reinterpret_cast< GraphName*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject s21::MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_s21__MainWindow.data,
    qt_meta_data_s21__MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *s21::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *s21::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_s21__MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int s21::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
