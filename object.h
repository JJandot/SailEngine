#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <QOpenGLWidget>
#include <QLabel>
#include <QPixmap>
#include <QFile>

class Object
{
public:
    Object();
    Object(QString path);

    void drawObject(QOpenGLWidget *mainWidget);
protected:
    QPixmap img;
    void setSprite(QString path);
};

#endif // OBJECT_H
