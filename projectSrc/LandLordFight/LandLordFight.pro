QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS += ico/myico.ico


SOURCES += \
    aiplaycard.cpp \
    card.cpp \
    cardlist.cpp \
    cardsound.cpp \
    main.cpp \
    maindialog.cpp \
    playround.cpp \
    rulers.cpp

HEADERS += \
    aiplaycard.h \
    card.h \
    cardlist.h \
    cardsound.h \
    maindialog.h \
    playround.h \
    rulers.h

FORMS += \
    card.ui \
    maindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
