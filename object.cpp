#include "object.h"


Object::Object(QString path)
{
    img = QPixmap(path);
}

void Object::drawObject(QOpenGLWidget *mainWidget)
{
    QLabel *label = new QLabel(mainWidget);
    label->setGeometry(50, 50, img.width(), img.height());
    label->setPixmap(img);
}
