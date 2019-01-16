#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "camera.h"
#include "object.h"
#include "ship.h"
#include "island.h"

#include <iostream>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QImage>
#include <QImageReader>


class Camera;
class Object;
class Ship;
class Island;

class Controller
{
public:
    Controller();

    void keyPressedEvent(QKeyEvent *event);
    void mousePressedEvent(QMouseEvent *event, std::vector<Ship> &ships, int &indice);
    void setCamera(Camera *camera);
    void setIslands(Island _islands[]);
    void setImg(QString path);

private:
    QVector2D mousePressedPosition;
    void debugMousePos();
    Camera *camera;
    bool isSelected = false;
    Island* islands;
    QImage img;
    QString path;
};

#endif // CONTROLLER_H
