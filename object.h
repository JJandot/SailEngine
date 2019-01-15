#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <QOpenGLWidget>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QVector2D>
#include <QVariant>

class Object
{
public:

    Object();
    Object(QString path, QVector2D pos);

    void drawObject(QOpenGLWidget *mainWidget);
    bool contains(QVector2D position);
    void printPos();
    QVector2D getPos();
    int getWidth();
    int getHeight();
    void setSelected(bool isSelected);
    bool getSelected();
    void testMove();
    void setPos(QVector2D pos);

protected:
    QPixmap img;
    QVector2D pos;
    QLabel *label;
    int width;
    int height;
    void setSprite(QString path);
    bool isSelected = false;
    std::string test;


};

#endif // OBJECT_H
