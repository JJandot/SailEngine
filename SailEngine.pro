QT       += core gui widgets

TARGET = SailEngine
TEMPLATE = app

SOURCES += main.cpp \
    mainwidget.cpp \
    plane.cpp \
    object.cpp \
    camera.cpp \
    light.cpp \
    base.cpp \
    controller.cpp \
    player.cpp \
    ship.cpp \
    resource.cpp \
    ia.cpp \
    island.cpp

HEADERS += \
    mainwidget.h \
    plane.h \
    object.h \
    camera.h \
    light.h \
    base.h \
    controller.h \
    player.h \
    ship.h \
    resource.h \
    ia.h \
    island.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=
