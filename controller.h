#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "camera.h"

#include <iostream>
#include <QKeyEvent>
#include <QMouseEvent>

class Camera;

class Controller
{
public:
    Controller();

    void keyPressedEvent(QKeyEvent *event);
    void mousePressedEvent(QMouseEvent *event);
    void setCamera(Camera *camera);

private:
    QVector2D mousePressedPosition;
    void debugMousePos();
    Camera *camera;
};

#endif // CONTROLLER_H
