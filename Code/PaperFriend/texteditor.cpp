// C++ file of the texteditor
#include "texteditor.h"
#include "ui_texteditor.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>
#include <cstring>
// #include "finddlg.h"
#include <QTimer>
#include <QShortcut>

// Initialize the texteditor - checked
TextEditor::TextEditor(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    isUntitled = true;                         // initialize the text as the status of unsaved
    curFile = tr("Untitled.txt");              // initialize the current file name as "untitled.txt"
    strUndo.push(ui->textEdit->toPlainText()); // Here the strUndo is a stack
    connect(ui->textEdit, SIGNAL(textChanged(QString)), this, SLOT(on_textEdit_textChanged));
}

TextEditor::~TextEditor()
{
    delete ui;
}

QString TextEditor::get_text() const{
    return ui->textEdit->toPlainText();
}

void TextEditor::set_title(QString text){
    ui->textEdit->setFontWeight(QFont::Bold);
    ui->textEdit->clear();
    ui->textEdit->insertPlainText(text);
    ui->textEdit->setFontWeight(1);
}

void TextEditor::append_text(QString text){
    ui->textEdit->insertPlainText(text);
}

// Create a new file - checked
// If you create a file without saving the previous file, the warning will pop up to remind you to save the previous file
void TextEditor::newFile()
{
    if (maybeSave() == true)
    {
        isUntitled = true;
        curFile = tr("Untitled.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
        strUndo.push(ui->textEdit->toPlainText());
    }
    resetStack();                              // clean and reset the stack and return to the initial state of 0
    strUndo.push(ui->textEdit->toPlainText()); // push the current text into the stack
}

// Check if the file is saved - checked
// If the file is not saved, then pop up a dialog box to ask the user to save the file, otherwise, return false
bool TextEditor::maybeSave()
{
    // if the file is modified
    if ((ui->textEdit->document()->isModified()) || ((undoIsUsed) && (!strUndo.isEmpty())))
    {
        // Waring part, we create a warning box here
        QMessageBox box;
        isUntitled = false;
        box.setWindowTitle(tr("Warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + tr(" haven't been saved, Do you want to save it?"));
        QPushButton *yesBtn = box.addButton(tr("YES"),
                                            QMessageBox::YesRole);
        QPushButton *noBtn = box.addButton(tr("NO"),
                                           QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("CANCEL"),
                                               QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton() == yesBtn)
            return save();
        else if (box.clickedButton() == cancelBut)
            return false;
    }
    return true;
}

// Save the file - checked
bool TextEditor::save()
{
    isUntitled == true ? saveAs() : saveFile(curFile);
}

// Save the file as - checked
bool TextEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save As"), curFile);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

// Clean the stack when open a new file
void TextEditor::resetStack()
{
    // clear the stack both in the undo and redo
    while (!strUndo.isEmpty())
    {
        strUndo.pop();
    }
    while (!strRedo.isEmpty())
    {
        strRedo.pop();
    }
    undoIsUsed = 0;
}

// Save the file
bool TextEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);

    QTextStream out(&file);
    // mouse pointer change to wait
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    // mouse pointer change to original
    QApplication::restoreOverrideCursor();
    isUntitled = false;
    // get the current file name
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

// Load the file
bool TextEditor::loadFile(const QString &fileName)
{
    // resetStack();
    QFile file(fileName); // create a new Qfile object

    QTextStream in(&file); // create a new QTextStream object
    QApplication::setOverrideCursor(Qt::WaitCursor);
    // Read the file
    ui->textEdit->setPlainText(in.readAll());
    resetStack();
    strUndo.push(ui->textEdit->toPlainText());
    QApplication::restoreOverrideCursor();

    // Set the current file name
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile + tr(" TextEditor"));
    ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    return true;
}

// Justify Triggered Part
void TextEditor::on_action_New_triggered()
{
    newFile();
}

void TextEditor::on_action_Save_triggered()
{
    save();
}

void TextEditor::on_action_SavaAs_triggered()
{
    saveAs();
}

void TextEditor::on_action_Open_triggered()
{
    //    resetStack();
    //    isLoadFile=1;
    if (maybeSave())
    {

        QString fileName = QFileDialog::getOpenFileName(this);

        // 如果文件名不为空，则加载文件
        if (!fileName.isEmpty())
        {
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}

void TextEditor::mergeformat(const QTextCharFormat &fmt)
{
    // Selection of the current cursor, like selection of the text that we want to copy or with other operations
    QTextCursor cursor = ui->textEdit->textCursor();

    if (cursor.hasSelection() == false)

        cursor.select(QTextCursor::WordUnderCursor);

    cursor.mergeCharFormat(fmt);

    ui->textEdit->mergeCurrentCharFormat(fmt);
}

// Bold, Italic, Underline, Strikeout
void TextEditor::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->action_Bold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeformat(fmt);
}

void TextEditor::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->action_Italic->isChecked());
    mergeformat(fmt);
}

void TextEditor::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->action_Underline->isChecked());
    mergeformat(fmt);
}

// Justify part, left justiy, right justify, center justify
void TextEditor::on_action_Left_triggered()
{
    ui->textEdit->setAlignment( Qt::AlignLeft );
    if (ui->textEdit->alignment() == Qt::AlignLeft)
    {
        ui->action_Left->setChecked(true);
        ui->action_Right->setChecked(false);
        ui->action_Center->setChecked(false);
    }
}

void TextEditor::on_action_Right_triggered()
{
    ui->textEdit->setAlignment( Qt::AlignRight );
    if (ui->textEdit->alignment() == Qt::AlignRight)
    {
        ui->action_Left->setChecked(false);
        ui->action_Right->setChecked(true);
        ui->action_Center->setChecked(false);
    }
}

void TextEditor::on_action_Center_triggered()
{
    ui->textEdit->setAlignment( Qt::AlignCenter );
    if (ui->textEdit->alignment() == Qt::AlignCenter)
    {
        ui->action_Left->setChecked(false);
        ui->action_Right->setChecked(false);
        ui->action_Center->setChecked(true);
    }
}

void TextEditor::on_action_Justify_triggered()
{
    ui->textEdit->setAlignment( Qt::AlignJustify );
    if (ui->textEdit->alignment() == Qt::AlignJustify)
    {
        ui->action_Left->setChecked(false);
        ui->action_Right->setChecked(false);
        ui->action_Center->setChecked(false);
    }
}

void TextEditor::textColor()
{
    QColor c = QColorDialog::getColor(Qt::red, this); // get the color tool box from out side API
    if (c.isValid())
    {
        QTextCharFormat fmt;

        fmt.setForeground(c);

        mergeformat(fmt);
    }
}

void TextEditor::textFont()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok); // get the Font tool box from out side API
    if (ok)
    {
        QTextCharFormat fmt;

        fmt.setFont(f);

        mergeformat(fmt);
    }
}

void TextEditor::textCopy()
{
    pasteBoard = "";
    // Setting the cursor for the part you want to copy
    QTextCursor cursor = ui->textEdit->textCursor();

    // If the cursor is not selected, then select the word under the cursor
    pasteBoard = cursor.selectedText();
}

void TextEditor::textCut()
{
    // Setting the cursor for the part you want to cut and storage the part you want to cut in the pasteBoard
    QTextCursor cursor = ui->textEdit->textCursor();

    pasteBoard = cursor.selectedText();

    cursor.removeSelectedText();
}

void TextEditor::textPaste()
{
    // Delete the part you want to paste and storage the part you want to paste in the pasteBoard
    QTextCursor cursor = ui->textEdit->textCursor();

    cursor.removeSelectedText();

    cursor.insertText(pasteBoard);
}

void TextEditor::on_action_Color_triggered()
{
    textColor();
}

void TextEditor::on_action_Font_triggered()
{
    textFont();
}

void TextEditor::on_textEdit_textChanged()
{
    if ((isUndo == false) && (isRedo == false) && (isLoadFile == false))
    {
        strUndo.push(ui->textEdit->toPlainText());
    }
}

// 以后的有关斜体，加粗，下标的代码 - Declearation Part
void TextEditor::on_action_Bold_triggered()
{
    textBold();
}

void TextEditor::on_action_Italic_triggered()
{
    textItalic();
}

void TextEditor::on_action_Underline_triggered()
{
    textUnderline();
}



void TextEditor::on_action_selectAll_triggered()
{
    ui->textEdit->selectAll();
}
void TextEditor::on_action_Copy_triggered()
{
    textCopy();
}

void TextEditor::on_action_Paste_triggered()
{
    textPaste();
}

void TextEditor::on_action_Cut_triggered()
{
    textCut();
}
