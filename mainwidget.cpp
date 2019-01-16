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

#include "mainwidget.h"
#include <math.h>
#include <iostream>
#include <QColor>


MainWidget::MainWidget(QWidget *parent, int time) :
    QOpenGLWidget(parent),
    plane(0),
    texture(0),
    angularSpeed(1)
{
    rotationAxis = QVector3D(0.0, 0.0, 1.0);
    timeFps = time;
}

MainWidget::MainWidget(int time) :
    QOpenGLWidget(0),
    plane(0),
    texture(0),
    angularSpeed(1)
{
    rotationAxis = QVector3D(0.0, 0.0, 1.0);
    timeFps = time;
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete plane;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    controller.mousePressedEvent(e, ships, selectedShip);
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    controller.keyPressedEvent(event);
}

void MainWidget::timerEvent(QTimerEvent *)
{
    update();
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glSelectBuffer(selectBufferSize, selectBuffer);

//!
//!
//! GAME INITIALISATION
//!
//!
    camera.init();
    controller.setCamera(&camera);

    plane = new Plane(":/img/map2.jpg", ":/img/water.png");
    plane->init();


    initIslands(":/img/labelmap2.jpg");
    initResources();
    initObjects();

    controller.setIslands(islands);
    controller.setImg(":/img/labelmap2.jpg");
    // Use QBasicTimer because its faster than QTimer
    timer.start(timeFps, this);
}

void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::initTextures()
{
    // Load cube.png image
    //texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
    texture = new QOpenGLTexture(QImage(":/img/map2.jpg").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::initObjects(){
    Ship s(Team::BLACK, QVector2D(50, 50), this);
    ships.push_back(s);
}

void MainWidget::drawObjects(){
    for(int i = 0; i < ships.size(); ++i){
        ships[i].drawObject();
    }
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    //const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    const qreal zNear = 1.0, zFar = 100.0, fov = 45.0;
    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(camera.getPosition());
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    //geometries->drawCubeGeometry(&program);
    // Draw plane geometry
    plane->draw(&program);
    plane->incrementTime();


    drawObjects();
    drawIslands();

}

void MainWidget::initIslands(QString path)
{
    QImage img(path);
    if(!img.isNull()) {
        int labels[256];
        memset((void*) labels, 0, sizeof(labels));
        QImageReader reader(path);
        if(reader.canRead() && reader.read(&img)) {
            for(int i = 0; i < img.width(); i++) {
                for(int j = 0; j < img.height(); j++) {
                    unsigned int value = qRed(img.pixel(i,j));
                    if(value != 0) {
                        if(labels[value] == 0) {
                            //nouvelle ile
                            islands[value].setLabel(value);
                        }
                        labels[value]++;
                        Pixel p; p.px = i; p.py = j;
                        islands[value].addPixel(p);
                    }
                }
            }
        }
        // islands clean up
        for(int i = 0; i < 256; i++) {
            if(islands[i].getNbPixels() <= 150) {
                islands[i].removeAllPixels();
            } else {
                islands[i].setQLabel(this);
                std::cout << "nouvelle ile " << i << "(nbPixels : " << islands[i].getNbPixels() << std::endl;
            }
        }
    }
}

void MainWidget::initResources() {
    bool alternate = true;
    for(int i = 0; i < 256; i++) {
        if(islands[i].getNbPixels() >= 150) {
            if(alternate) {
                resources[i].setName("wood");
            } else {
                resources[i].setName("food");
            }
            resources[i].modifyMaxResources(100);
            resources[i].addNbResources(50);
            alternate = !alternate;

            islands[i].setResource(&resources[i]);
            std::cout << "ile " << i << " ressource : " << islands[i].getResource()->getName() << std::endl;

        }
    }
}

void MainWidget::drawIslands(){
    for(int i = 0; i < 256; ++i){
        Team t = islands[i].getController();
        if(t != 6){
            islands[i].drawFlag();
        }
    }
}



std::vector<Ship> MainWidget::getShips(){
    return ships;
}

Plane MainWidget::getPlane(){
    return *plane;
}

Island* MainWidget::getIsland(){
    return islands;
}
