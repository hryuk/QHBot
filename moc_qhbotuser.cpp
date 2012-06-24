/****************************************************************************
** Meta object code from reading C++ file 'qhbotuser.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qhbotuser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhbotuser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QHBotUser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x0a,
      37,   33,   10,   10, 0x0a,
      62,   53,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QHBotUser[] = {
    "QHBotUser\0\0nick\0setNick(QString)\0jid\0"
    "setJID(QString)\0presence\0"
    "setPresence(QXmppPresence)\0"
};

void QHBotUser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QHBotUser *_t = static_cast<QHBotUser *>(_o);
        switch (_id) {
        case 0: _t->setNick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setJID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setPresence((*reinterpret_cast< QXmppPresence(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QHBotUser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QHBotUser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QHBotUser,
      qt_meta_data_QHBotUser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QHBotUser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QHBotUser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QHBotUser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QHBotUser))
        return static_cast<void*>(const_cast< QHBotUser*>(this));
    return QObject::qt_metacast(_clname);
}

int QHBotUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
