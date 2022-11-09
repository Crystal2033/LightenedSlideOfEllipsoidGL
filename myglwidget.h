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
#include "slidedellipsoid.h"
#include <QKeyEvent>
#include <QWheelEvent>
#define INTENSITY_DENUM 200.0
#define SPECULAR_DENUM 200.0
#define LIN_AND_CONST_ATEN_DENUM 10.0
#define QUADRATIC_ATEN_DENUM 10.0
#define STRETCH_DENUM 5.0


class MyGLWidget : public  QOpenGLWidget, public QOpenGLFunctions, public InterfaceObserver{
public:
    explicit MyGLWidget(QWidget* parent = nullptr);
    void setSlidersValues(const int value, const CHANGE_TYPE sliderType);
    void updateObserver(const float value, CHANGE_TYPE changeType) override;
    void getKeyBoardEvent(QKeyEvent* event);
    glm::vec3 getCurrPosInWorld() const;

    ~MyGLWidget();
private:
    void keyPressEvent(QKeyEvent *ev) override;

    SlidedEllipsoid* ellipsoid;
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

    float rSpecular = 0.0;
    float gSpecular = 0.0;
    float bSpecular = 0.0;

    int shiness = 0;

    float xCameraPos = 0.0;
    float yCameraPos = 0.0;
    float zCameraPos = 4.5;


    void drawFigure();
    void makeLighting();

    void insertDataInBuffer(GLuint* indexBuffer, std::vector<glm::vec3>& data, const int index);
    void insertFigureInBuffer();

    void transformView();
    void reconstructFigure();
    void drawDataFromBuffer();

    void drawArrays(GLenum mode, GLint first, GLsizei count);


    GLuint flatsVBO[3];
    GLuint flatsColorVBO[3];

    GLuint fencesVBO[2];
    GLuint fencesColorVBO[2];

    GLuint normalsVBO[5];

};

#endif // MYGLWIDGET_H
