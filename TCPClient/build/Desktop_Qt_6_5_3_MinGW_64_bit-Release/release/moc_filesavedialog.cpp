/****************************************************************************
** Meta object code from reading C++ file 'filesavedialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../filesavedialog.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filesavedialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSFileSaveDialogENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSFileSaveDialogENDCLASS = QtMocHelpers::stringData(
    "FileSaveDialog",
    "on_returnPB_clicked",
    "",
    "on_FileInfoTreeW_doubleClicked",
    "QModelIndex",
    "index",
    "on_createDirPB_clicked",
    "on_savePB_clicked",
    "on_cancelPB_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFileSaveDialogENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[15];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[31];
    char stringdata4[12];
    char stringdata5[6];
    char stringdata6[23];
    char stringdata7[18];
    char stringdata8[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFileSaveDialogENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFileSaveDialogENDCLASS_t qt_meta_stringdata_CLASSFileSaveDialogENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "FileSaveDialog"
        QT_MOC_LITERAL(15, 19),  // "on_returnPB_clicked"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 30),  // "on_FileInfoTreeW_doubleClicked"
        QT_MOC_LITERAL(67, 11),  // "QModelIndex"
        QT_MOC_LITERAL(79, 5),  // "index"
        QT_MOC_LITERAL(85, 22),  // "on_createDirPB_clicked"
        QT_MOC_LITERAL(108, 17),  // "on_savePB_clicked"
        QT_MOC_LITERAL(126, 19)   // "on_cancelPB_clicked"
    },
    "FileSaveDialog",
    "on_returnPB_clicked",
    "",
    "on_FileInfoTreeW_doubleClicked",
    "QModelIndex",
    "index",
    "on_createDirPB_clicked",
    "on_savePB_clicked",
    "on_cancelPB_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFileSaveDialogENDCLASS[] = {

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
       3,    1,   45,    2, 0x08,    2 /* Private */,
       6,    0,   48,    2, 0x08,    4 /* Private */,
       7,    0,   49,    2, 0x08,    5 /* Private */,
       8,    0,   50,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FileSaveDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFileSaveDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFileSaveDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFileSaveDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FileSaveDialog, std::true_type>,
        // method 'on_returnPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_FileInfoTreeW_doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_createDirPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_savePB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cancelPB_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FileSaveDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileSaveDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_returnPB_clicked(); break;
        case 1: _t->on_FileInfoTreeW_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 2: _t->on_createDirPB_clicked(); break;
        case 3: _t->on_savePB_clicked(); break;
        case 4: _t->on_cancelPB_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *FileSaveDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileSaveDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFileSaveDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FileSaveDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
