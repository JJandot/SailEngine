#include "camera.h"

Camera::Camera()
{

}

void Camera::init(){
    position = QVector3D(0.0,0.0,-5.0);
}

void Camera::left()
{
    position[0] -= 0.05;
}

void Camera::right()
{
    position[0] += 0.05;
}

void Camera::up()
{
    position[2] += 0.05;
}

void Camera::down()
{
    position[2] -= 0.05;
}

void Camera::forward()
{
    position[1] += 0.05;
}

void Camera::backward()
{
    position[1] -= 0.05;
}

QVector3D Camera::getPosition()
{
    return position;
}
