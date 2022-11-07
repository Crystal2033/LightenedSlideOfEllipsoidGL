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
    void setSlidersValues(const int value, const CHANGE_TYPE sliderType);
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    float xRotTheta = 0.0f;
    float yRotTheta= 0.0f;
    float zRotTheta= 0.0f;

    float xPosLight = 0.0;
    float yPosLight = 0.0;
    float zPosLight = 0.0;

    float rLightIntensity = 0.0;
    float gLightIntensity = 0.0;
    float bLightIntensity = 0.0;

    float atenuationConstant = 0.0;
    float atenuationLinear = 0.0;
    float atenuationQuadratic = 0.0;

    float spotCutOff = 0.0;
    float spotExponent = 0.0;

    void drawFigure();
    void makeLighting();
    void drawLightSquare();
    void makeFigure();
    void insertDataInBuffer(GLuint* indexBuffer, std::vector<glm::vec3>& data, const int index);
    void insertFigureInBuffer();
    void transformFigure();
    void reconstructFigure();
    void drawDataFromBuffer();
    void clearFigure();
    void drawArrays(GLenum mode, GLint first, GLsizei count);
    //void installShaders();
    void insertColorInVertexes(std::vector<glm::vec3>& colorData, const float r, const float g, const float b);
    void countAndInsertNormals(const std::vector<glm::vec3>& fences, std::vector<glm::vec3>& normals, const int index, const int valueOfPush);


    std::vector<glm::vec3> upperFigurePlane;
    std::vector<glm::vec3> middleFigurePlane;
    std::vector<glm::vec3> bottomFigurePlane;

    std::vector<glm::vec3> colorsUpper;
    std::vector<glm::vec3> colorsMiddle;
    std::vector<glm::vec3> colorsBottom;

    std::vector<glm::vec3> upAndMidFlatsFences;
    std::vector<glm::vec3> midAndBotFlatsFences;

    std::vector<glm::vec3> upAndMidFlatsColors;
    std::vector<glm::vec3> midAndBotFlatsColors;

    std::vector<glm::vec3> upperFlatNormals;
    std::vector<glm::vec3> bottomFlatNormals;
    std::vector<glm::vec3> middleFlatNormals;
    std::vector<glm::vec3> upAndMidFenceNormals;
    std::vector<glm::vec3> midAndBotFenceNormals;

    int valueOfEdges = 3;
    GLuint flatsVBO[3];
    GLuint flatsColor[3];

    GLuint fencesVBO[2];
    GLuint fencesColor[2];

    GLuint normalsVBO[5];

public:
    void updateObserver(const float value, CHANGE_TYPE changeType) override;

};

#endif // MYGLWIDGET_H
