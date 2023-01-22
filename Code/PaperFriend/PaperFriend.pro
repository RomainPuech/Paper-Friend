QT       += core gui
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Analysis/textanalysis.cpp \
    Analysis/DataAnalysis.cpp \
    file_processing/file_processing/file_save_and_load.cpp \
    Frontend/activity_cell.cpp \
    Frontend/activityclasses.cpp \
    Frontend/all_activities.cpp \
    Frontend/all_habits.cpp \
    Frontend/cardclasses.cpp \
    Frontend/display_daily_habit.cpp \
    Frontend/dynamicgraph.cpp \
    Frontend/entryclasses.cpp \
    Frontend/entryfilter.cpp \
    Frontend/entryrecap.cpp \
    Frontend/main.cpp \
    Frontend/mainwindow.cpp\
    Frontend/mascot.cpp \
    Frontend/mascotchat.cpp \
    Frontend/settings.cpp \
    Frontend/text_analysis_window.cpp \
    Frontend/texteditor.cpp \
    Frontend/edit.cpp \
    Frontend/welcome_msg.cpp

HEADERS += \
    Analysis/textanalysis.h \
    Analysis/DataAnalysis.h \
    file_processing/file_processing/file_save_and_load.h \
    Frontend/activity_cell.h \
    Frontend/activityclasses.h \
    Frontend/all_activities.h \
    Frontend/all_habits.h \
    Frontend/cardclasses.h \
    Frontend/display_daily_habit.h \
    Frontend/dynamicgraph.h \
    Frontend/entryclasses.h \
    Frontend/entryfilter.h \
    Frontend/entryrecap.h \
    Frontend/mainwindow.h \
    Frontend/mascot.h \
    Frontend/mascotchat.h \
    Frontend/mascotchat.h \
    Frontend/settings.h \
    Frontend/text_analysis_window.h \
    Frontend/texteditor.h \
    Frontend/edit.h \
    Frontend/welcome_msg.h

FORMS += \
    Frontend/activity_cell.ui \
    Frontend/add_habit_cell.ui \
    Frontend/all_activities.ui \
    Frontend/all_habits.ui \
    Frontend/display_daily_habit.ui \
    Frontend/mainwindow.ui \
    Frontend/text_analysis_window.ui \
    Frontend/texteditor.ui

TRANSLATIONS += \
    PaperFriend_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cipher/Qt-AES-1.2/CONTRIBUTING.md \
    cipher/Qt-AES-1.2/LICENSE \
    cipher/Qt-AES-1.2/README.md

RESOURCES += \
    myresources.qrc

RC_FILE += rsc/Editor.rc

macx: {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
}
