// Head file of texteditor.cpp
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
// #include "finddlg.h"
#include <QTextCharFormat>
#include <QDialog>
#include <QStack>
#include "edit.h"

namespace Ui
{
    class TextEditor;
}

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();
    void newFile();                         // Create a New file
    bool maybeSave();                       // check if the file is saved
    bool save();                            // save operation
    bool saveAs();                          // save as operation
    bool saveFile(const QString &fileName); // Save the file
    bool loadFile(const QString &fileName); // Load the file
    void mergeformat(const QTextCharFormat &fmt);
    void textColor();                                          // Set the text color
    void textCurrentFormatChanged(const QTextCharFormat &fmt); // Change the status of the menu
    void textFont();                                           // Set the font
    QStack<QString> strUndo;
    QStack<QString> strRedo;
    void refreshStack(); // Refresh the stack
    void resetStack();   // Clean the stack when open a new file
    void textCopy();     // Copy the text
    void textCut();
    void textPaste();
    QString pasteBoard;
    void createPdf();

private slots:
    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_SavaAs_triggered();

    void on_action_Open_triggered();

    void on_action_Color_triggered();

    void on_action_Font_triggered();
    void on_textEdit_textChanged();
    void on_action_selectAll_triggered();
    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Cut_triggered();

private:
    Edit edit;
    Ui::TextEditor *ui;
    // if isUntitled is true, the file is not saved
    bool isUntitled;
    // Save the current file path
    QString curFile;
    bool isUndo = 0;
    bool isRedo = 0;
    bool isLoadFile = 0;
    bool undoIsUsed = 0;
};

#endif // TEXTEDITOR_H
