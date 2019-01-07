#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

/*
 * Une ressource a un nom, une valeur initiale et une valeur maximale
 * On peut ajouter/enlever des ressources, et modifier le maximum de ressource
 */

class Resource
{
public:
    Resource(std::string _name, int _value, int _max);

    bool operator==(const Resource& r);

    int getNbResources();
    void addNbResources(int _value);

    int getMaxResources();
    void modifyMaxResources(int _max);

    std::string getName();

private:
    int value;
    int max;
    std::string name;
};

#endif // RESOURCE_H
