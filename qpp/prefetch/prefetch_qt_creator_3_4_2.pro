#-------------------------------------------------
#
# Project created by QtCreator 2023-03-26T19:08:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prefetch_qt_creator_3_4_2
TEMPLATE = app

HEADERS  += \
    Source/Core/ReadFile/const_read_file_thread.h \
    Source/Core/ReadFile/read_file_thread.h \
    Source/Core/RocketLaunch/rocket_launch.h \
    Source/Core/ScanCache/scan_cache.h \
    Source/Core/Skip/skip.h \
    Source/Core/Sleep/sleep.h \
    Source/Core/Sleep/sleep_thread.h \
    Source/Core/StartProcess/start_process.h \
    Source/Core/Startup/startup.h \
    Source/Core/Time/time.h \
    Source/Core/const_core.h \
    Source/Core/core.h \
    Source/Define/define.h \
    Source/Example/Hack/function_pointer_in_signal_slot.h \
    Source/Example/mutex_example.h \
    Source/Example/run_on_ui_thread_example.h \
    Source/Example/self_delete_thread_example.h \
    Source/Example/semaphore_example.h \
    Source/Global/const_global.h \
    Source/Global/global.h \
    Source/Input/Thread/Command/Level1/parent_define.h \
    Source/Input/Thread/Command/Level2/parent_define.h \
    Source/Input/Thread/input_loop_thread.h \
    Source/Input/Thread/receive_text_thread.h \
    Source/Input/command_line_argument.h \
    Source/Input/const_input.h \
    Source/Input/stdin.h \
    Source/Interface/Dpi/dpi.h \
    Source/Interface/MainWindow/const_mainwindow.h \
    Source/Interface/MainWindow/mainwindow.h \
    Source/Interface/TrayIcon/Action/custom_action.h \
    Source/Interface/TrayIcon/const_tray_icon.h \
    Source/Interface/TrayIcon/tray_icon.h \
    Source/Interface/TrayIcon/tray_icon_object.h \
    Source/Output/const_log.h \
    Source/Output/log.h \
    Source/Output/stdout.h \
    Source/Setting/const_setting.h \
    Source/Setting/setting.h \
    Source/Template/include_guard.h \
    Source/Translate/const_translator_loader.h \
    Source/Translate/translate_define.h \
    Source/Translate/translate_tool.h \
    Source/Translate/translator_loader.h

SOURCES += \
    main.cpp\
    Source/Core/ReadFile/init.cpp \
    Source/Core/ReadFile/read_file_thread.cpp \
    Source/Core/ReadFile/run.cpp \
    Source/Core/RocketLaunch/rocket_launch.cpp \
    Source/Core/ScanCache/scan_cache.cpp \
    Source/Core/Skip/skip.cpp \
    Source/Core/Sleep/sleep.cpp \
    Source/Core/Sleep/sleep_thread.cpp \
    Source/Core/StartProcess/start_process.cpp \
    Source/Core/Startup/startup.cpp \
    Source/Core/Time/time.cpp \
    Source/Core/const_core.cpp \
    Source/Core/const_core_tdummy.cpp \
    Source/Core/core.cpp \
    Source/Core/init.cpp \
    Source/Core/run.cpp \
    Source/Global/const_global.cpp \
    Source/Global/global.cpp \
    Source/Input/Thread/Command/Level1/exit.cpp \
    Source/Input/Thread/Command/Level1/expiresc.cpp \
    Source/Input/Thread/Command/Level1/start.cpp \
    Source/Input/Thread/Command/Level1/startup.cpp \
    Source/Input/Thread/Command/Level1/stop.cpp \
    Source/Input/Thread/Command/Level1/test.cpp \
    Source/Input/Thread/Command/Level1/traydc.cpp \
    Source/Input/Thread/Command/Level2/lang.cpp \
    Source/Input/Thread/Command/Level2/run.cpp \
    Source/Input/Thread/input_loop_thread.cpp \
    Source/Input/Thread/receive_text_thread.cpp \
    Source/Input/cli_constructor.cpp \
    Source/Input/cli_to_string.cpp \
    Source/Input/command_line_argument.cpp \
    Source/Input/const_input.cpp \
    Source/Input/const_input_tdummy.cpp \
    Source/Input/stdin.cpp \
    Source/Input/stdin_freeze_restore.cpp \
    Source/Interface/Dpi/dpi.cpp \
    Source/Interface/MainWindow/const_mainwindow.cpp \
    Source/Interface/MainWindow/const_mainwindow_tdummy.cpp \
    Source/Interface/MainWindow/mainwindow.cpp \
    Source/Interface/MainWindow/send_command.cpp \
    Source/Interface/MainWindow/slot_io.cpp \
    Source/Interface/MainWindow/slot_scroll_bar.cpp \
    Source/Interface/MainWindow/slot_window_event.cpp \
    Source/Interface/MainWindow/stdout.cpp \
    Source/Interface/TrayIcon/Action/custom_action.cpp \
    Source/Interface/TrayIcon/const_tray_icon.cpp \
    Source/Interface/TrayIcon/const_tray_icon_tdummy.cpp \
    Source/Interface/TrayIcon/freeze_restore.cpp \
    Source/Interface/TrayIcon/init.cpp \
    Source/Interface/TrayIcon/tray_icon.cpp \
    Source/Interface/TrayIcon/tray_icon_object.cpp \
    Source/Output/const_log.cpp \
    Source/Output/log.cpp \
    Source/Output/stdout.cpp \
    Source/Setting/const_setting.cpp \
    Source/Setting/setting.cpp \
    Source/Translate/init_file.cpp \
    Source/Translate/init_message.cpp \
    Source/Translate/translate_tool.cpp

FORMS    += \
    Source/Interface/MainWindow/mainwindow.ui

# My setting

# Compile with console
# This setting can be change by qmake command line arguments
#CONFIG += console

# Enable c++11 for QT 4.8.7
QMAKE_CXXFLAGS += -std=c++11

# Fix source code with same name in different folder "multiple definition"
# https://stackoverflow.com/questions/6185129/how-to-include-2-files-with-same-name
# https://stackoverflow.com/questions/58766735/qt-qmake-doesnt-follow-source-folder-structure-when-using-config-object-para
# https://wiki.qt.io/Undocumented_QMake
CONFIG += object_parallel_to_source

# Compiler -Ofast here we go again
QMAKE_CFLAGS_RELEASE -= -O
QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O3
QMAKE_CFLAGS_RELEASE *= -Ofast

# Icon
RC_FILE = prefetch.rc

RESOURCES += \
    prefetch.qrc

# Third party library
INCLUDEPATH += $$PWD/../ThirdParty/boost
