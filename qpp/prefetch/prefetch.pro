QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Source/Global/global.cpp \
        Source/Output/stdout.cpp \
        Source/Setting/setting.cpp \
        Source/Translate/translate.cpp \
        main.cpp

TRANSLATIONS += \
    prefetch_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# My setting

# Enable c++11 for QT 4.8.7
QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    Source/Global/global.h \
    Source/Output/stdout.h \
    Source/Setting/setting.h \
    Source/Translate/translate.h

DISTFILES += \
    prefetch.ini
