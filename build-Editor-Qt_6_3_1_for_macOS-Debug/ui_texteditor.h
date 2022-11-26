/********************************************************************************
** Form generated from reading UI file 'texteditor.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDITOR_H
#define UI_TEXTEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "edit.h"

QT_BEGIN_NAMESPACE

class Ui_TextEditor
{
public:
    QAction *action_New;
    QAction *action_Open;
    QAction *action_Close;
    QAction *action_Save;
    QAction *action_SavaAs;
    QAction *action_Exit;
    QAction *action_Undo;
    QAction *action_Cut;
    QAction *action_Copy;
    QAction *action_Paste;
    QAction *action_Find;
    QAction *action_Help;
    QAction *action_Bold;
    QAction *action_Italic;
    QAction *action_Underline;
    QAction *action_Left;
    QAction *action_Right;
    QAction *action_Center;
    QAction *action_Color;
    QAction *action_Font;
    QAction *action_Just;
    QAction *action_Y;
    QAction *action_selectAll;
    QAction *actionNew;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    Edit *textEdit;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_F_3;
    QMenu *menu_P;

    void setupUi(QMainWindow *TextEditor)
    {
        if (TextEditor->objectName().isEmpty())
            TextEditor->setObjectName(QString::fromUtf8("TextEditor"));
        TextEditor->resize(1000, 800);
        action_New = new QAction(TextEditor);
        action_New->setObjectName(QString::fromUtf8("action_New"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/myImages/rsc/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_New->setIcon(icon);
        action_Open = new QAction(TextEditor);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/myImages/rsc/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon1);
        action_Close = new QAction(TextEditor);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/myImages/rsc/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Close->setIcon(icon2);
        action_Save = new QAction(TextEditor);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/myImages/rsc/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Save->setIcon(icon3);
        action_SavaAs = new QAction(TextEditor);
        action_SavaAs->setObjectName(QString::fromUtf8("action_SavaAs"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/myImages/rsc/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_SavaAs->setIcon(icon4);
        action_Exit = new QAction(TextEditor);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_Exit->setIcon(icon2);
        action_Undo = new QAction(TextEditor);
        action_Undo->setObjectName(QString::fromUtf8("action_Undo"));
        action_Undo->setCheckable(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/myImages/rsc/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Undo->setIcon(icon5);
        action_Cut = new QAction(TextEditor);
        action_Cut->setObjectName(QString::fromUtf8("action_Cut"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/myImages/rsc/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Cut->setIcon(icon6);
        action_Copy = new QAction(TextEditor);
        action_Copy->setObjectName(QString::fromUtf8("action_Copy"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/myImages/rsc/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Copy->setIcon(icon7);
        action_Paste = new QAction(TextEditor);
        action_Paste->setObjectName(QString::fromUtf8("action_Paste"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/myImages/rsc/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Paste->setIcon(icon8);
        action_Find = new QAction(TextEditor);
        action_Find->setObjectName(QString::fromUtf8("action_Find"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/myImages/rsc/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Find->setIcon(icon9);
        action_Help = new QAction(TextEditor);
        action_Help->setObjectName(QString::fromUtf8("action_Help"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/myImages/rsc/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Help->setIcon(icon10);
        action_Bold = new QAction(TextEditor);
        action_Bold->setObjectName(QString::fromUtf8("action_Bold"));
        action_Bold->setCheckable(true);
        action_Bold->setChecked(false);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/myImages/rsc/bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Bold->setIcon(icon11);
        action_Italic = new QAction(TextEditor);
        action_Italic->setObjectName(QString::fromUtf8("action_Italic"));
        action_Italic->setCheckable(true);
        action_Italic->setChecked(false);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/myImages/rsc/i.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Italic->setIcon(icon12);
        action_Underline = new QAction(TextEditor);
        action_Underline->setObjectName(QString::fromUtf8("action_Underline"));
        action_Underline->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/myImages/rsc/underline.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Underline->setIcon(icon13);
        action_Left = new QAction(TextEditor);
        action_Left->setObjectName(QString::fromUtf8("action_Left"));
        action_Left->setCheckable(true);
        action_Left->setChecked(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/myImages/rsc/left.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Left->setIcon(icon14);
        action_Right = new QAction(TextEditor);
        action_Right->setObjectName(QString::fromUtf8("action_Right"));
        action_Right->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/myImages/rsc/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Right->setIcon(icon15);
        action_Center = new QAction(TextEditor);
        action_Center->setObjectName(QString::fromUtf8("action_Center"));
        action_Center->setCheckable(true);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/myImages/rsc/middle.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Center->setIcon(icon16);
        action_Color = new QAction(TextEditor);
        action_Color->setObjectName(QString::fromUtf8("action_Color"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/myImages/rsc/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Color->setIcon(icon17);
        action_Font = new QAction(TextEditor);
        action_Font->setObjectName(QString::fromUtf8("action_Font"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/myImages/rsc/size.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Font->setIcon(icon18);
        action_Just = new QAction(TextEditor);
        action_Just->setObjectName(QString::fromUtf8("action_Just"));
        action_Just->setCheckable(true);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/myImages/rsc/just.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Just->setIcon(icon19);
        action_Y = new QAction(TextEditor);
        action_Y->setObjectName(QString::fromUtf8("action_Y"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/myImages/rsc/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Y->setIcon(icon20);
        action_selectAll = new QAction(TextEditor);
        action_selectAll->setObjectName(QString::fromUtf8("action_selectAll"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/myImages/rsc/selectall.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_selectAll->setIcon(icon21);
        actionNew = new QAction(TextEditor);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        centralWidget = new QWidget(TextEditor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEdit = new Edit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        TextEditor->setCentralWidget(centralWidget);
        toolBar = new QToolBar(TextEditor);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        TextEditor->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(TextEditor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 24));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_F_3 = new QMenu(menu_2);
        menu_F_3->setObjectName(QString::fromUtf8("menu_F_3"));
        menu_P = new QMenu(menu_2);
        menu_P->setObjectName(QString::fromUtf8("menu_P"));
        TextEditor->setMenuBar(menuBar);

        toolBar->addAction(action_Open);
        toolBar->addAction(action_New);
        toolBar->addAction(action_Save);
        toolBar->addAction(action_SavaAs);
        toolBar->addSeparator();
        toolBar->addAction(action_Copy);
        toolBar->addAction(action_Cut);
        toolBar->addAction(action_Paste);
        toolBar->addSeparator();
        toolBar->addAction(action_Font);
        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu_F->addAction(action_New);
        menu_F->addAction(action_Open);
        menu_F->addSeparator();
        menu_F->addAction(action_Save);
        menu_F->addAction(action_SavaAs);
        menu->addAction(action_Undo);
        menu->addAction(action_Y);
        menu->addSeparator();
        menu->addAction(action_Cut);
        menu->addAction(action_Copy);
        menu->addAction(action_Paste);
        menu->addAction(action_selectAll);
        menu->addSeparator();
        menu->addAction(action_Find);
        menu_2->addAction(menu_F_3->menuAction());
        menu_2->addAction(menu_P->menuAction());
        menu_2->addAction(action_Color);
        menu_F_3->addAction(action_Bold);
        menu_F_3->addAction(action_Italic);
        menu_F_3->addAction(action_Underline);
        menu_F_3->addAction(action_Font);
        menu_P->addAction(action_Left);
        menu_P->addAction(action_Right);
        menu_P->addAction(action_Center);
        menu_P->addAction(action_Just);

        retranslateUi(TextEditor);

        QMetaObject::connectSlotsByName(TextEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TextEditor)
    {
        TextEditor->setWindowTitle(QCoreApplication::translate("TextEditor", "TextEditor", nullptr));
        action_New->setText(QCoreApplication::translate("TextEditor", "New", nullptr));
#if QT_CONFIG(tooltip)
        action_New->setToolTip(QCoreApplication::translate("TextEditor", "New File", nullptr));
#endif // QT_CONFIG(tooltip)
        action_Open->setText(QCoreApplication::translate("TextEditor", "Open", nullptr));
#if QT_CONFIG(tooltip)
        action_Open->setToolTip(QCoreApplication::translate("TextEditor", "Open the file", nullptr));
#endif // QT_CONFIG(tooltip)
        action_Close->setText(QCoreApplication::translate("TextEditor", "Close(&C)", nullptr));
        action_Save->setText(QCoreApplication::translate("TextEditor", "Save(&S)", nullptr));
#if QT_CONFIG(shortcut)
        action_Save->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_SavaAs->setText(QCoreApplication::translate("TextEditor", "Save As(&A)", nullptr));
        action_Exit->setText(QCoreApplication::translate("TextEditor", "Exit(&X)", nullptr));
        action_Undo->setText(QCoreApplication::translate("TextEditor", "Undo(&Z)", nullptr));
#if QT_CONFIG(shortcut)
        action_Undo->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Cut->setText(QCoreApplication::translate("TextEditor", "Cut(&X)", nullptr));
#if QT_CONFIG(shortcut)
        action_Cut->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Copy->setText(QCoreApplication::translate("TextEditor", "Copy(&C)", nullptr));
#if QT_CONFIG(shortcut)
        action_Copy->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Paste->setText(QCoreApplication::translate("TextEditor", "Paste(&V)", nullptr));
#if QT_CONFIG(shortcut)
        action_Paste->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Find->setText(QCoreApplication::translate("TextEditor", "Find/Substitue(&F)", nullptr));
#if QT_CONFIG(shortcut)
        action_Find->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Help->setText(QCoreApplication::translate("TextEditor", "About", nullptr));
        action_Bold->setText(QCoreApplication::translate("TextEditor", "Blod(&B)", nullptr));
#if QT_CONFIG(shortcut)
        action_Bold->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+B", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Italic->setText(QCoreApplication::translate("TextEditor", "Italic(&I)", nullptr));
#if QT_CONFIG(shortcut)
        action_Italic->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Underline->setText(QCoreApplication::translate("TextEditor", "Underline(U)", nullptr));
#if QT_CONFIG(shortcut)
        action_Underline->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Left->setText(QCoreApplication::translate("TextEditor", "JustifyLeft", nullptr));
        action_Right->setText(QCoreApplication::translate("TextEditor", "JustifyRight", nullptr));
        action_Center->setText(QCoreApplication::translate("TextEditor", "JustifyCenter", nullptr));
        action_Color->setText(QCoreApplication::translate("TextEditor", "Color", nullptr));
        action_Font->setText(QCoreApplication::translate("TextEditor", "Font Setting", nullptr));
        action_Just->setText(QCoreApplication::translate("TextEditor", "Alignment of both ends", nullptr));
        action_Y->setText(QCoreApplication::translate("TextEditor", "Redo(&Y)", nullptr));
#if QT_CONFIG(tooltip)
        action_Y->setToolTip(QCoreApplication::translate("TextEditor", "Redo(Y)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_Y->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        action_selectAll->setText(QCoreApplication::translate("TextEditor", "Select All(&A)", nullptr));
#if QT_CONFIG(tooltip)
        action_selectAll->setToolTip(QCoreApplication::translate("TextEditor", "Select All(A)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_selectAll->setShortcut(QCoreApplication::translate("TextEditor", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew->setText(QCoreApplication::translate("TextEditor", "New", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("TextEditor", "toolBar", nullptr));
        menu_F->setTitle(QCoreApplication::translate("TextEditor", "File(&F)", nullptr));
        menu->setTitle(QCoreApplication::translate("TextEditor", "Edit(&E)", nullptr));
        menu_2->setTitle(QCoreApplication::translate("TextEditor", "Format(&O)", nullptr));
        menu_F_3->setTitle(QCoreApplication::translate("TextEditor", "Font(&F)", nullptr));
        menu_P->setTitle(QCoreApplication::translate("TextEditor", "Paragraphs(&P)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextEditor: public Ui_TextEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDITOR_H
