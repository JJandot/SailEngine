#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QFile>

class Object
{
public:
    Object(QString path);
    bool loadObject(QString path, std::vector<QVector3D> &outVertices, std::vector<QVector2D> &outUvs, std::vector<QVector3D> &outNormals);

    void drawObject(QOpenGLShaderProgram *program);
private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    void initObject(QString path);

};

#endif // OBJECT_H
