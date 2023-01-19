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
    strUndo.push(ui->textEdit->toHtml()); // Here the strUndo is a stack
    connect(ui->textEdit, SIGNAL(textChanged(QString)), this, SLOT(on_textEdit_textChanged));
    // Set Background color
    ui->lineEdit->setStyleSheet("background-color: rgb(220, 220, 220); border-radius: 5px;");
    ui->line->setStyleSheet("background-color: rgb(0,0,0); border-radius: 50%; width: 90%;");
    ui->lineEdit->setPlaceholderText("Edit Entry Title");
    ui->textEdit->setPlaceholderText("Edit Entry Text");
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::set_title(QString text)
{
    // set the title of the text editor
    // We want to display the title in indipendent line writen in html and css
    // We want to make the text in lineEdit become the title
    ui->lineEdit->clear();
    ui->lineEdit->setText(text);
    this->setWindowTitle(text);
}

// Set the maximum height of the text editor
void TextEditor::set_max_height(int height)
{
    ui->textEdit->setMaximumHeight(height - 10);
}

// Set the maximum width of the text editor
void TextEditor::set_max_width(int width)
{
    ui->textEdit->setMaximumWidth(width);
}

QString TextEditor::get_title() const
{
    // Return the pure text of the title
    return ui->lineEdit->text();
}

QString TextEditor::get_text() const
{
    return ui->textEdit->toHtml();
}

void TextEditor::append_title(QString text)
{
    ui->lineEdit->setText(text);
}

void TextEditor::set_text(QString text)
{
    ui->textEdit->clear();
    ui->textEdit->insertHtml(text);
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
    ui->textEdit->setAlignment(Qt::AlignLeft);
    if (ui->textEdit->alignment() == Qt::AlignLeft)
    {
        ui->action_Left->setChecked(true);
        ui->action_Right->setChecked(false);
        ui->action_Center->setChecked(false);
    }
}

void TextEditor::on_action_Right_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
    if (ui->textEdit->alignment() == Qt::AlignRight)
    {
        ui->action_Left->setChecked(false);
        ui->action_Right->setChecked(true);
        ui->action_Center->setChecked(false);
    }
}

void TextEditor::on_action_Center_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
    if (ui->textEdit->alignment() == Qt::AlignCenter)
    {
        ui->action_Left->setChecked(false);
        ui->action_Right->setChecked(false);
        ui->action_Center->setChecked(true);
    }
}

void TextEditor::on_action_Justify_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat format = cursor.blockFormat();
    format.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(format);
    ui->textEdit->setTextCursor(cursor);
}

void TextEditor::textColor()
{
    // get the color tool box from out side API
    QColor c = QColorDialog::getColor(Qt::red, this);
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

// Text editor blod italic underline
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
