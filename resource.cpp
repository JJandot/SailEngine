#include "resource.h"

Resource::Resource(std::string _name, int _value, int _max)
{
    name = _name;
    value = _value;
    max = _max;
}

Resource::operator ==(const Resource& r) {
    if(name == r.getName())
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
