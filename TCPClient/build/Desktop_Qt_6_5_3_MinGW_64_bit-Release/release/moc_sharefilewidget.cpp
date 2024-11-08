/****************************************************************************
** Meta object code from reading C++ file 'sharefilewidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../sharefilewidget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sharefilewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSShareFileWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSShareFileWidgetENDCLASS = QtMocHelpers::stringData(
    "ShareFileWidget",
    "on_refreshPB_clicked",
    "",
    "on_allSelectPB_clicked",
    "on_cancelSelectPB_clicked",
    "on_okPB_clicked",
    "on_cancelPB_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSShareFileWidgetENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[16];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[26];
    char stringdata5[16];
    char stringdata6[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSShareFileWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSShareFileWidgetENDCLASS_t qt_meta_stringdata_CLASSShareFileWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "ShareFileWidget"
        QT_MOC_LITERAL(16, 20),  // "on_refreshPB_clicked"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 22),  // "on_allSelectPB_clicked"
        QT_MOC_LITERAL(61, 25),  // "on_cancelSelectPB_clicked"
        QT_MOC_LITERAL(87, 15),  // "on_okPB_clicked"
        QT_MOC_LITERAL(103, 19)   // "on_cancelPB_clicked"
    },
    "ShareFileWidget",
    "on_refreshPB_clicked",
    "",
    "on_allSelectPB_clicked",
    "on_cancelSelectPB_clicked",
    "on_okPB_clicked",
    "on_cancelPB_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSShareFileWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    0,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ShareFileWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSShareFileWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSShareFileWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSShareFileWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ShareFileWidget, std::true_type>,
        // method 'on_refreshPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_allSelectPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cancelSelectPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_okPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cancelPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ShareFileWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShareFileWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_refreshPB_clicked(); break;
        case 1: _t->on_allSelectPB_clicked(); break;
        case 2: _t->on_cancelSelectPB_clicked(); break;
        case 3: _t->on_okPB_clicked(); break;
        case 4: _t->on_cancelPB_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ShareFileWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShareFileWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSShareFileWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ShareFileWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
