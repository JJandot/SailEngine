/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "plane.h"
#include <iostream>
#include <cmath>

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D color;
};

Plane::Plane(QString hmPath, QString hmWaterPath)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    heightmapPath = hmPath;
    heightmap = QImage(heightmapPath);
    heightmapWaterPath = hmWaterPath;
    heightmapWater = QImage(heightmapWaterPath);

    time = 0;

    // Initializes cube geometry and transfers it to VBOs
    init();
}

Plane::~Plane()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
void Plane::init()
{
    QVector3D colour;

    nbVertices = 64;
    // For plane, we need 8 vertices on the same plane z=0
    VertexData vertices[nbVertices*nbVertices] = {};

    // heightmap
    std::vector<double> grayLevelHeightmap;
    int indiceHeightmap = 0;
    QImage img(heightmap.width(), heightmap.height(), heightmap.format());
    QImageReader reader(heightmapPath);

    double ratio = img.size().height()/nbVertices;
    if (reader.read(&img)) {
        for(int i = 0; i < nbVertices; ++i){
            for(int j = 0; j < nbVertices; ++j){
                int gray = qGray(img.pixel(i * ratio, j * ratio));
                //printf("test(%d;%d) %d = %lf\n",i,j, gray, (double) gray/255);
                grayLevelHeightmap.push_back((double) gray/255);
            }
        }
    }

    // water heightmap
    std::vector<double> grayLevelWater;
    int indiceWater = 0;
    QImage imgW(heightmapWater.width(), heightmapWater.height(), heightmapWater.format());
    QImageReader readerW(heightmapWaterPath);
    ratio = imgW.size().height()/nbVertices;
    if (readerW.read(&imgW)) {
        for(int i = 0; i < nbVertices; ++i){
            for(int j = 0; j < nbVertices; ++j){
                int gray = qGray(imgW.pixel(i * ratio, j * ratio));
                grayLevelWater.push_back((double) gray/255); //valeurs comprises entre -1 et 1
            }
        }
    }

    double incr = 2./nbVertices;
    for(int j = 0; j < nbVertices; j++) {
        for(int i = 0; i < nbVertices; i++) {
            QVector3D positionVector;
            if(grayLevelHeightmap[indiceHeightmap] <= 0.1) {
                // water
                colour = QVector3D(0.1 * grayLevelWater[indiceWater], 0.1 * grayLevelWater[indiceWater], grayLevelWater[indiceWater]);
                positionVector = QVector3D(i*incr, j*incr, grayLevelWater[indiceWater] * 0.2);
            } else {
                // land
                if(grayLevelHeightmap[indiceHeightmap] <= 0.2) {
                    // sand
                    colour = QVector3D(1.0 * grayLevelHeightmap[indiceHeightmap] + 0.3, 0.3 + 1.0* grayLevelHeightmap[indiceHeightmap], grayLevelHeightmap[indiceHeightmap]);
                } else {
                    // forest
                    if(grayLevelHeightmap[indiceHeightmap] <= 0.5) {
                        colour = QVector3D(0.0, 1.0 * grayLevelHeightmap[indiceHeightmap], 0.0);
                    } else {
                        // mountain
                        colour = QVector3D(1.0 * grayLevelHeightmap[indiceHeightmap], 1.0* grayLevelHeightmap[indiceHeightmap], 1.0* grayLevelHeightmap[indiceHeightmap]);
                    }
                }
                positionVector = QVector3D(i*incr, j*incr, grayLevelHeightmap[indiceHeightmap]);
            }

            vertices[i+j*nbVertices] = {positionVector,
                                        QVector2D(i*(1./(nbVertices-1)), j*(1./(nbVertices-1))),
                                        QVector3D(colour[0], colour[1], colour[2])};
            indiceWater++;
            //indiceWater%imgW.size().height();
            indiceHeightmap++;
        }
        //std::cout << std::endl;
    }
    //std::cout << "indices" << std::endl;
    GLushort indices[nbVertices*nbVertices*nbVertices] = {};
    // bg, bd, hg, hd
    // 16, 0, 17, 1, ... n, n : one line

    int offset = 0;
    int temp = 0;
    for(int j = 0; j < nbVertices-1; j++) {
        if(j>0) {
            indices[j*nbVertices+offset] = j*nbVertices+nbVertices;
            //std::cout << indices[j*n+offset] << "|";
            offset++;
        }
        for(int i = 0; i < nbVertices; i++) {
            indices[i+j*nbVertices+offset] = j*nbVertices+i+nbVertices;
            indices[i+j*nbVertices+1+offset] = (j-1)*nbVertices+i+nbVertices;
            temp = indices[i+j*nbVertices+1+offset];
            //std::cout << indices[i+j*n+offset] << ";" << indices[i+j*n+1+offset] << "|";
            offset++;
        }
        if(j<(nbVertices-2)) {
            indices[nbVertices+j*nbVertices+offset] = temp;
            //std::cout << indices[n+j*n+offset];
            offset++;
        }
        //std::cout << std::endl;
    }

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbVertices*nbVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbVertices*nbVertices*nbVertices * sizeof(GLushort));
//! [1]

}

void Plane::draw(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);
    //color
    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, nbVertices*nbVertices*nbVertices, GL_UNSIGNED_SHORT, 0);
}

void Plane::incrementTime() { time ++; }
