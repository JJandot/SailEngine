#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "camera.h"
#include "object.h"
#include "ship.h"

#include <iostream>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>


class Camera;
class Object;
class Ship;

class Controller
{
public:
    Controller();

    void keyPressedEvent(QKeyEvent *event);
    void mousePressedEvent(QMouseEvent *event, std::vector<Ship> ships, Ship &selectedShip);
    void setCamera(Camera *camera);

private:
    QVector2D mousePressedPosition;
    void debugMousePos();
    Camera *camera;
    bool isSelected = false;
};

#endif // CONTROLLER_H
