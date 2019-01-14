#include "object.h"

Object::Object(){}

Object::Object(QString path, QVector2D pos)
{
    img = QPixmap(path);
    width = img.width();
    height = img.height();
}

void Object::drawObject(QOpenGLWidget *mainWidget)
{
    QLabel *label = new QLabel(mainWidget);
    label->setGeometry(pos.x(), pos.y(), width, height);
    label->setPixmap(img);
}

void Object::setSprite(QString path){
    this->img = QPixmap(path);
    width = img.width();
    height = img.height();
}

bool Object::contains(QVector2D position){
    return position.x() > pos.x() &&
            position.x() < pos.x() + width &&
            position.y() > pos.y() &&
            position.y() < pos.y() + height;

}
