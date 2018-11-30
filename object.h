#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <QVector3D>
#include <QVector2D>

class Object
{
public:
    Object();
    bool loadObject(std::string path, std::vector<QVector3D> &outVertices, std::vector<QVector2D> &outUvs, std::vector<QVector3D> &outNormals);
};

#endif // OBJECT_H
