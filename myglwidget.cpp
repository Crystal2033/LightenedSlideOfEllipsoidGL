#include "myglwidget.h"
#include <fstream>

MyGLWidget::MyGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    ellipsoid = new SlidedEllipsoid();
}

void MyGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);
    resizeGL(width(), height());
    reconstructFigure();
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, aspect, 0.1f, 100.0f);

}

void MyGLWidget::paintGL()
{
    glClearColor(0.0, 0.0, 0.0, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawFigure();

    glFlush();
}

void MyGLWidget::drawFigure()
{
    transformView();
    insertFigureInBuffer();
    drawDataFromBuffer();
}

void MyGLWidget::makeLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);

    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        GLfloat lightPosition[] = {xPosLight, yPosLight, zPosLight, 1};
        GLfloat lightColor[] = {rLightIntensity, gLightIntensity, bLightIntensity, 1};
        GLfloat specular[] = {rSpecular, gSpecular, bSpecular, 1};

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutOff);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atenuationConstant);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, atenuationLinear);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, atenuationQuadratic);

    glPopMatrix();
}


void MyGLWidget::insertDataInBuffer(GLuint* indexBuffer, std::vector<glm::vec3> &data, const int index)
{
    glGenBuffers(1, &indexBuffer[index]);
    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer[index]);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW
}

void MyGLWidget::insertFigureInBuffer()
{
        insertDataInBuffer(flatsVBO, ellipsoid->upperFigurePlane, 0);
        insertDataInBuffer(flatsVBO, ellipsoid->middleFigurePlane, 1);
        insertDataInBuffer(flatsVBO, ellipsoid->bottomFigurePlane, 2);

        insertDataInBuffer(flatsColorVBO, ellipsoid->colorsUpper, 0);
        insertDataInBuffer(flatsColorVBO, ellipsoid->colorsMiddle, 1);
        insertDataInBuffer(flatsColorVBO, ellipsoid->colorsBottom, 2);

        insertDataInBuffer(fencesVBO, ellipsoid->upAndMidFlatsFences, 0);
        insertDataInBuffer(fencesVBO, ellipsoid->midAndBotFlatsFences, 1);

        insertDataInBuffer(fencesColorVBO, ellipsoid->upAndMidFlatsColors, 0);
        insertDataInBuffer(fencesColorVBO, ellipsoid->midAndBotFlatsColors, 1);

        insertDataInBuffer(normalsVBO, ellipsoid->upperFlatNormals, 0);
        insertDataInBuffer(normalsVBO, ellipsoid->middleFlatNormals, 1);
        insertDataInBuffer(normalsVBO, ellipsoid->bottomFlatNormals, 2);
        insertDataInBuffer(normalsVBO, ellipsoid->upAndMidFenceNormals, 3);
        insertDataInBuffer(normalsVBO, ellipsoid->midAndBotFenceNormals, 4);
}



void MyGLWidget::transformView()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(xCameraPos, yCameraPos, zCameraPos, 0, 0, 0, 0, 1, 0);

    //glTranslatef(0, 0, -1);
    glRotatef(xRotTheta, 1, 0, 0);
    glRotatef(yRotTheta, 0, 1, 0);
    glRotatef(zRotTheta, 0, 0, 1);
    //glTranslatef(0, 0, 1);
    makeLighting();

}

void MyGLWidget::updateObserver(const float value, CHANGE_TYPE changeType)
{
    switch (changeType)
        {
        case XROT: {
            xRotTheta = value;
            break;
        }
        case YROT: {
            yRotTheta = value;
            break;
        }
        case ZROT: {
            zRotTheta = value;
            break;
        }

        case APROX: {
            ellipsoid->valueOfEdges = value;
            reconstructFigure();
            break;
        }
        case XSTRETCH: {
            ellipsoid->xStretch = value / 5.0;
            reconstructFigure();
            break;
        }
        case YSTRETCH: {
            ellipsoid->yStretch = value / 5.0;
            reconstructFigure();
            break;
        }

        case SPOT_CUT_OFF:{
            spotCutOff = value;
            break;
        }
        case SPOT_EXPONENT:{
            spotExponent = value;
            break;
        }
        case SHINESS:{
            shiness = value;
            break;
        }

        case XLIGHT:{
             xPosLight = value;
             break;
        }
        case YLIGHT:{
            yPosLight = value;
            break;
        }
        case ZLIGHT:{
            zPosLight = value;
            break;
        }

        case RINTENSITY:{
            rLightIntensity = value/200.0;
            break;
        }
        case GINTENSITY:{
            gLightIntensity = value/200.0;
            break;
        }
        case BINTENSITY:{
            bLightIntensity = value/200.0;
            break;
        }

        case RSPECULAR:{
            rSpecular = value/200.0;
            break;
        }
        case GSPECULAR:{
            gSpecular = value/200.0;
            break;
        }
        case BSPECULAR:{
            bSpecular = value/200.0;
            break;
        }

        case ATENUATION_CONST:{
            atenuationConstant = value/10.0;
            break;
        }
        case ATENUATION_LIN:{
            atenuationLinear = value/10.0;
            break;
        }
        case ATENUATION_QUAD:{
            atenuationQuadratic = value/25.0;
            break;
        }

        default:
            exit(0);
        }

    update();
}

void MyGLWidget::getKeyBoardEvent(QKeyEvent *event)
{
    keyPressEvent(event);
}


MyGLWidget::~MyGLWidget()
{
    delete ellipsoid;
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        yCameraPos += 0.5;
        break;

    case Qt::Key_S:
        yCameraPos -= 0.5;
        break;

    case Qt::Key_A:
        xCameraPos -= 0.5;
        break;

    case Qt::Key_D:
        xCameraPos += 0.5;
        break;

    case Qt::Key_F:
        zCameraPos += 0.5;
        break;

    case Qt::Key_R:
        zCameraPos -= 0.5;
        break;

    default:
        event->ignore();
        break;
    }

    update();
}



void MyGLWidget::reconstructFigure()
{
    ellipsoid->clearFigure();
    ellipsoid->makeFigure();
    insertFigureInBuffer();
}

void MyGLWidget::drawDataFromBuffer()
{

    for(int i = 0; i < 3; i++){
        glBindBuffer(GL_ARRAY_BUFFER, flatsVBO[i]);
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, flatsColorVBO[i]);
        glColorPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, normalsVBO[i]);
        glNormalPointer(GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        drawArrays(GL_POLYGON, 0, ellipsoid->valueOfEdges);
    }

    for(int i = 0; i < 2; i++){
        glBindBuffer(GL_ARRAY_BUFFER, fencesVBO[i]);
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, fencesColorVBO[i]);
        glColorPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, normalsVBO[i + 3]);
        glNormalPointer(GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        drawArrays(GL_QUADS, 0, ellipsoid->valueOfEdges * 4);
    }

}

void MyGLWidget::drawArrays(GLenum mode, GLint first, GLsizei count)
{

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glDrawArrays(mode, first, count);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void MyGLWidget::setSlidersValues(const int value, const CHANGE_TYPE sliderType)
{
    updateObserver(value, sliderType);
}
