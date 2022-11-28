#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "entryclasses.h"
#include <iostream>

int main(int argc, char *argv[])
{

    Entry aeo = Entry();
    qDebug() << aeo.get_absolute_day();
    return 0;

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PaperFriend_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
