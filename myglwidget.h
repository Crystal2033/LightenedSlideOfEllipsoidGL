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
    void makeFigure();
    void insertFigureInBuffer();
    void transformFigure();
    void reconstructFigure();
    void drawDataFromBuffer();
    void clearFigure();
    void installShaders();

    std::vector<float> upperFigurePlane;
    std::vector<unsigned int> indexesUpperPlane;

    std::vector<glm::vec3> middleFigurePlane;
    std::vector<glm::vec3> bottomFigurePlane;

    std::vector<glm::vec3> colorsUpper;
    std::vector<glm::vec3> colorsMiddle;
    std::vector<glm::vec3> colorsBottom;

    std::vector<glm::vec3> upAndMidFlatsFences;
    std::vector<glm::vec3> midAndBotFlatsFences;

    std::vector<glm::vec3> upAndMidFlatsColors;
    std::vector<glm::vec3> midAndBotFlatsColors;

    int valueOfEdges = 3;
    GLuint flatsVBO[3];
    GLuint flatsColor[3];

    GLuint fencesVBO[2];
    GLuint fencesColor[2];

public:
    void updateObserver(const float value, CHANGE_TYPE changeType) override;

};

#endif // MYGLWIDGET_H
