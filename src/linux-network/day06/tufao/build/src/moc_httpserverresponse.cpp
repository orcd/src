/****************************************************************************
** Meta object code from reading C++ file 'httpserverresponse.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/httpserverresponse.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpserverresponse.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tufao__HttpServerResponse_t {
    QByteArrayData data[17];
    char stringdata[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Tufao__HttpServerResponse_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Tufao__HttpServerResponse_t qt_meta_stringdata_Tufao__HttpServerResponse = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 8),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 13),
QT_MOC_LITERAL(4, 50, 9),
QT_MOC_LITERAL(5, 60, 10),
QT_MOC_LITERAL(6, 71, 12),
QT_MOC_LITERAL(7, 84, 7),
QT_MOC_LITERAL(8, 92, 7),
QT_MOC_LITERAL(9, 100, 18),
QT_MOC_LITERAL(10, 119, 5),
QT_MOC_LITERAL(11, 125, 5),
QT_MOC_LITERAL(12, 131, 11),
QT_MOC_LITERAL(13, 143, 10),
QT_MOC_LITERAL(14, 154, 10),
QT_MOC_LITERAL(15, 165, 11),
QT_MOC_LITERAL(16, 177, 3)
    },
    "Tufao::HttpServerResponse\0finished\0\0"
    "writeContinue\0writeHead\0statusCode\0"
    "reasonPhrase\0Headers\0headers\0"
    "HttpResponseStatus\0write\0chunk\0"
    "addTrailers\0addTrailer\0headerName\0"
    "headerValue\0end\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tufao__HttpServerResponse[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x0a,
       4,    3,   81,    2, 0x0a,
       4,    2,   88,    2, 0x0a,
       4,    3,   93,    2, 0x0a,
       4,    2,  100,    2, 0x0a,
       4,    2,  105,    2, 0x0a,
       4,    1,  110,    2, 0x0a,
      10,    1,  113,    2, 0x0a,
      12,    1,  116,    2, 0x0a,
      13,    2,  119,    2, 0x0a,
      16,    1,  124,    2, 0x0a,
      16,    0,  127,    2, 0x2a,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Int, QMetaType::QByteArray, 0x80000000 | 7,    5,    6,    8,
    QMetaType::Bool, QMetaType::Int, QMetaType::QByteArray,    5,    6,
    QMetaType::Bool, 0x80000000 | 9, QMetaType::QByteArray, 0x80000000 | 7,    5,    6,    8,
    QMetaType::Bool, 0x80000000 | 9, QMetaType::QByteArray,    5,    6,
    QMetaType::Bool, 0x80000000 | 9, 0x80000000 | 7,    5,    8,
    QMetaType::Bool, 0x80000000 | 9,    5,
    QMetaType::Bool, QMetaType::QByteArray,   11,
    QMetaType::Bool, 0x80000000 | 7,    8,
    QMetaType::Bool, QMetaType::QByteArray, QMetaType::QByteArray,   14,   15,
    QMetaType::Bool, QMetaType::QByteArray,   11,
    QMetaType::Bool,

       0        // eod
};

void Tufao::HttpServerResponse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpServerResponse *_t = static_cast<HttpServerResponse *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: { bool _r = _t->writeContinue();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->writeHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const Headers(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->writeHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->writeHead((*reinterpret_cast< HttpResponseStatus(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const Headers(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->writeHead((*reinterpret_cast< HttpResponseStatus(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->writeHead((*reinterpret_cast< HttpResponseStatus(*)>(_a[1])),(*reinterpret_cast< const Headers(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->writeHead((*reinterpret_cast< HttpResponseStatus(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->write((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->addTrailers((*reinterpret_cast< const Headers(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->addTrailer((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->end((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->end();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HttpServerResponse::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpServerResponse::finished)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Tufao::HttpServerResponse::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tufao__HttpServerResponse.data,
      qt_meta_data_Tufao__HttpServerResponse,  qt_static_metacall, 0, 0}
};


const QMetaObject *Tufao::HttpServerResponse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tufao::HttpServerResponse::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tufao__HttpServerResponse.stringdata))
        return static_cast<void*>(const_cast< HttpServerResponse*>(this));
    return QObject::qt_metacast(_clname);
}

int Tufao::HttpServerResponse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Tufao::HttpServerResponse::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
