#include "island.h"

Island::Island() {
    label = 0;
    team = Team::NONE;
}

Island::Island(int labelId)
{
    label = labelId;
    team = Team::NONE;
}

Island::Island(int labelId, QList<Resource> resources)
{
    label = labelId;
    addResources(resources);
    team = Team::NONE;
}

void Island::addResources(QList<Resource> res)
{
    for(Resource r : res)
        if(!resources.contains(r))
            res.append(res);
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

Team Island::getController() { return team; }

QList<Resource> Island::getResources() { return resources; }

int Island::getNbPixels()
{
    return islandPixel.size();
}

void Island::setQLabel(QOpenGLWidget *mainWidget)
{
    qlabel = new QLabel(mainWidget);
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


}
void Island::harvest(Resource r, int _value)
{
    r.addNbResources(-_value);
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

