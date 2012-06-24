/****************************************************************************
** Meta object code from reading C++ file 'qhbotusermanager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qhbotusermanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhbotusermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QHBotUserManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      51,   34,   17,   17, 0x0a,
      91,   87,   17,   17, 0x0a,
     116,  111,   17,   17, 0x0a,
     139,   87,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QHBotUserManager[] = {
    "QHBotUserManager\0\0populateUsers()\0"
    "bareJid,resource\0updateUserPresence(QString,QString)\0"
    "jid\0inviteUser(QString)\0user\0"
    "removeUser(QHBotUser&)\0removeUser(QString)\0"
};

void QHBotUserManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QHBotUserManager *_t = static_cast<QHBotUserManager *>(_o);
        switch (_id) {
        case 0: _t->populateUsers(); break;
        case 1: _t->updateUserPresence((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->inviteUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->removeUser((*reinterpret_cast< QHBotUser(*)>(_a[1]))); break;
        case 4: _t->removeUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QHBotUserManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QHBotUserManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QHBotUserManager,
      qt_meta_data_QHBotUserManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QHBotUserManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QHBotUserManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QHBotUserManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QHBotUserManager))
        return static_cast<void*>(const_cast< QHBotUserManager*>(this));
    return QObject::qt_metacast(_clname);
}

int QHBotUserManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
