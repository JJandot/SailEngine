#include "controller.h"

Controller::Controller()
{

}

void Controller::setCamera(Camera *camera)
{
    this->camera = camera;
}

void Controller::keyPressedEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q) {
        camera->left();
    }
    if(event->key() == Qt::Key_D) {
        camera->right();
    }

    if(event->key() == Qt::Key_Z) {
        camera->up();
    }
    if(event->key() == Qt::Key_S) {
        camera->down();
    }

    if(event->key() == Qt::Key_R) {
        camera->forward();
    }
    if(event->key() == Qt::Key_F) {
        camera->backward();
    }
}

void Controller::mousePressedEvent(QMouseEvent *event, std::vector<Object> objects, Object &selectedObject)
{
    mousePressedPosition = QVector2D(event->x(), event->y());
    debugMousePos();

    for(Object o : objects){
        if(o.contains(mousePressedPosition)){
            std::cout << "click inside" << std::endl;
            selectedObject = o;
            selectedObject.setSelected(true);
            return; //pour l'opti
        }
    }
}

void Controller::debugMousePos()
{
    std::cout << "Clicked at " << mousePressedPosition.x() << " ; " << mousePressedPosition.y() << std::endl;
}
