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
    Object(QString path);

    void drawObject(QOpenGLWidget *mainWidget);
private:
    QPixmap img;
};

#endif // OBJECT_H
