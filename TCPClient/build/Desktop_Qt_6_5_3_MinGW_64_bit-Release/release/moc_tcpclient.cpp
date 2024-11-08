/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tcpclient.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTCPClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTCPClientENDCLASS = QtMocHelpers::stringData(
    "TCPClient",
    "showConnect",
    "",
    "onDisconnected",
    "onError",
    "QAbstractSocket::SocketError",
    "error",
    "recvMsg",
    "on_connect_pb_clicked",
    "on_login_pb_clicked",
    "on_regist_pb_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTCPClientENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[10];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[8];
    char stringdata5[29];
    char stringdata6[6];
    char stringdata7[8];
    char stringdata8[22];
    char stringdata9[20];
    char stringdata10[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTCPClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTCPClientENDCLASS_t qt_meta_stringdata_CLASSTCPClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "TCPClient"
        QT_MOC_LITERAL(10, 11),  // "showConnect"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 14),  // "onDisconnected"
        QT_MOC_LITERAL(38, 7),  // "onError"
        QT_MOC_LITERAL(46, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(75, 5),  // "error"
        QT_MOC_LITERAL(81, 7),  // "recvMsg"
        QT_MOC_LITERAL(89, 21),  // "on_connect_pb_clicked"
        QT_MOC_LITERAL(111, 19),  // "on_login_pb_clicked"
        QT_MOC_LITERAL(131, 20)   // "on_regist_pb_clicked"
    },
    "TCPClient",
    "showConnect",
    "",
    "onDisconnected",
    "onError",
    "QAbstractSocket::SocketError",
    "error",
    "recvMsg",
    "on_connect_pb_clicked",
    "on_login_pb_clicked",
    "on_regist_pb_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTCPClientENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x0a,    1 /* Public */,
       3,    0,   57,    2, 0x0a,    2 /* Public */,
       4,    1,   58,    2, 0x0a,    3 /* Public */,
       7,    0,   61,    2, 0x0a,    5 /* Public */,
       8,    0,   62,    2, 0x0a,    6 /* Public */,
       9,    0,   63,    2, 0x08,    7 /* Private */,
      10,    0,   64,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TCPClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSTCPClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTCPClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTCPClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TCPClient, std::true_type>,
        // method 'showConnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'recvMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_connect_pb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_login_pb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_regist_pb_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TCPClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCPClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showConnect(); break;
        case 1: _t->onDisconnected(); break;
        case 2: _t->onError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 3: _t->recvMsg(); break;
        case 4: _t->on_connect_pb_clicked(); break;
        case 5: _t->on_login_pb_clicked(); break;
        case 6: _t->on_regist_pb_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject *TCPClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTCPClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TCPClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
