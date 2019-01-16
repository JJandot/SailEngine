#include "controller.h"

Controller::Controller()
{
}

void Controller::setCamera(Camera *camera)
{
    this->camera = camera;
}

void Controller::setIslands(Island _islands[])
{
    islands = _islands;
}

void Controller::setImg(QString path)
{
    img = QImage(path);
    this->path = path;
}

void Controller::setMainWidget(QOpenGLWidget *mainWidget) {
    mw = mainWidget;
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

    if(event->key() == Qt::Key_B) {
        //spawn bateau sur une île controlée
        //TODO: actuellement gérer dans mainWidget -> gérer dans controller
    }
}

void Controller::mousePressedEvent(QMouseEvent *event, std::vector<Ship> &ships, int &indice)
{
    mousePressedPosition = QVector2D(event->x(), event->y());

    if(isSelected == false){
        for(int i = 0; i < ships.size(); ++i){
            if(ships[i].contains(mousePressedPosition)){
                std::cout << "click inside" << std::endl;
                indice = i;
                ships[i].setSelected(true);
                isSelected = true;
                return; //pour l'opti
            }
        }
    }
    else{
        QVector2D dest(event->x(), event->y());
        unsigned int value;
        QImageReader reader(path);
        if(reader.canRead() && reader.read(&img)) {
            value = qRed(img.pixel(dest.y() / 900 * 1280, dest.x() / 900 * 1280));
        }

        if(value != 0){
            if(islands[value].getController() == 6){
                std::cout << "free island" << std::endl;
            }
            ships[indice].setOnIsland(value);
        }
        ships[indice].setOnIsland(value);
        ships[indice].setDestination(dest);
        isSelected = false;
    }
}

void Controller::debugMousePos()
{
    std::cout << "Clicked at " << mousePressedPosition.x() << " ; " << mousePressedPosition.y() << std::endl;
}
