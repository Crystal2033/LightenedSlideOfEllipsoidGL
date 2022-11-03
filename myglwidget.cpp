#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget* parent)
{
    qInfo()<< "Nice MyGLWidget";
}

void MyGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    resizeGL(width(), height());
    qInfo() << "initializeGL";

    reconstructFigure();
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //GLfloat x = (GLfloat)w / h;
    //glFrustum(-x, x, -1.0, 1.0, -2.0, 15.0);
    //gluLookAt(0,0,0,0,0,0,0,0,0);
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::paintGL()
{
    qInfo() << "paintGL";

    glLoadIdentity();
    glClearColor(0.39, 0.58, 0.93, 0.2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawFigure();

    glFlush();
}

void MyGLWidget::drawFigure()
{
    reconstructFigure();

    transformFigure();

    drawDataFromBuffer();
}

void MyGLWidget::makeFigure()
{
    float x, y, z;
    int a = 1;
    int b = 1;

    for(int i = 0; i < valueOfEdges; i++){
        x = cos(i*2*M_PI/valueOfEdges)/a;
        //qInfo() << "x = " << x;
        y = sin(i*2*M_PI/valueOfEdges)/b;
        //qInfo() << "y = " << y;
        z = 0.5;
        //qInfo() << "z = " << z;
        figure.push_back(glm::vec3(x, y, z));
        colors.push_back(glm::vec3(abs(x), abs(y), abs(z)));
    }
}

void MyGLWidget::insertFigureInBuffer()
{
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, figure.size() * sizeof(glm::vec3), figure.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MyGLWidget::transformFigure()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glRotatef(xRotTheta, 1, 0, 0);
    glRotatef(yRotTheta, 0, 1, 0);
    glRotatef(zRotTheta, 0, 0, 1);
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
            valueOfEdges = value;
            break;
        }
        default:
            exit(0);
        }
    update();
}

void MyGLWidget::reconstructFigure()
{
    figure.clear();
    colors.clear();
    makeFigure();
    insertFigureInBuffer();
}

void MyGLWidget::drawDataFromBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_POLYGON, 0, valueOfEdges);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
