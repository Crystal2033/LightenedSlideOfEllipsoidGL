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
    //glViewport(0, 0, w, h);
    qInfo() << "resizeGL";
    GLfloat aspect = (GLfloat)w / (GLfloat)h; // Compute aspect ratio of window
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset
    //gluPerspective(60.0f, aspect, 0.1f, 100.0f);
    gluPerspective(60.0f, aspect, 0.1f, 100.0f);

}

void MyGLWidget::paintGL()
{
    qInfo() << "paintGL";

    //glLoadIdentity();
    glClearColor(0.39, 0.58, 0.93, 0.2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawFigure();

    glFlush();
}

void MyGLWidget::drawFigure()
{
    transformFigure();

    drawDataFromBuffer();

}

void MyGLWidget::makeFigure()
{
    float x, y, z;
    int a = 2;
    int b = 1;

    for(int i = 0; i < valueOfEdges; i++){
        x = a*cos(i*2*M_PI/valueOfEdges);
        //qInfo() << "x = " << x;
        y = b*sin(i*2*M_PI/valueOfEdges);
        //qInfo() << "y = " << y;
        z = -1;
        //qInfo() << "z = " << z;
        upperFigurePlane.push_back(glm::vec3(x, y, z));
        colorsUpper.push_back(glm::vec3(abs(x), abs(y), abs(y)));
    }

    for(int i = 0; i < valueOfEdges; i++){
        x = 1.2*a*cos(i*2*M_PI/valueOfEdges);
       // qInfo() << "x2 = " << x;
        y = 1.2*b*sin(i*2*M_PI/valueOfEdges);
        //qInfo() << "y2 = " << y;
        z = -1.5;
        //qInfo() << "z2 = " << z;
        middleFigurePlane.push_back(glm::vec3(x, y, z));
        colorsMiddle.push_back(glm::vec3(abs(0.1), abs(0.5), abs(0.3)));
    }

    for(int i = 0; i < valueOfEdges; i++){
        x = a*cos(i*2*M_PI/valueOfEdges);
        //qInfo() << "x = " << x;
        y = b*sin(i*2*M_PI/valueOfEdges);
        //qInfo() << "y = " << y;
        z = -2;
        //qInfo() << "z = " << z;
        downFigurePlane.push_back(glm::vec3(x, y, z));
        colorsDown.push_back(glm::vec3(abs(y), abs(x), abs(x)));
    }
}

void MyGLWidget::insertFigureInBuffer()
{
    glGenBuffers(1, &vertexVBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, upperFigurePlane.size() * sizeof(glm::vec3), upperFigurePlane.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW
    //glGenBuffers(1, &colorVBO);

    glGenBuffers(1, colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, colorsUpper.size() * sizeof(glm::vec3), colorsUpper.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vertexVBO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, middleFigurePlane.size() * sizeof(glm::vec3), middleFigurePlane.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW

    glGenBuffers(1, &colorVBO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorsMiddle.size() * sizeof(glm::vec3), colorsMiddle.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW

    glGenBuffers(1, &vertexVBO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[2]);
    glBufferData(GL_ARRAY_BUFFER, downFigurePlane.size() * sizeof(glm::vec3), downFigurePlane.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW

    glGenBuffers(1, &colorVBO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO[2]);
    glBufferData(GL_ARRAY_BUFFER, colorsDown.size() * sizeof(glm::vec3), colorsDown.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW



}

void MyGLWidget::transformFigure()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, -5, 1, 0, 0, -1, 0, 1, 0);

    glTranslatef(0, 0, -1);
    glRotatef(xRotTheta, 1, 0, 0);
    glRotatef(yRotTheta, 0, 1, 0);
    glRotatef(zRotTheta, 0, 0, 1);
    glTranslatef(0, 0, 1);
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
            reconstructFigure();
            break;
        }
        default:
            exit(0);
        }
    update();
}

void MyGLWidget::reconstructFigure()
{
    upperFigurePlane.clear();
    colorsUpper.clear();
    middleFigurePlane.clear();
    colorsMiddle.clear();
    downFigurePlane.clear();
    colorsDown.clear();
    makeFigure();
    insertFigureInBuffer();
}

void MyGLWidget::drawDataFromBuffer()
{
    for(int i = 0; i < 3; i++){
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[i]);
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, colorVBO[i]);
        glColorPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
            glDrawArrays(GL_POLYGON, 0, valueOfEdges);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

}
