QT       += core gui
QT       += opengl
QT       += openglwidgets
LIBS += -lglu32 -lopengl32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += D:\Paul\Programming\libraries\glm\glm\glm #Insert your glm path
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sliders/classicslider.cpp \
    Sliders\abstractslider.cpp \
    main.cpp \
    mainwindow.cpp \
    myglwidget.cpp \
    slidedellipsoid.cpp

HEADERS += \
    Sliders/classicslider.h \
    Sliders\abstractslider.h \
    mainwindow.h \
    myglwidget.h \
    Patterns\observer.h \
    Patterns\subject.h \
    slidedellipsoid.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
