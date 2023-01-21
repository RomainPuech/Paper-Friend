#include "text_analysis_window.h"
#include "qevent.h"
#include "ui_text_analysis_window.h"
#include "Analysis/textanalysis.h"

#include <thread>
#include <QMovie>


text_analysis_window::text_analysis_window(QString text_to_analize, double mood, EntryCard *card) :
        QMainWindow(),
        text_to_analize(text_to_analize),
        mood(mood),
        card(card),
        ui(new Ui::text_analysis_window)
    {

        ui->setupUi(this);
        analize_text = new TextAnalysis(text_to_analize);
        message = new QTextEdit();
        load_container = new QLabel();
        movie = new QMovie("../PaperFriend/rsc/loading.gif");
}


text_analysis_window::~text_analysis_window(){
    delete ui;
    delete message;
    delete analize_text;
    delete load_container;
    delete movie;
}

void text_analysis_window::set(QString text){
    text_to_analize = text;
    analize_text = new TextAnalysis(text_to_analize);
    if (!movie->isValid())
    {
        qDebug()<<"gif not loadeed";
    }
    load_container->setMovie(movie);
    load_container->setMaximumSize(150, 150);
    movie->setScaledSize(QSize(150, 150));
    this->setWindowTitle("Analysis in progres...");
    movie->start();
    ui->verticalLayout->addWidget(load_container);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->apply_mood->setVisible(false);
}

void text_analysis_window::set_message(QString message){
    this->message->setText(message);
}

void text_analysis_window::analize(){
    TextAnalysis *copy_for_thread = this->analize_text;
    std::thread text_analysis([copy_for_thread](){
            qDebug()<<"start analysis";
            copy_for_thread->analyze_text();
            for(long long unsigned i =0; i< 100000000; i++){

            }
            qDebug()<<"analysis done";
    });
    text_analysis.join();
    movie->stop();
    qDebug()<<"removing everything";
    ui->verticalLayout->removeWidget(load_container);
    ui->apply_mood->setVisible(true);
    message->setText("The analysis of this entry suggests that your mood is " + QString::number(analize_text->get_text_mood()));
    this->setWindowTitle("Sentiment analysis of the text");
    message->setReadOnly(true);
    ui->verticalLayoutWidget->setStyleSheet("border-style: none;");
    ui->apply_mood->setStyleSheet("QPushButton{color: white; background-color: black; font-weight: bold; "
                                                              "font: 18px; border: 2px solid black; border-radius:"+ QString::number(card->get_border_radius())+"px;} "
                                                              "QPushButton:hover{background-color:white; color:black;}");
    message->setStyleSheet("font: 15px; font-weight: bold; border-style: 2px solid black; border-radius: 10px;");
    message->setAlignment(Qt::AlignCenter);
    message->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    ui->verticalLayout->addWidget(message);

}


void text_analysis_window::on_apply_mood_clicked()
{
    card->automatic_mood(analize_text->get_text_mood()*100);
}

