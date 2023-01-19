QT       += core gui
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Analysis/textanalysis.cpp \
    activity_cell.cpp \
    activityclasses.cpp \
    all_activities.cpp \
    all_habits.cpp \
    cardclasses.cpp \
    Analysis/DataAnalysis.cpp \
    entryclasses.cpp \
    entryfilter.cpp \
    entryrecap.cpp \
    file_processing/file_processing/file_save_and_load.cpp \
    friendclasses.cpp \
    main.cpp \
    mainwindow.cpp\
    dynamicgraph.cpp \
    mascot.cpp \
    mascotchat.cpp \
    settings.cpp \
    text_analysis_window.cpp \
    texteditor.cpp \
    edit.cpp \
    welcome_msg.cpp

HEADERS += \
    Analysis/textanalysis.h \
    activity_cell.h \
    activityclasses.h \
    all_activities.h \
    all_habits.h \
    cardclasses.h \
    Analysis/DataAnalysis.h \
    entryclasses.h \
    entryfilter.h \
    entryrecap.h \
    file_processing/file_processing/file_save_and_load.h \
    friendclasses.h \
    mainwindow.h\
    dynamicgraph.h \
    mascot.h \
    mascotchat.h \
    mascotchat.h \
    settings.h \
    text_analysis_window.h \
    texteditor.h \
    edit.h \
    welcome_msg.h

FORMS += \
    activity_cell.ui \
    add_habit_cell.ui \
    all_activities.ui \
    all_habits.ui \
    mainwindow.ui \
    text_analysis_window.ui \
    texteditor.ui \

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
