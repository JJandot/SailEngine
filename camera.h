#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <iostream>

class Camera
{
public:
    Camera();
    QVector3D getPosition();
    void init();
    void left();
    void right();
    void up();
    void down();
    void forward();
    void backward();

private:
    QVector3D position;
};

#endif // CAMERA_H
