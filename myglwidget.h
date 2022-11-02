/***************************************************************************
 *                                                                         *
 *   Copyright (C) 27.10.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QOpenGLWidget>
#include <qopenglfunctions.h>
#include <gl/GLU.h>
#include "Patterns/observer.h"
#include <gl/GL.h>
#include <glm.hpp>

class MyGLWidget : public  QOpenGLWidget, public QOpenGLFunctions, public InterfaceObserver{

public:
    explicit MyGLWidget(QWidget* parent = nullptr);
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    float xRotTheta = 0.0f;
    float yRotTheta= 0.0f;
    float zRotTheta= 0.0f;
    void drawFigure();
    void initFigure();

    std::vector<glm::vec3> figure;
    std::vector<glm::vec3> colors;
    int valueOfEdges = 3;
    GLuint vertexVBO;
    GLuint colorVBO;

public:
    void updateObserver(const float value, CHANGE_TYPE changeType) override;
};

#endif // MYGLWIDGET_H
