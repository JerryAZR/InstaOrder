/****************************************************************************
** Meta object code from reading C++ file 'orderhelper.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../orderhelper.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'orderhelper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
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
struct qt_meta_stringdata_CLASSOrderHelperENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSOrderHelperENDCLASS = QtMocHelpers::stringData(
    "OrderHelper",
    "imageReady",
    "",
    "QPixmap*",
    "img",
    "imageSrcReady",
    "src",
    "itemNameReady",
    "name",
    "itemPriceReady",
    "price",
    "itemStatusReady",
    "status",
    "shopNameReady",
    "shop",
    "progressUpdated",
    "progress",
    "qrCodeReady",
    "loggedIn",
    "username",
    "orderFinished",
    "success"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSOrderHelperENDCLASS_t {
    uint offsetsAndSizes[44];
    char stringdata0[12];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[4];
    char stringdata5[14];
    char stringdata6[4];
    char stringdata7[14];
    char stringdata8[5];
    char stringdata9[15];
    char stringdata10[6];
    char stringdata11[16];
    char stringdata12[7];
    char stringdata13[14];
    char stringdata14[5];
    char stringdata15[16];
    char stringdata16[9];
    char stringdata17[12];
    char stringdata18[9];
    char stringdata19[9];
    char stringdata20[14];
    char stringdata21[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSOrderHelperENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSOrderHelperENDCLASS_t qt_meta_stringdata_CLASSOrderHelperENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "OrderHelper"
        QT_MOC_LITERAL(12, 10),  // "imageReady"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 8),  // "QPixmap*"
        QT_MOC_LITERAL(33, 3),  // "img"
        QT_MOC_LITERAL(37, 13),  // "imageSrcReady"
        QT_MOC_LITERAL(51, 3),  // "src"
        QT_MOC_LITERAL(55, 13),  // "itemNameReady"
        QT_MOC_LITERAL(69, 4),  // "name"
        QT_MOC_LITERAL(74, 14),  // "itemPriceReady"
        QT_MOC_LITERAL(89, 5),  // "price"
        QT_MOC_LITERAL(95, 15),  // "itemStatusReady"
        QT_MOC_LITERAL(111, 6),  // "status"
        QT_MOC_LITERAL(118, 13),  // "shopNameReady"
        QT_MOC_LITERAL(132, 4),  // "shop"
        QT_MOC_LITERAL(137, 15),  // "progressUpdated"
        QT_MOC_LITERAL(153, 8),  // "progress"
        QT_MOC_LITERAL(162, 11),  // "qrCodeReady"
        QT_MOC_LITERAL(174, 8),  // "loggedIn"
        QT_MOC_LITERAL(183, 8),  // "username"
        QT_MOC_LITERAL(192, 13),  // "orderFinished"
        QT_MOC_LITERAL(206, 7)   // "success"
    },
    "OrderHelper",
    "imageReady",
    "",
    "QPixmap*",
    "img",
    "imageSrcReady",
    "src",
    "itemNameReady",
    "name",
    "itemPriceReady",
    "price",
    "itemStatusReady",
    "status",
    "shopNameReady",
    "shop",
    "progressUpdated",
    "progress",
    "qrCodeReady",
    "loggedIn",
    "username",
    "orderFinished",
    "success"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSOrderHelperENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       5,    1,   77,    2, 0x06,    3 /* Public */,
       7,    1,   80,    2, 0x06,    5 /* Public */,
       9,    1,   83,    2, 0x06,    7 /* Public */,
      11,    1,   86,    2, 0x06,    9 /* Public */,
      13,    1,   89,    2, 0x06,   11 /* Public */,
      15,    1,   92,    2, 0x06,   13 /* Public */,
      17,    1,   95,    2, 0x06,   15 /* Public */,
      18,    1,   98,    2, 0x06,   17 /* Public */,
      20,    1,  101,    2, 0x06,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::Bool,   21,

       0        // eod
};

Q_CONSTINIT const QMetaObject OrderHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSOrderHelperENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSOrderHelperENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSOrderHelperENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<OrderHelper, std::true_type>,
        // method 'imageReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        // method 'imageSrcReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'itemNameReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'itemPriceReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'itemStatusReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'shopNameReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'progressUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'qrCodeReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        // method 'loggedIn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'orderFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void OrderHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OrderHelper *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->imageReady((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1]))); break;
        case 1: _t->imageSrcReady((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->itemNameReady((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->itemPriceReady((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->itemStatusReady((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->shopNameReady((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->progressUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->qrCodeReady((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1]))); break;
        case 8: _t->loggedIn((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->orderFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OrderHelper::*)(QPixmap * );
            if (_t _q_method = &OrderHelper::imageReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(const QString & );
            if (_t _q_method = &OrderHelper::imageSrcReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(const QString & );
            if (_t _q_method = &OrderHelper::itemNameReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(const QString & );
            if (_t _q_method = &OrderHelper::itemPriceReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(const QString & );
            if (_t _q_method = &OrderHelper::itemStatusReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(const QString & );
            if (_t _q_method = &OrderHelper::shopNameReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(int );
            if (_t _q_method = &OrderHelper::progressUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(QPixmap * );
            if (_t _q_method = &OrderHelper::qrCodeReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(const QString & );
            if (_t _q_method = &OrderHelper::loggedIn; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (OrderHelper::*)(bool );
            if (_t _q_method = &OrderHelper::orderFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *OrderHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OrderHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSOrderHelperENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int OrderHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void OrderHelper::imageReady(QPixmap * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OrderHelper::imageSrcReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OrderHelper::itemNameReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OrderHelper::itemPriceReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OrderHelper::itemStatusReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OrderHelper::shopNameReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void OrderHelper::progressUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void OrderHelper::qrCodeReady(QPixmap * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void OrderHelper::loggedIn(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void OrderHelper::orderFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
