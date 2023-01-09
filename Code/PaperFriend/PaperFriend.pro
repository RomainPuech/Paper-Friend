QT       += core gui
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activity_cell.cpp \
    activityclasses.cpp \
    all_activities.cpp \
    all_habits.cpp \
    all_people.cpp \
    cardclasses.cpp \
    Analysis/DataAnalysis.cpp \
    cipher/Qt-AES-1.2/qaesencryption.cpp \
    cipher/cipher.cpp \
    Analysis/moodanalysis.cpp \
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
    mypushbutton.cpp \
    settings.cpp \
    texteditor.cpp \
    edit.cpp \
    welcome_msg.cpp

HEADERS += \
    activity_cell.h \
    activityclasses.h \
    all_activities.h \
    all_habits.h \
    all_people.h \
    cardclasses.h \
    Analysis/DataAnalysis.h \
    cipher/Qt-AES-1.2/aesni/aesni-enc-cbc.h \
    cipher/Qt-AES-1.2/aesni/aesni-enc-ecb.h \
    cipher/Qt-AES-1.2/aesni/aesni-key-exp.h \
    cipher/Qt-AES-1.2/qaesencryption.h \
    cipher/cipher.h \
    Analysis/moodanalysis.h \
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
    mypushbutton.h \
    settings.h \
    texteditor.h \
    edit.h \
    welcome_msg.h

FORMS += \
    activity_cell.ui \
    all_activities.ui \
    all_habits.ui \
    all_people.ui \
    mainwindow.ui \
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
