/****************************************************************************
** Meta object code from reading C++ file 'qhbotcommands.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qhbotcommands.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qhbotcommands.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QHBotCommands[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   20,   15,   14, 0x0a,
      48,   20,   15,   14, 0x0a,
      73,   20,   14,   14, 0x08,
      99,   20,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QHBotCommands[] = {
    "QHBotCommands\0\0bool\0msg\0isCommand(QXmppMessage)\0"
    "runCommand(QXmppMessage)\0"
    "runCmdHello(QXmppMessage)\0"
    "runCmdInvite(QXmppMessage)\0"
};

void QHBotCommands::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QHBotCommands *_t = static_cast<QHBotCommands *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->isCommand((*reinterpret_cast< const QXmppMessage(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->runCommand((*reinterpret_cast< const QXmppMessage(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->runCmdHello((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        case 3: _t->runCmdInvite((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QHBotCommands::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QHBotCommands::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QHBotCommands,
      qt_meta_data_QHBotCommands, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QHBotCommands::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QHBotCommands::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QHBotCommands::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QHBotCommands))
        return static_cast<void*>(const_cast< QHBotCommands*>(this));
    return QObject::qt_metacast(_clname);
}

int QHBotCommands::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
