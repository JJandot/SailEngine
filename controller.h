#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "camera.h"
#include "object.h"

#include <iostream>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>


class Camera;
class Object;

class Controller
{
public:
    Controller();

    void keyPressedEvent(QKeyEvent *event);
    void mousePressedEvent(QMouseEvent *event, std::vector<Object> objects, Object &selectedObject);
    void setCamera(Camera *camera);

private:
    QVector2D mousePressedPosition;
    void debugMousePos();
    Camera *camera;
};

#endif // CONTROLLER_H
