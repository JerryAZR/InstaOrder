/****************************************************************************
** Meta object code from reading C++ file 'jdhelper.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../jdhelper.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jdhelper.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSJDHelperENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSJDHelperENDCLASS = QtMocHelpers::stringData(
    "JDHelper",
    "pageReady",
    "",
    "pageCreated",
    "_on_cookie_add",
    "QNetworkCookie",
    "cookie",
    "_on_page_load",
    "_on_url_change",
    "_order_next_step",
    "url",
    "_reload",
    "_update_manual_config",
    "result"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSJDHelperENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[9];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[15];
    char stringdata5[15];
    char stringdata6[7];
    char stringdata7[14];
    char stringdata8[15];
    char stringdata9[17];
    char stringdata10[4];
    char stringdata11[8];
    char stringdata12[22];
    char stringdata13[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSJDHelperENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSJDHelperENDCLASS_t qt_meta_stringdata_CLASSJDHelperENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "JDHelper"
        QT_MOC_LITERAL(9, 9),  // "pageReady"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 11),  // "pageCreated"
        QT_MOC_LITERAL(32, 14),  // "_on_cookie_add"
        QT_MOC_LITERAL(47, 14),  // "QNetworkCookie"
        QT_MOC_LITERAL(62, 6),  // "cookie"
        QT_MOC_LITERAL(69, 13),  // "_on_page_load"
        QT_MOC_LITERAL(83, 14),  // "_on_url_change"
        QT_MOC_LITERAL(98, 16),  // "_order_next_step"
        QT_MOC_LITERAL(115, 3),  // "url"
        QT_MOC_LITERAL(119, 7),  // "_reload"
        QT_MOC_LITERAL(127, 21),  // "_update_manual_config"
        QT_MOC_LITERAL(149, 6)   // "result"
    },
    "JDHelper",
    "pageReady",
    "",
    "pageCreated",
    "_on_cookie_add",
    "QNetworkCookie",
    "cookie",
    "_on_page_load",
    "_on_url_change",
    "_order_next_step",
    "url",
    "_reload",
    "_update_manual_config",
    "result"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSJDHelperENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   64,    2, 0x0a,    3 /* Public */,
       7,    0,   67,    2, 0x0a,    5 /* Public */,
       8,    0,   68,    2, 0x0a,    6 /* Public */,
       9,    1,   69,    2, 0x0a,    7 /* Public */,
      11,    0,   72,    2, 0x0a,    9 /* Public */,
      12,    1,   73,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QUrl,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject JDHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<OrderHelper::staticMetaObject>(),
    qt_meta_stringdata_CLASSJDHelperENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSJDHelperENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSJDHelperENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<JDHelper, std::true_type>,
        // method 'pageReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pageCreated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method '_on_cookie_add'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QNetworkCookie &, std::false_type>,
        // method '_on_page_load'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method '_on_url_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method '_order_next_step'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>,
        // method '_reload'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method '_update_manual_config'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void JDHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JDHelper *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pageReady(); break;
        case 1: _t->pageCreated(); break;
        case 2: _t->_on_cookie_add((*reinterpret_cast< std::add_pointer_t<QNetworkCookie>>(_a[1]))); break;
        case 3: _t->_on_page_load(); break;
        case 4: _t->_on_url_change(); break;
        case 5: _t->_order_next_step((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 6: _t->_reload(); break;
        case 7: _t->_update_manual_config((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (JDHelper::*)();
            if (_t _q_method = &JDHelper::pageReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (JDHelper::*)();
            if (_t _q_method = &JDHelper::pageCreated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *JDHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JDHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSJDHelperENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return OrderHelper::qt_metacast(_clname);
}

int JDHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OrderHelper::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void JDHelper::pageReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void JDHelper::pageCreated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
