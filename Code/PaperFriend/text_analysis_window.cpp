#include "text_analysis_window.h"
#include "ui_text_analysis_window.h"

text_analysis_window::text_analysis_window(double mood, EntryCard* card, QWidget* parent) :
        QDialog(parent),
        mood(mood),
        card(card),
        ui(new Ui::text_analysis_window)
    {

        ui->setupUi(this);
        message = new QTextEdit();
        this->setWindowIconText("Sentiment analysis of the text");
        message->setReadOnly(true);
        ui->verticalLayoutWidget->setStyleSheet("border-style: none;");
        ui->apply_mood->setStyleSheet("QPushButton{color: white; background-color: black; font-weight: bold; "
                                                          "font: 18px; border: 2px solid black; border-radius:"+ QString::number(card->get_border_radius())+"px;} "
                                                          "QPushButton:hover{background-color:white; color:black;}");
        message->setStyleSheet("font: 15px; font-weight: bold; border-style: 2px solid black; border-radius: "+ QString::number(card->get_border_radius())+"px;");
        message->setAlignment(Qt::AlignCenter);
        message->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        ui->verticalLayout->addWidget(message);
}

text_analysis_window::~text_analysis_window(){
    delete ui;
    delete message;
}

void text_analysis_window::set_message(QString message){
    this->message->setText(message);
}

void text_analysis_window::on_apply_mood_clicked(bool checked)
{
    card->automatic_mood(mood);
    qDebug()<<"mood set";
}

