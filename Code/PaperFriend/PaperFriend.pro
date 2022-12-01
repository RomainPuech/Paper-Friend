QT       += core gui
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activityclasses.cpp \
    all_activities.cpp \
    all_habits.cpp \
    cardclasses.cpp \
    Analysis/DataAnalysis.cpp \
    cipher/Qt-AES-1.2/qaesencryption.cpp \
    cipher/cipher.cpp \
    dynamicgraph.cpp \
    Analysis/moodanalysis.cpp \
    entryclasses.cpp \
    friendclasses.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    activityclasses.h \
    all_activities.h \
    all_habits.h \
    cardclasses.h \
    Analysis/DataAnalysis.h \
    cipher/Qt-AES-1.2/aesni/aesni-enc-cbc.h \
    cipher/Qt-AES-1.2/aesni/aesni-enc-ecb.h \
    cipher/Qt-AES-1.2/aesni/aesni-key-exp.h \
    cipher/Qt-AES-1.2/qaesencryption.h \
    cipher/cipher.h \
    dynamicgraph.h \
    Analysis/moodanalysis.h \
    entryclasses.h \
    friendclasses.h \
    mainwindow.h

FORMS += \
    all_habits.ui \
    mainwindow.ui

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
