// Head file of texteditor.cpp
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
// #include "finddlg.h"
#include <QTextCharFormat>
#include <QDialog>
#include <QStack>
#include "edit.h"

class MainWindow;

namespace Ui
{
    class TextEditor;
}

class TextEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();
    friend class MainWindow;
    class MainWindow *mainUi;
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
    void textBold();                                           // Set the font to bold
    void textItalic();                                         // Set the font to italic
    void textUnderline();                                      // Set the font to underline
    QStack<QString> strUndo;
    QStack<QString> strRedo;
    void refreshStack(); // Refresh the stack
    void resetStack();   // Clean the stack when open a new file
    void textCopy();     // Copy the text
    void textCut();
    void textPaste();
    QString pasteBoard;
    void createPdf();
    QString get_text() const;
    QString get_title() const;
    QString htmlText;
    void set_title(QString text);
    void on_textEdit();
    void set_text(QString text);
    void append_title(QString text);
    void set_max_width(int width);
    void set_max_height(int height);

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

    void on_action_Bold_triggered();

    void on_action_Italic_triggered();

    void on_action_Underline_triggered();

    void on_action_Left_triggered();

    void on_action_Right_triggered();

    void on_action_Center_triggered();

    void on_action_Justify_triggered();

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
