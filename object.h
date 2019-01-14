#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <QOpenGLWidget>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QVector2D>

class Object
{
public:
    Object();
    Object(QString path, QVector2D pos);

    void drawObject(QOpenGLWidget *mainWidget);
    bool contains(QVector2D position);

protected:
    QPixmap img;
    QVector2D pos;
    int width;
    int height;
    void setSprite(QString path);
};

#endif // OBJECT_H
