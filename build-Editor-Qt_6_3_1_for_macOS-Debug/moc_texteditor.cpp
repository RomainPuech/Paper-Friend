/****************************************************************************
** Meta object code from reading C++ file 'texteditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../TextEditor/texteditor.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'texteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TextEditor_t {
    const uint offsetsAndSize[26];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_TextEditor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_TextEditor_t qt_meta_stringdata_TextEditor = {
    {
QT_MOC_LITERAL(0, 10), // "TextEditor"
QT_MOC_LITERAL(11, 23), // "on_action_New_triggered"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 24), // "on_action_Save_triggered"
QT_MOC_LITERAL(61, 26), // "on_action_SavaAs_triggered"
QT_MOC_LITERAL(88, 24), // "on_action_Open_triggered"
QT_MOC_LITERAL(113, 25), // "on_action_Color_triggered"
QT_MOC_LITERAL(139, 24), // "on_action_Font_triggered"
QT_MOC_LITERAL(164, 23), // "on_textEdit_textChanged"
QT_MOC_LITERAL(188, 29), // "on_action_selectAll_triggered"
QT_MOC_LITERAL(218, 24), // "on_action_Copy_triggered"
QT_MOC_LITERAL(243, 25), // "on_action_Paste_triggered"
QT_MOC_LITERAL(269, 23) // "on_action_Cut_triggered"

    },
    "TextEditor\0on_action_New_triggered\0\0"
    "on_action_Save_triggered\0"
    "on_action_SavaAs_triggered\0"
    "on_action_Open_triggered\0"
    "on_action_Color_triggered\0"
    "on_action_Font_triggered\0"
    "on_textEdit_textChanged\0"
    "on_action_selectAll_triggered\0"
    "on_action_Copy_triggered\0"
    "on_action_Paste_triggered\0"
    "on_action_Cut_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextEditor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    0,   84,    2, 0x08,    5 /* Private */,
       7,    0,   85,    2, 0x08,    6 /* Private */,
       8,    0,   86,    2, 0x08,    7 /* Private */,
       9,    0,   87,    2, 0x08,    8 /* Private */,
      10,    0,   88,    2, 0x08,    9 /* Private */,
      11,    0,   89,    2, 0x08,   10 /* Private */,
      12,    0,   90,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TextEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TextEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_action_New_triggered(); break;
        case 1: _t->on_action_Save_triggered(); break;
        case 2: _t->on_action_SavaAs_triggered(); break;
        case 3: _t->on_action_Open_triggered(); break;
        case 4: _t->on_action_Color_triggered(); break;
        case 5: _t->on_action_Font_triggered(); break;
        case 6: _t->on_textEdit_textChanged(); break;
        case 7: _t->on_action_selectAll_triggered(); break;
        case 8: _t->on_action_Copy_triggered(); break;
        case 9: _t->on_action_Paste_triggered(); break;
        case 10: _t->on_action_Cut_triggered(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject TextEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_TextEditor.offsetsAndSize,
    qt_meta_data_TextEditor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_TextEditor_t
, QtPrivate::TypeAndForceComplete<TextEditor, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *TextEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextEditor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TextEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
