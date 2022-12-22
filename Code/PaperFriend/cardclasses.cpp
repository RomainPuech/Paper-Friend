#include "cardclasses.h"
#include "mainwindow.h"

#include <QDate>
#include <QCalendar>
#include <QMessageBox>

Card::Card(int border_radius, int width, int height, QString color) : border_radius(border_radius), background_color(color){
    this->resize(width, height);
    this->rect().setHeight(height);
    this->rect().setWidth(width);
    this->setStyleSheet("background-color: " + color + "; border: 1px solid black; border-radius: " + QString::number(border_radius) + "px;");
    vb_layout = new QVBoxLayout(this);
    vb_layout->setContentsMargins(0, 0, 0, 0);
    vb_layout->setSpacing(0);
    this->setLayout(vb_layout);
}

Card::~Card(){
    delete vb_layout;
}

int Card::get_width() const{
    return this->width();
}

int Card::get_height() const{
    return this->height();
}

int Card::get_border_radius() const{
    return border_radius;
}

QString Card::get_background_color() const{
    return background_color;
}

void Card::set_width(int width){
    this->resize(width, this->height());
    this->rect().setWidth(width);
}

void Card::set_height(int height){
    this->resize(this->width(), height);
    this->rect().setHeight(height);
}

void Card::set_border_radius(int border_radius){
    this->border_radius = border_radius;
}

void Card::set_background_color(QString color){
    this->background_color = color;
}

void Card::display(QLayout *layout){
    this->setStyleSheet("background-color: " + background_color + "; border: 1px solid black; border-radius:" + QString::number(border_radius) + "px;");
    layout->addWidget(this);

}

QString generate_date_string(QDate date){
    /* Using the date of the entry generates the QString of the form
     * 'Day - dd days ago
     * date of the entry '
     */

    int day_int = date.dayOfWeek();
    QString day_string;
    switch(day_int){
    case 1:
        day_string = "Mon"; break;
    case 2:
        day_string = "Tue"; break;
    case 3:
        day_string = "Wed"; break;
    case 4:
        day_string = "Thu"; break;
    case 5:
        day_string = "Fri"; break;
    case 6:
        day_string = "Sat"; break;
    case 7:
        day_string = "Sun"; break;
    default:
        day_string = QString::number(day_int); break;
    }

    QDate today = QDate::currentDate();
    int days_ago = date.daysTo(today);
    QString days_ago_string;
    if(days_ago == 0){
        return day_string + " - today \n" + date.toString("MM-dd-yyyy");
    }
    else if(days_ago % 100 == 1){
        days_ago_string = " day ago \n";
    }
    else{
        days_ago_string = " days ago \n";
    }

    return day_string + " - " + QString::number(days_ago) + days_ago_string + date.toString("MM-dd-yyyy");
}

void generate_rgb(QString &red, QString &green, double m){
    /* Associate a color on a scale from red to green
     * according to the mood parameter
     */
    if(m <= 0.5){
        red = QString::number(255);
        green = QString::number(255 * m / (1-m));
    }
    else{
        green = QString::number(255);
        red = QString::number(255 * (1-m) / m);
    }
}

std::vector<QListWidgetItem*> EntryCard::fr_act_options;

EntryCard::EntryCard(int border_radius, int width, int height, QString color, Entry *entry, bool readOnly, MainWindow *main_window) : Card(border_radius, width, height, color), entry(entry), readOnly(readOnly), main_window(main_window){
    display_layout = new QVBoxLayout(); // to be changed - layout containing the card
    entry_perso = nullptr;
    entry_recap = nullptr;
    //entry_perso display
    date_display = new QLabel();
    text_title_w = new QWidget();
    edit_and_return = new QGroupBox();
    title = new QLabel(QString::fromStdString(entry->get_title()), text_title_w);
    text_field = new QTextEdit(QString::fromStdString(entry->get_text()), text_title_w);
    edit_vb = new QVBoxLayout(edit_and_return);
    top_menu = new QHBoxLayout();
    fr_act_display = new QListWidget();
    fr_act_select = new QListWidget();
    mood_display = new QLabel();
    mood_slider_w = new QWidget();
    mood_slider_instr = new QLabel(mood_slider_w);
    mood_slider = new QSlider(Qt::Horizontal, mood_slider_w);
    mood_slider_vb = new QVBoxLayout(mood_slider_w);
    text_title_vb = new QVBoxLayout(text_title_w);
    edit_text_w = new QStackedWidget();
    edit_text = new TextEditor();
    modify = new QPushButton("Modify this entry", text_title_w);
    back_to_display = new QPushButton("Exit editing mode", edit_and_return);
    //entry_recap display
    recap_layout = new QVBoxLayout();
    recap_title = new QLabel();
    mood_msg = new QWidget();
    avg_mood = new QLabel();
    message = new QTextEdit();
    mood_msg_hb = new QHBoxLayout();
    best_title = new QLabel();
    worst_title = new QLabel();
    best_date = new QLabel();
    worst_date = new QLabel();
    best_mood = new QLabel();
    worst_mood = new QLabel();
    recap_days_hb = new QHBoxLayout();
    best_day_vb = new QVBoxLayout();
    worst_day_vb = new QVBoxLayout();

    //find the type of the entry
    switch(entry->entry_type()){
        case 1:
            entry_perso = static_cast<EntryPerso*>(entry); break;
        case 2:
            entry_recap = static_cast<EntryRecap*>(entry); break;
    }

    //display specific for entryPerso
    if(entry_perso != nullptr){

        //set structure
        text_title_w->setParent(this);
        edit_and_return->setParent(this);
        //top_menu->setParent(this);
        fr_act_display->setParent(this);
        fr_act_select->setParent(this);
        mood_slider_w->setParent(this);


        // display date
        date_display->setMaximumHeight(47);
        date_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        date_display->setText(generate_date_string(entry->get_qdate()));
        date_display->setAlignment(Qt::AlignCenter);

        if((entry->get_title()) != ""){
            edit_text->set_title(QString::fromStdString(entry->get_title()));
        }
        edit_text->append_text(QString::fromStdString(entry->get_text()));


        //modify
        modify->setMinimumWidth(40);
        connect(modify, &QPushButton::released, this, &EntryCard::handleModify);

        //back_to_display
        back_to_display->setMinimumWidth(40);
        connect(back_to_display, &QPushButton::released, this, &EntryCard::handleBack);

        //entry text and title

        title->setMinimumHeight(40);
        title->setMinimumWidth(this->get_width());
        title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        title->setAlignment(Qt::AlignLeft);
        title->setContentsMargins(5, 10, 5, 0);

        text_field->setMinimumWidth(this->get_width());
        text_field->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        text_field->setAlignment(Qt::AlignLeft);
        text_field->setReadOnly(true);
        text_field->setContentsMargins(10, 0, 10, 5);

        //handle layout
        text_title_vb->addWidget(title);
        text_title_vb->addWidget(text_field);
        text_title_vb->addWidget(modify);
        text_title_w->setLayout(text_title_vb);

        //text-editor
        edit_text_w->setMinimumWidth(this->get_width());
        edit_text_w->setMinimumHeight(this->get_height());
        edit_text_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        edit_text_w->setContentsMargins(10, 0, 10, 5);

        //edit_text layout
        edit_text_w->addWidget(edit_text);
        edit_text_w->setCurrentWidget(edit_text);
        edit_text_w->setParent(edit_and_return);
        edit_vb->addWidget(edit_text_w);
        edit_vb->addWidget(back_to_display);
        edit_and_return->setLayout(edit_vb);

        //top menu
        top_menu->setAlignment(Qt::AlignTop);
        top_menu->setSpacing(0);
        date_display->setParent(this);
        top_menu->addWidget(date_display);

        // display activities and friends
        fr_act_display->setMaximumHeight(47);
        fr_act_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        for(long long unsigned fr = 0; fr < (entry_perso->get_friends()).size(); fr++){
            fr_act_display->addItem(QString::fromStdString((entry_perso->get_friends().at(fr))->get_name()));
        }
        for(long long unsigned act = 0; act < (entry_perso->get_activities()).size(); act++){
            QString name = QString::fromStdString((entry_perso->get_activities().at(act))->get_name());
            switch((entry_perso->get_activities().at(act))->get_type()){
                case 1: // sports
                    name += QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD"); break;
                case 2: // spiritual
                    name += QString::fromUtf8("\xE2\x9B\xAA"); break;
                case 3: // work
                    name += QString::fromUtf8("\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5"); break;
                case 4: // study
                    name += QString::fromUtf8("\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D"); break;
                case 5: // art
                    name += QString::fromUtf8("\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8"); break;
                default:
                    break;
            }
            fr_act_display->addItem(name);
        }

        //choose friends and activities
        fr_act_select->setMaximumHeight(47);
        fr_act_select->setSpacing(5);
        fr_act_select->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        for(long long unsigned fr = 0; fr < (MainWindow::get_friends()).size(); fr++){
            QListWidgetItem *cb = new QListWidgetItem(QString::fromStdString((MainWindow::get_friends().at(fr)).get_name()));
            cb->setCheckState(Qt::Unchecked);
            fr_act_options.push_back(cb);
            fr_act_select->addItem(cb);

        }
        for(long long unsigned act = 0; act < (MainWindow::get_activities()).size(); act++){
            QString name = QString::fromStdString((MainWindow::get_activities().at(act)).get_name());
            switch((MainWindow::get_activities().at(act)).get_type()){
                case 1: // sports
                    name += QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD"); break;
                case 2: // spiritual
                    name += QString::fromUtf8("\xE2\x9B\xAA"); break;
                case 3: // work
                    name += QString::fromUtf8("\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5"); break;
                case 4: // study
                    name += QString::fromUtf8("\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D"); break;
                case 5: // art
                    name += QString::fromUtf8("\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8"); break;
                default:
                    break;
            }

            QListWidgetItem *cb = new QListWidgetItem(name);
            cb->setCheckState(Qt::Unchecked);
            fr_act_options.push_back(cb);
            fr_act_select->addItem(cb);
        }

        //display mood
        mood_display->setText("Mood: " + QString::number(std::round(entry_perso->get_mood())) + "%");
        mood_display->setMaximumHeight(47);
        mood_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        mood_display->setAlignment(Qt::AlignCenter);

        //get mood
        mood_slider->setMinimum(0);
        mood_slider->setMaximum(100);
        mood_slider->setValue(int(this->entry_perso->get_mood()));
        mood_slider->setTickInterval(50);
        mood_slider->setTickPosition(QSlider::TicksBelow);
        mood_slider_instr->setText("Slide the bar to enter your mood");
        mood_slider->setMinimumHeight(18);
        mood_slider_w->setMaximumHeight(47);
        mood_slider_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        mood_slider_vb->setSpacing(5);
        mood_slider_instr->setAlignment(Qt::AlignCenter);
        mood_slider_vb->addWidget(mood_slider_instr);
        mood_slider_vb->addWidget(mood_slider);
        mood_slider_w->setLayout(mood_slider_vb);

        //size adjustments

        date_display->setMinimumWidth(this->get_width() / 3);
        fr_act_display->setMinimumWidth(this->get_width() / 3);
        fr_act_select->setMinimumWidth(this->get_width() / 3);
        mood_display->setMinimumWidth(this->get_width() / 3);
        mood_slider->setMinimumWidth(this->get_width() / 3);

        // top menu
        fr_act_display->setParent(this);
        fr_act_select->setParent(this);
        top_menu->addWidget(fr_act_display);
        top_menu->addWidget(fr_act_select);
        mood_display->setParent(this);
        top_menu->addWidget(mood_display);
        top_menu->addWidget(mood_slider_w);
        if(isReadOnly()){
            mood_display->setVisible(true);
            mood_slider_w->setVisible(false);
        }
        else{
            mood_slider_w->setVisible(true);
            mood_display->setVisible(false);
        }

        if(readOnly && fr_act_display->count() != 0){
            set_entryPerso_style(3);
        }
        else if(!readOnly && (MainWindow::get_activities().size() + MainWindow::get_friends().size()) != 0){
            set_entryPerso_style(3);
        }
        else{
            set_entryPerso_style(2);
        }

        //add to the layout
        vb_layout->addItem(top_menu);
        vb_layout->addWidget(text_title_w);
        vb_layout->addWidget(edit_and_return);
        if(isReadOnly()){
            text_title_w->setVisible(true); // for readOnly
            edit_and_return->setVisible(false);
        }
        else{
            edit_and_return->setVisible(true); // for editor
            text_title_w->setVisible(false);
        }
        this->setLayout(vb_layout);

    }

    else if(entry_recap != nullptr){
        EntryPerso best = entry_recap->get_best_day();
        EntryPerso worst = entry_recap->get_worst_day();
        recap_title->setParent(this);
        mood_msg_hb->setParent(this);

        switch(entry_recap->get_type()){
            case 0:
                recap_title->setText("Weekly recap"); break;
            case 1:
                recap_title->setText("Monthly recap"); break;
            case 2:
                recap_title->setText("Annual recap"); break;
        }
        recap_title->setMaximumHeight(50);
        recap_title->setMinimumWidth(this->get_width());
        recap_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        recap_title->setStyleSheet("font-weight: bold; font: 24px; border-style: none; border-bottom: 1px solid black; border-radius: 0px;");

        avg_mood->setText(QString::number(entry_recap->get_average_mood() * 100) + "% mood average");
        avg_mood->setMinimumHeight(50);
        avg_mood->setMinimumWidth(70);
        avg_mood->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        message->setText(QString::fromStdString(entry_recap->get_text()));
        message->setReadOnly(true);
        message->setMinimumHeight(50);
        message->setMinimumWidth(this->get_width() - 70);
        message->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        mood_msg_hb->addWidget(avg_mood);
        mood_msg_hb->addWidget(message);
        //mood_msg->setLayout(mood_msg_hb);
        recap_layout->addWidget(recap_title);
        recap_title->setAlignment(Qt::AlignCenter);
        recap_layout->addItem(mood_msg_hb);
        this->setLayout(recap_layout);

        /*best_title = new QLabel();
        worst_title = new QLabel();
        best_date = new QLabel();
        worst_date = new QLabel();
        best_mood = new QLabel();
        worst_mood = new QLabel();
        recap_days_hb = new QHBoxLayout();
        best_day_vb = new QVBoxLayout();
        worst_day_vb = new QVBoxLayout();*/


    }

}

EntryCard::~EntryCard(){
    /*//delete entry;
    delete date_display;
    delete mood_display;
    delete fr_act_display;
    delete top_menu;
    delete title;
    delete text_field;
    delete text_title_vb;
    delete text_title_w;
    //delete entry_perso;
    delete edit_text;
    delete edit_text_w;
    delete edit_vb;
    delete edit_and_return;
    delete modify;
    delete back_to_display;
    //delete display_layout;
    delete mood_slider_w;
    delete mood_slider_instr;
    delete mood_slider;
    delete mood_slider_vb;
    delete fr_act_select;
    delete main_window;
    delete recap_title;
    delete message;
    delete avg_mood;
    delete recap_days;
    delete recap_layout;
    delete recap_days_hb;*/
}

void EntryCard::handleModify(){
    this->change();
}

void EntryCard::handleBack(){
    QMessageBox alert;
    alert.setText("Do you want to save the changes to your entry?");
    alert.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    alert.setDefaultButton(QMessageBox::Save);
    int choice = alert.exec();
    std::string retrieve_text = (edit_text->get_text()).toStdString();
    std::string new_title = retrieve_text.substr(0, retrieve_text.find("\n"));
    std::string new_text = retrieve_text.substr(retrieve_text.find("\n") + 1);
    bool saved;
    switch(choice){
    case QMessageBox::Save:
        entry->set_title(new_title);
        entry->set_text(new_text);
        this->change();
        this->update();
        saved = save_entryperso(*entry_perso);
        if(saved){
            QMessageBox msg;
            msg.setText("successfully saved changes to the file");
            msg.exec();
        }
        else{
            QMessageBox msg;
            msg.setText("saving changes to the file failed");
            msg.exec();
        }
        break;
    case QMessageBox::Discard:
        this->change();
        break;
    alert.close();
    }


}

void EntryCard::change(){
    readOnly = !readOnly;
    if(isReadOnly()){
        text_title_w->setVisible(true);
        edit_and_return->setVisible(false); // for readOnly text
        if(entry_perso != nullptr){
            mood_slider_w->setVisible(false);
            mood_display->setVisible(true);
        }
    }
    else{
        text_title_w->setVisible(false);
        edit_and_return->setVisible(true); // for editor
        if(entry_perso != nullptr){
            update_fr_act_select();
            mood_display->setVisible(false);
            mood_slider_w->setVisible(true);
        }
    }
    if(readOnly && fr_act_display->count() != 0){
        set_entryPerso_style(3);
    }
    else if(!readOnly && (MainWindow::get_activities().size() + MainWindow::get_friends().size()) != 0){
        set_entryPerso_style(3);
    }
    else{
        set_entryPerso_style(2);
    }
}

void EntryCard::update(){
    //update values
    date_display->setText(generate_date_string(entry->get_qdate()));
    title->setText(QString::fromStdString(entry->get_title()));
    text_field->setText(QString::fromStdString(entry->get_text()));
    if((entry->get_title()) != ""){
        edit_text->set_title(QString::fromStdString(entry->get_title()));
    }
    edit_text->append_text(QString::fromStdString(entry->get_text()));
    if(entry_perso != nullptr){
        this->entry_perso->set_mood(this->mood_slider->value());
        mood_display->setText("Mood: " + QString::number(std::round(entry_perso->get_mood())) + "%");
        mood_slider->setValue(int(this->entry_perso->get_mood()));
        //friends and activities
        update_fr_act();
    }
    //update dynamic graph
    main_window->update_graph();
    //update style
    if(readOnly && fr_act_display->count() != 0){
        set_entryPerso_style(3);
    }
    else if(!readOnly && (MainWindow::get_activities().size() + MainWindow::get_friends().size()) != 0){
        set_entryPerso_style(3);
    }
    else{
        set_entryPerso_style(2);
    }

}

void EntryCard::update_fr_act_select(){
    for(long long unsigned fr = 0; fr < (MainWindow::get_friends()).size(); fr++){
        QListWidgetItem *cb = new QListWidgetItem(QString::fromStdString((MainWindow::get_friends().at(fr)).get_name()));
        cb->setCheckState(Qt::Unchecked);
        fr_act_options.push_back(cb);
        fr_act_select->addItem(cb);

    }
    for(long long unsigned act = 0; act < (MainWindow::get_activities()).size(); act++){
        QString name = QString::fromStdString((MainWindow::get_activities().at(act)).get_name());
        switch((MainWindow::get_activities().at(act)).get_type()){
            case 1: // sports
                name += QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD"); break;
            case 2: // spiritual
                name += QString::fromUtf8("\xE2\x9B\xAA"); break;
            case 3: // work
                name += QString::fromUtf8("\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5"); break;
            case 4: // study
                name += QString::fromUtf8("\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D"); break;
            case 5: // art
                name += QString::fromUtf8("\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8"); break;
            default:
                break;
        }

        QListWidgetItem *cb = new QListWidgetItem(name);
        cb->setCheckState(Qt::Unchecked);
        fr_act_options.push_back(cb);
        fr_act_select->addItem(cb);
    }
}

void EntryCard::update_fr_act(){
    std::vector<Activity*> activities;
    std::vector<Friend*> friends;
    unsigned long long num_friends = (MainWindow::get_friends()).size();
    unsigned long long num_activities = (MainWindow::get_activities()).size();
    qDebug()<< QString::number((MainWindow::get_activities()).size());

    for(unsigned long long i = 0; i < num_activities; i++){
        QListWidgetItem *option = fr_act_options.at(fr_act_options.size()-1);
        fr_act_options.pop_back();
        if(option->checkState() == Qt::Checked){
            activities.push_back(MainWindow::get_activity_at_i(i));
        }
        fr_act_select->removeItemWidget(option);
        delete option;
    }

    for(unsigned long long i = 0; i < num_friends; i++){
        QListWidgetItem *option = fr_act_options.at(fr_act_options.size()-1);
        fr_act_options.pop_back();
        if(option->checkState() == Qt::Checked){
            friends.push_back(MainWindow::get_friend_at_i(i));
        }
        fr_act_select->removeItemWidget(option);
        delete option;
    }

    entry_perso->set_activities(activities);
    entry_perso->set_friends(friends);

    fr_act_display->clear();
    for(unsigned long long fr = 0; fr < (entry_perso->get_friends()).size(); fr++){
        fr_act_display->addItem(QString::fromStdString((entry_perso->get_friends().at(fr))->get_name()));
    }
    for(unsigned long long act = 0; act < (entry_perso->get_activities()).size(); act++){
        QString name = QString::fromStdString((entry_perso->get_activities().at(act))->get_name());
        switch((entry_perso->get_activities().at(act))->get_type()){
            case 1: // sports
                name += QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD"); break;
            case 2: // spiritual
                name += QString::fromUtf8("\xE2\x9B\xAA"); break;
            case 3: // work
                name += QString::fromUtf8("\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5"); break;
            case 4: // study
                name += QString::fromUtf8("\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D"); break;
            case 5: // art
                name += QString::fromUtf8("\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8"); break;
            default:
                break;
        }
        fr_act_display->addItem(name);
    }
}

void EntryCard::set_entryPerso_style(int top_menu_num_items){
    if(top_menu_num_items == 3 and readOnly){
        fr_act_display->setVisible(true);
        fr_act_select->setVisible(false);
        qDebug()<< "READONLY MODE";
    }
    else if(top_menu_num_items == 3){
        fr_act_display->setVisible(false);
        fr_act_select->setVisible(true);
        qDebug()<< "CORRECT DISPLAY FOR MODIFYING";
    }
    else{
        fr_act_display->setVisible(false);
        fr_act_select->setVisible(false);
        qDebug()<< "BOTH INVISIBLE";
    }

    this->setStyleSheet("background-color: " + get_background_color() + "; border: 1px solid black; border-radius: " + QString::number(get_border_radius()) + "px;");
    date_display->setStyleSheet("font-weight: bold; border-style: none; border-radius: 0px; border-top-left-radius: " + QString::number(this->get_border_radius()) + "px; border-right: 1px solid black; border-bottom: 1px solid black;");
    text_title_w->setStyleSheet("border-style: none; border-radius: 0px; border-bottom-left-radius: " + QString::number(this->get_border_radius()) + "px; border-bottom-right-radius: " + QString::number(this->get_border_radius()) + "px;");
    title->setStyleSheet("font: 24px; font-weight: bold; border-style: none;");
    edit_text_w->setStyleSheet("border-style: none;");
    edit_and_return->setStyleSheet("border-style: none;");
    modify->setStyleSheet("QPushButton{color: white; background-color: black; font-weight: bold; font: 15px; border: 2px solid black; border-radius: 5px;} QPushButton:hover{background-color:white; color:black;}");
    back_to_display->setStyleSheet("QPushButton{color: white; background-color: black; font-weight: bold; font: 15px; border: 2px solid black; border-radius: 5px;} QPushButton:hover{background-color:white; color:black;}");
    fr_act_display->setStyleSheet("font-weight: bold; border-style: none; border-radius: 0px; border-right: 1px solid black; border-bottom: 1px solid black;");
    fr_act_select->setStyleSheet("font-weight: bold; border-style: none; border-radius: 0px; border-right: 1px solid black; border-bottom: 1px solid black;");
    QString red, green;
    generate_rgb(red, green, entry_perso->get_mood()/100);
    mood_display->setStyleSheet("font-weight: bold; color: rgb(" + red + ", " + green + ", 0); border-style: none; border-bottom: 1px solid black; border-radius: 0px; border-top-right-radius:" + QString::number(this->get_border_radius()) + "px;");
    mood_slider_w->setStyleSheet("border-style: none; border-bottom: 1px solid black; border-radius: 0px; border-top-right-radius: " + QString::number(get_border_radius()) + "px;");
    mood_slider->setStyleSheet("QSlider{border-style: none;} QSlider::groove:horizontal{border-style: none; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 rgb(255, 0, 0), stop: 0.5 rgb(255, 255, 0), stop: 1 rgb(0, 255, 0)); height: 10px; border-radius: 5px;}QSlider::sub-page:horizontal{background: transparent;border: 1px solid grey;height: 10px;border-radius: 5px;} QSlider::add-page:horizontal {background: white; border: 1px solid grey;height: 10px;border-radius: 5px;} QSlider::handle:horizontal {background: grey; border: 1px solid dark-grey; width: 16px;margin-top: -3px;margin-bottom: -3px;border-radius: 5px;} QSlider::handle:horizontal:hover {background: dark-grey; border: 1px solid black; border-radius: 5px;}");
    mood_slider_instr->setStyleSheet("font-weight: bold; border-style: none;");

}

void EntryCard::display(QLayout *layout){
    layout->addWidget(this);
    display_layout = layout;
}

bool EntryCard::isReadOnly(){
    return readOnly;
}

void EntryCard::setReadOnly(bool readOnly){
    this->readOnly = readOnly;
}

void EntryCard::set_main_window(MainWindow* mw){
    main_window = mw;
}
