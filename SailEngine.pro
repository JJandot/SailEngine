QT       += core gui widgets

TARGET = SailEngine
TEMPLATE = app

SOURCES += main.cpp


SOURCES += \
    mainwidget.cpp \
    plane.cpp

HEADERS += \
    mainwidget.h \
    plane.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=
