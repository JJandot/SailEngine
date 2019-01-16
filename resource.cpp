#include "resource.h"

Resource::Resource()
{
    name = "";
    value = 0;
    max = 0;
}

Resource::Resource(std::string _name, int _value, int _max)
{
    name = _name;
    value = _value;
    max = _max;
}

bool Resource::operator==(const Resource& r) {
    if(name == r.name)
        return true;
    return false;
}


int Resource::getNbResources()
{
   return value;
}

void Resource::addNbResources(int _value)
{
    value += _value;
    if(value < 0)
        value = 0;
    if(value > max)
        value = max;
}

void Resource::setName(std::string _name) {
    name = _name;
}

std::string Resource::getName()
{
    return name;
}

int Resource::getMaxResources()
{
    return max;
}

void Resource::modifyMaxResources(int _max)
{
    max = _max;
}


void Resource::setPixmap(QString path) {
    this->img = QPixmap(path);

}

QPixmap Resource::getPixmap() { return img; }
