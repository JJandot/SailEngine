#include "island.h"

Island::Island() {
    label = 0;
    team = Team::NONE;
    attackPower = 5;
}

Island::Island(int labelId)
{
    label = labelId;
    team = Team::NONE;
    attackPower = 5;
}

Island::Island(int labelId, Resource *res)
{
    label = labelId;
    resource = res;
    team = Team::NONE;
    attackPower = 5;
}

void Island::addResource(int value)
{
    resource->addNbResources(value);
}

void Island::addPixels(QList<Pixel> px)
{
    for(Pixel p : px)
        addPixel(p);
}

void Island::addPixel(Pixel px)
{
    islandPixel.append(px);
}

void Island::removeAllPixels()
{
    islandPixel.clear();
}

void Island::setResource(Resource *res) {
    resource = res;
}

Team Island::getController() { return team; }

Resource* Island::getResource() { return resource; }

int Island::getNbPixels()
{
    return islandPixel.size();
}

void Island::setQLabel(QOpenGLWidget *mainWidget)
{
    qlabel = new QLabel(mainWidget);
    qlabelR = new QLabel(mainWidget);
}

void Island::setLabel(int id) { label = id; }
void Island::setController(Team playerTeam) {
    team = playerTeam;
    QString path = ":/img/teams/";
    switch(team){
        case Team::BLACK:
            path += "black/";
            break;
        case Team::BLUE:
            path += "blue/";
            break;
        case Team::GREEN:
            path += "green/";
            break;
        case Team::RED:
            path += "red/";
            break;
        case Team::WHITE:
            path += "white/";
            break;
        case Team::YELLOW:
            path += "yellow/";
            break;
        default:
            break;
    }
    path += "flag.png";

    setPath(path);
    std::cout << path.toStdString() << std::endl;


}
void Island::harvest(int _value)
{
    resource->addNbResources(-_value);
}

void Island::setPath(QString path){
    this->img = QPixmap(path);
}

void Island::drawFlag()
{
    float x = (float)islandPixel[0].py / (float)1280 * (float)900;
    float y = (float)islandPixel[0].px / (float)1280 * (float)900;
    qlabel->setGeometry(x, y, img.width(), img.height());
    qlabel->setPixmap(img);
}


int Island::getAttackPower() const
{
    return attackPower;
}

Pixel Island::getPosition() {
    return islandPixel[0];
}

void Island::drawResource()
{
    float x = ((float)islandPixel[0].py-100) / (float)1280 * (float)900;
    float y = ((float)islandPixel[0].px) / (float)1280 * (float)900;
    qlabelR->setGeometry(x, y, img.width(), img.height());
    qlabelR->setPixmap(resource->getPixmap());
}
