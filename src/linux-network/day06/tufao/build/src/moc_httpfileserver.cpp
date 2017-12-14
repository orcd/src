/****************************************************************************
** Meta object code from reading C++ file 'httpfileserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/httpfileserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpfileserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tufao__HttpFileServer_t {
    QByteArrayData data[7];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Tufao__HttpFileServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Tufao__HttpFileServer_t qt_meta_stringdata_Tufao__HttpFileServer = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 13),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 25),
QT_MOC_LITERAL(4, 63, 7),
QT_MOC_LITERAL(5, 71, 26),
QT_MOC_LITERAL(6, 98, 8)
    },
    "Tufao::HttpFileServer\0handleRequest\0"
    "\0Tufao::HttpServerRequest&\0request\0"
    "Tufao::HttpServerResponse&\0response\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tufao__HttpFileServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void Tufao::HttpFileServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpFileServer *_t = static_cast<HttpFileServer *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->handleRequest((*reinterpret_cast< Tufao::HttpServerRequest(*)>(_a[1])),(*reinterpret_cast< Tufao::HttpServerResponse(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject Tufao::HttpFileServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tufao__HttpFileServer.data,
      qt_meta_data_Tufao__HttpFileServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *Tufao::HttpFileServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tufao::HttpFileServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tufao__HttpFileServer.stringdata))
        return static_cast<void*>(const_cast< HttpFileServer*>(this));
    if (!strcmp(_clname, "AbstractHttpServerRequestHandler"))
        return static_cast< AbstractHttpServerRequestHandler*>(const_cast< HttpFileServer*>(this));
    return QObject::qt_metacast(_clname);
}

int Tufao::HttpFileServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
