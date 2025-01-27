QT       += core gui
QT += widgets
QT += printsupport
ICON = icon/fox.icns
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Backend/s21_calculator.c \
    ../Backend/s21_check.c \
    ../Backend/s21_op_on_numbers.c \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp


HEADERS += \
    ../Backend/s21_calculator.h \
    mainwindow.h \
    ui_mainwindow.h \
    qcustomplot.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
