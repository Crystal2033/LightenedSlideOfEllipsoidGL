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
    insertFigureInBuffer();
    drawDataFromBuffer();
}

void MyGLWidget::makeFigure()
{
    float x, y, z;
    int a = 2;
    int b = 1;

    for(int i = 0; i < valueOfEdges; i++){
        x = a*cos(i*2*M_PI/valueOfEdges);
        y = b*sin(i*2*M_PI/valueOfEdges);
        z = -1;
        upperFigurePlane.push_back(x);
        upperFigurePlane.push_back(y);
        upperFigurePlane.push_back(z);
        upperFigurePlane.push_back(abs(x));
        upperFigurePlane.push_back(abs(y));
        upperFigurePlane.push_back(abs(y));
        colorsUpper.push_back(glm::vec3(abs(x), abs(y), abs(y)));
        indexesUpperPlane.push_back(i);
    }
    qInfo() << upperFigurePlane.size();
    for(int i = 0; i < valueOfEdges; i++){
        x = 1.2*a*cos(i*2*M_PI/valueOfEdges);
        y = 1.2*b*sin(i*2*M_PI/valueOfEdges);
        z = -1.25;

//        upperFigurePlane.push_back(abs(x));
//        upperFigurePlane.push_back(abs(y));
//        upperFigurePlane.push_back(abs(y));
//        middleFigurePlane.push_back(glm::vec3(x, y, z));
//        colorsMiddle.push_back(glm::vec3(abs(0.1), abs(0.5), abs(0.3)))
    }

//    for(int i = 0; i < valueOfEdges; i++){
//        x = 1.2*a*cos(i*2*M_PI/valueOfEdges);
//        y = 1.2*b*sin(i*2*M_PI/valueOfEdges);
//        z = -1.25;
//        middleFigurePlane.push_back(glm::vec3(x, y, z));
//        colorsMiddle.push_back(glm::vec3(abs(0.1), abs(0.5), abs(0.3)));
//        if(i != 0){
//            upAndMidFlatsFences.push_back(upperFigurePlane[i - 1]);
//            upAndMidFlatsFences.push_back(middleFigurePlane[i - 1]);

//            upAndMidFlatsFences.push_back(middleFigurePlane[i]);
//            upAndMidFlatsFences.push_back(upperFigurePlane[i]);

//            upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));
//            upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));
//            upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));
//            upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));
//        }
//    }
//    upAndMidFlatsFences.push_back(upperFigurePlane[0]);
//    upAndMidFlatsFences.push_back(middleFigurePlane[0]);

//    upAndMidFlatsFences.push_back(middleFigurePlane[valueOfEdges - 1]);
//    upAndMidFlatsFences.push_back(upperFigurePlane[valueOfEdges - 1]);

//    upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));
//    upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));
//    upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));
//    upAndMidFlatsColors.push_back(glm::vec3(0.5, 0.5, 0.5));


//    //qInfo() << upAndMidFlatsFences.size();

//    for(int i = 0; i < valueOfEdges; i++){
//        bottomFigurePlane.push_back(glm::vec3(upperFigurePlane[i].x, upperFigurePlane[i].y, middleFigurePlane[0].z + (middleFigurePlane[0].z- upperFigurePlane[0].z)));
//        if(i != 0){
//            midAndBotFlatsFences.push_back(middleFigurePlane[i - 1]);
//            midAndBotFlatsFences.push_back(bottomFigurePlane[i - 1]);

//            midAndBotFlatsFences.push_back(bottomFigurePlane[i]);
//            midAndBotFlatsFences.push_back(middleFigurePlane[i]);
//            midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));
//            midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));
//            midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));
//            midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));
//        }
//    }
//    midAndBotFlatsFences.push_back(middleFigurePlane[0]);
//    midAndBotFlatsFences.push_back(bottomFigurePlane[0]);

//    midAndBotFlatsFences.push_back(bottomFigurePlane[valueOfEdges - 1]);
//    midAndBotFlatsFences.push_back(middleFigurePlane[valueOfEdges - 1]);
//    midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));
//    midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));
//    midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));
//    midAndBotFlatsColors.push_back(glm::vec3(0.0, 0.0, 0.0));

//    colorsBottom = colorsUpper;
}

void MyGLWidget::insertFigureInBuffer()
{
    //UPPER ellipse flat

    glGenBuffers(1, &flatsVBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, flatsVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, upperFigurePlane.size() * sizeof(float), upperFigurePlane.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW
    glEnableVertexAttribArray(0); //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
    glEnableVertexAttribArray(1); //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(sizeof(float) * 2));

//    GLuint indexBufferID;
//    glGenBuffers(1, &indexBufferID);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexesUpperPlane.size() * sizeof(unsigned int), indexesUpperPlane.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW


//    glGenBuffers(1, flatsColor);
//    glBindBuffer(GL_ARRAY_BUFFER, flatsColor[0]);
//    glBufferData(GL_ARRAY_BUFFER, colorsUpper.size() * sizeof(glm::vec3), colorsUpper.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    //MIDDLE ellipse flat
//    glGenBuffers(1, &flatsVBO[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, flatsVBO[1]);
//    glBufferData(GL_ARRAY_BUFFER, middleFigurePlane.size() * sizeof(glm::vec3), middleFigurePlane.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    glGenBuffers(1, &flatsColor[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, flatsColor[1]);
//    glBufferData(GL_ARRAY_BUFFER, colorsMiddle.size() * sizeof(glm::vec3), colorsMiddle.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    //BOTTOM ellipse flat
//    glGenBuffers(1, &flatsVBO[2]);
//    glBindBuffer(GL_ARRAY_BUFFER, flatsVBO[2]);
//    glBufferData(GL_ARRAY_BUFFER, bottomFigurePlane.size() * sizeof(glm::vec3), bottomFigurePlane.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    glGenBuffers(1, &flatsColor[2]);
//    glBindBuffer(GL_ARRAY_BUFFER, flatsColor[2]);
//    glBufferData(GL_ARRAY_BUFFER, colorsBottom.size() * sizeof(glm::vec3), colorsBottom.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    //UPPER ellipse ring (connecting middle and upper flats)
//    glGenBuffers(1, &fencesVBO[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, fencesVBO[0]);
//    glBufferData(GL_ARRAY_BUFFER, upAndMidFlatsFences.size() * sizeof(glm::vec3), upAndMidFlatsFences.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    glGenBuffers(1, &fencesColor[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, fencesColor[0]);
//    glBufferData(GL_ARRAY_BUFFER, upAndMidFlatsColors.size() * sizeof(glm::vec3), upAndMidFlatsColors.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    //BOTTOM ellipse ring (connecting middle and bottom flats)
//    glGenBuffers(1, &fencesVBO[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, fencesVBO[1]);
//    glBufferData(GL_ARRAY_BUFFER, midAndBotFlatsFences.size() * sizeof(glm::vec3), midAndBotFlatsFences.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

//    glGenBuffers(1, &fencesColor[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, fencesColor[1]);
//    glBufferData(GL_ARRAY_BUFFER, midAndBotFlatsColors.size() * sizeof(glm::vec3), midAndBotFlatsColors.data(), GL_STATIC_DRAW);//GL_STREAM_DRAW

}



void MyGLWidget::transformFigure()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, -3, 1, 0, 0, -1, 0, 1, 0);

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
    clearFigure();
    makeFigure();
    insertFigureInBuffer();
}

void MyGLWidget::drawDataFromBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, flatsVBO[0]);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    glBindBuffer(GL_ARRAY_BUFFER, flatsColor[i]);
//    glColorPointer(3, GL_FLOAT, 0, NULL);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_POLYGON, 0, valueOfEdges);
    //glDrawElements(GL_POLYGON, valueOfEdges, GL_UNSIGNED_INT, 0);
    //glDisableClientState(GL_COLOR_ARRAY);
    //glDisableClientState(GL_VERTEX_ARRAY);

//    for(int i = 0; i < 3; i++){ //TODO: probably middle flat could be just a empty circle
//        glBindBuffer(GL_ARRAY_BUFFER, flatsVBO[i]);
//        glVertexPointer(3, GL_FLOAT, 0, NULL);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);

//        glBindBuffer(GL_ARRAY_BUFFER, flatsColor[i]);
//        glColorPointer(3, GL_FLOAT, 0, NULL);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);

//        glEnableClientState(GL_VERTEX_ARRAY);
//        glEnableClientState(GL_COLOR_ARRAY);
//            glDrawArrays(GL_POLYGON, 0, valueOfEdges);
//        glDisableClientState(GL_COLOR_ARRAY);
//        glDisableClientState(GL_VERTEX_ARRAY);
//    }

//    for(int i = 0; i < 2; i++){ //TODO: probably middle flat could be just a empty circle
//        glBindBuffer(GL_ARRAY_BUFFER, fencesVBO[i]);
//        glVertexPointer(3, GL_FLOAT, 0, NULL);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);

//        glBindBuffer(GL_ARRAY_BUFFER, fencesColor[i]);
//        glColorPointer(3, GL_FLOAT, 0, NULL);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);

//        glEnableClientState(GL_VERTEX_ARRAY);
//        glEnableClientState(GL_COLOR_ARRAY);
//            glDrawArrays(GL_QUADS, 0, valueOfEdges*4);
//        glDisableClientState(GL_COLOR_ARRAY);
//        glDisableClientState(GL_VERTEX_ARRAY);
//    }

}

void MyGLWidget::clearFigure()
{
    upperFigurePlane.clear();
    indexesUpperPlane.clear();
    colorsUpper.clear();

    middleFigurePlane.clear();
    colorsMiddle.clear();

    bottomFigurePlane.clear();
    colorsBottom.clear();

    upAndMidFlatsFences.clear();
    upAndMidFlatsColors.clear();

    midAndBotFlatsFences.clear();
    midAndBotFlatsColors.clear();
}

void MyGLWidget::installShaders()
{

}
