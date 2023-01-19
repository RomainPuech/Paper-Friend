#include "text_analysis_window.h"
#include "ui_text_analysis_window.h"

text_analysis_window::text_analysis_window(QWidget* parent) :
        QDialog(parent),
        ui(new Ui::text_analysis_window)
    {

        ui->setupUi(this);
        message = new QTextEdit(ui->verticalLayoutWidget);
        ui->verticalLayout->addWidget(message);
        this->setWindowIconText("Sentiment analysis of the text");
        message->setReadOnly(true);
}

text_analysis_window::~text_analysis_window(){
    delete ui;
    delete message;
}

void text_analysis_window::set_message(QString message){
    this->message->setText(message);
}
