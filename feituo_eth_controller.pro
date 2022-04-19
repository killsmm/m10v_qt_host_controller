QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets webengine

CONFIG+= static
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camerawebview.cpp \
    filedownloader.cpp \
    httpcameracontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    messagereceiver.cpp

HEADERS += \
    camerawebview.h \
    filedownloader.h \
    httpcameracontroller.h \
    mainwindow.h    \
    messagereceiver.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32: LIBS += -L$$PWD/../../../../../../src/vcpkg/installed/x86-windows/lib/ -llibzmq-mt-4_3_4

INCLUDEPATH += $$PWD/../../../../../../src/vcpkg/installed/x86-windows/include
DEPENDPATH += $$PWD/../../../../../../src/vcpkg/installed/x86-windows/include
