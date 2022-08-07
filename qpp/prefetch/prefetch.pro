QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Source/Core/Thread/read_thread.h \
    Source/Core/Thread/sleep_thread.h \
    Source/Core/read_file.h \
    Source/Core/startup.h \
    Source/Global/global.h \
    Source/Input/Thread/loop_thread.h \
    Source/Input/stdin.h \
    Source/Output/stdout.h \
    Source/Setting/setting.h \
    Source/Translate/translate.h

SOURCES += \
        Source/Core/Thread/read_thread.cpp \
        Source/Core/Thread/sleep_thread.cpp \
        Source/Core/read_file.cpp \
        Source/Core/startup.cpp \
        Source/Global/global.cpp \
        Source/Input/Thread/loop_thread.cpp \
        Source/Input/stdin.cpp \
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

# Compiler -Ofast here we go again
QMAKE_CFLAGS_RELEASE -= -O
QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O3
QMAKE_CFLAGS_RELEASE *= -Ofast
