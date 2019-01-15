#include "object.h"

Object::Object(){
    test = "";
}

Object::Object(QString path, QVector2D pos)
{
    img = QPixmap(path);
    width = img.width();
    height = img.height();
    test = "";
}

void Object::drawObject(QOpenGLWidget *mainWidget)
{
    label = new QLabel(mainWidget);
    label->setGeometry(pos.x(), pos.y(), width, height);
    label->setPixmap(img);
    label->setProperty("selected", QVariant(false));
    label->setStyleSheet("* [selected='true'] { background-color: yellow }");
    if(isSelected){
        label->update();
        label->updateGeometry();
    }
    label->update();
    label->updateGeometry();
}

void Object::setPos(QVector2D pos){
    this->pos = pos;
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

void Object::printPos(){
    std::cout << pos.x() << " : " << pos.y() << std::endl;
}

QVector2D Object::getPos(){
    return pos;
}

int Object::getWidth(){
    return width;
}

int Object::getHeight(){
    return height;
}

void Object::setSelected(bool isSelected){
    this->isSelected = isSelected;
    std::cout << "selected" << std::endl;
    label->setProperty("selected", QVariant(true));
}

bool Object::getSelected(){
    return  isSelected;
}

void Object::testMove(){
    pos.setX(500);
    pos.setY(500);
    //label->setGeometry(500, 500, width, height);
}
