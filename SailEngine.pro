QT       += core gui widgets opengl

TARGET = SailEngine
TEMPLATE = app

LIBS += -lopengl32

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
    island.cpp \
    base.cpp \
    calendar.cpp \
    camera.cpp \
    controller.cpp \
    ia.cpp \
    island.cpp \
    light.cpp \
    main.cpp \
    mainwidget.cpp \
    object.cpp \
    plane.cpp \
    player.cpp \
    resource.cpp \
    ship.cpp

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
    island.h \
    teams.h \
    pixel.h \
    base.h \
    calendar.h \
    camera.h \
    controller.h \
    ia.h \
    island.h \
    light.h \
    mainwidget.h \
    object.h \
    pixel.h \
    plane.h \
    player.h \
    resource.h \
    ship.h \
    teams.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target
