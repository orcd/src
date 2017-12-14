/****************************************************************************
** Meta object code from reading C++ file 'httpserverrequest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/httpserverrequest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpserverrequest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tufao__HttpServerRequest_t {
    QByteArrayData data[9];
    char stringdata[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Tufao__HttpServerRequest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Tufao__HttpServerRequest_t qt_meta_stringdata_Tufao__HttpServerRequest = {
    {
QT_MOC_LITERAL(0, 0, 24),
QT_MOC_LITERAL(1, 25, 5),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 4),
QT_MOC_LITERAL(4, 37, 3),
QT_MOC_LITERAL(5, 41, 5),
QT_MOC_LITERAL(6, 47, 7),
QT_MOC_LITERAL(7, 55, 11),
QT_MOC_LITERAL(8, 67, 9)
    },
    "Tufao::HttpServerRequest\0ready\0\0data\0"
    "end\0close\0upgrade\0onReadyRead\0onTimeout\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tufao__HttpServerRequest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06,
       3,    0,   50,    2, 0x06,
       4,    0,   51,    2, 0x06,
       5,    0,   52,    2, 0x06,
       6,    0,   53,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       7,    0,   54,    2, 0x08,
       8,    0,   55,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tufao::HttpServerRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpServerRequest *_t = static_cast<HttpServerRequest *>(_o);
        switch (_id) {
        case 0: _t->ready(); break;
        case 1: _t->data(); break;
        case 2: _t->end(); break;
        case 3: _t->close(); break;
        case 4: _t->upgrade(); break;
        case 5: _t->onReadyRead(); break;
        case 6: _t->onTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HttpServerRequest::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpServerRequest::ready)) {
                *result = 0;
            }
        }
        {
            typedef void (HttpServerRequest::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpServerRequest::data)) {
                *result = 1;
            }
        }
        {
            typedef void (HttpServerRequest::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpServerRequest::end)) {
                *result = 2;
            }
        }
        {
            typedef void (HttpServerRequest::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpServerRequest::close)) {
                *result = 3;
            }
        }
        {
            typedef void (HttpServerRequest::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpServerRequest::upgrade)) {
                *result = 4;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Tufao::HttpServerRequest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tufao__HttpServerRequest.data,
      qt_meta_data_Tufao__HttpServerRequest,  qt_static_metacall, 0, 0}
};


const QMetaObject *Tufao::HttpServerRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tufao::HttpServerRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tufao__HttpServerRequest.stringdata))
        return static_cast<void*>(const_cast< HttpServerRequest*>(this));
    return QObject::qt_metacast(_clname);
}

int Tufao::HttpServerRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Tufao::HttpServerRequest::ready()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Tufao::HttpServerRequest::data()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Tufao::HttpServerRequest::end()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Tufao::HttpServerRequest::close()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Tufao::HttpServerRequest::upgrade()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
