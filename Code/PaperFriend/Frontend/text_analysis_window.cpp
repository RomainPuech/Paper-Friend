#include "text_analysis_window.h"
#include "qevent.h"
#include "qthread.h"
#include "ui_text_analysis_window.h"
#include "Analysis/textanalysis.h"

#include <thread>
#include <QMovie>


text_analysis_window::text_analysis_window(EntryCard *card) :
        QMainWindow(),
        card(card),
        ui(new Ui::text_analysis_window)
    {

        ui->setupUi(this);
        message = new QTextEdit();
        load_container = new QLabel();
        mood = 0;
        movie = new QMovie("../PaperFriend/rsc/loading.gif");
        load_container->setMovie(movie);
        load_container->setMaximumSize(150, 150);
        movie->setScaledSize(QSize(150, 150));
        this->setWindowTitle("Analysis in progres...");
}


text_analysis_window::~text_analysis_window(){
    delete ui;
    delete message;
    delete load_container;
    delete movie;
}

void text_analysis_window::start(){
    movie->start();
    ui->verticalLayout->addWidget(load_container);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->apply_mood->setVisible(false);
    this->show();
}

void text_analysis_window::set_message(){
    movie->stop();
    ui->verticalLayout->removeWidget(load_container);
    load_container->setVisible(false);
    ui->apply_mood->setVisible(true);
    this->message->setText("The analysis of this entry suggests that your mood is " + QString::number(mood) + "%");
    this->setWindowTitle("Sentiment analysis of the text");
    this->message->setReadOnly(true);
    ui->verticalLayoutWidget->setStyleSheet("border-style: none;");
    ui->apply_mood->setStyleSheet("QPushButton{color: white; background-color: black; font-weight: bold; "
                                                              "font: 18px; border: 2px solid black; border-radius:"+ QString::number(card->get_border_radius())+"px;} "
                                                              "QPushButton:hover{background-color:white; color:black;}");
    this->message->setStyleSheet("font: 15px; font-weight: bold; border-style: 2px solid black; border-radius: 10px;");
    this->message->setAlignment(Qt::AlignCenter);
    this->message->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    ui->verticalLayout->addWidget(this->message);
}


void text_analysis_window::on_apply_mood_clicked()
{
    card->automatic_mood(mood);
}

void WindowThread::run(){
    window->start();
    window->show();
}
