#include "myglwidget.h"
#include <fstream>
float squareVertex[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
float squareColor[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1};

MyGLWidget::MyGLWidget(QWidget* parent)
{
    qInfo()<< "Nice MyGLWidget";
}

void MyGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    resizeGL(width(), height());
    qInfo() << "initializeGL";
    reconstructFigure();
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    qInfo() << "resizeGL";
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, aspect, 0.1f, 100.0f);

}

void MyGLWidget::paintGL()
{
    qInfo() << "paintGL";
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

void MyGLWidget::makeLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
                GLfloat light4_diffuse[] = {1, 1, 1};

                GLfloat light4_position[] = {0.0, 0.0, 1.0, 1.0};

                GLfloat light4_spot_direction[] = {0.0, 0.0, -1.0};

                glEnable(GL_LIGHT0);

                glLightfv(GL_LIGHT0, GL_DIFFUSE, light4_diffuse);

                glLightfv(GL_LIGHT0, GL_POSITION, light4_position);

                glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);

                glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light4_spot_direction);

                glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15.0);

    glPopMatrix();
}

void MyGLWidget::drawLightSquare()
{
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(1, 1, 1);
        glVertexPointer(3, GL_FLOAT, 0, squareVertex);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void MyGLWidget::makeFigure()
{
    float x, y, z;
        int a = 2;
        int b = 1;

        for(int i = 0; i < valueOfEdges; i++){
            x = a*cos(i*2*M_PI/valueOfEdges);
            y = b*sin(i*2*M_PI/valueOfEdges);
            z = 0;
            upperFigurePlane.push_back(glm::vec3(x, y, z));
            colorsUpper.push_back(glm::vec3(abs(1), abs(0), abs(0)));
        }
        //NORMALS FOR TOP FLAT
        glm::vec3 vec01Up = upperFigurePlane[1] -upperFigurePlane[0];
        glm::vec3 vec02Up = upperFigurePlane[2] -upperFigurePlane[0];
        glm::vec3 normalVec = glm::cross(vec01Up, vec02Up);
        //normalVec = glm::normalize(normalVec);

        for(int i = 0; i < valueOfEdges; i++){
            upperFlatNormals.push_back(normalVec);
        }

        for(int i = 0; i < valueOfEdges; i++){
            middleFlatNormals.push_back(normalVec);
        }

        for(int i = 0; i < valueOfEdges; i++){
            x = 1.2*a*cos(i*2*M_PI/valueOfEdges);
            y = 1.2*b*sin(i*2*M_PI/valueOfEdges);
            z = upperFigurePlane[0].z - 0.25;

            middleFigurePlane.push_back(glm::vec3(x, y, z));
            colorsMiddle.push_back(glm::vec3(abs(0), abs(0), abs(0)));
            if(i != 0){
                upAndMidFlatsFences.push_back(upperFigurePlane[i - 1]);
                upAndMidFlatsFences.push_back(middleFigurePlane[i - 1]);

                upAndMidFlatsFences.push_back(middleFigurePlane[i]);
                upAndMidFlatsFences.push_back(upperFigurePlane[i]);

                insertColorInVertexes(upAndMidFlatsColors, 0, 1, 0);
            }
        }
        insertColorInVertexes(upAndMidFlatsColors, 0, 1, 0);
        upAndMidFlatsFences.push_back(upperFigurePlane[valueOfEdges - 1]);
        upAndMidFlatsFences.push_back(middleFigurePlane[valueOfEdges - 1]);

        upAndMidFlatsFences.push_back(middleFigurePlane[0]);
        upAndMidFlatsFences.push_back(upperFigurePlane[0]);


        //NORMALS FOR UP AND MID FENCES
        qInfo() << upAndMidFlatsFences.size();
        for(int i = 0; i < upAndMidFlatsFences.size(); i+=4){
            countAndInsertNormals(upAndMidFlatsFences, upAndMidFenceNormals, i, 4);
        }




        for(int i = 0; i < valueOfEdges; i++){
            bottomFigurePlane.push_back(glm::vec3(upperFigurePlane[i].x, upperFigurePlane[i].y, middleFigurePlane[0].z + (middleFigurePlane[0].z- upperFigurePlane[0].z)));
            if(i != 0){
                midAndBotFlatsFences.push_back(middleFigurePlane[i - 1]);
                midAndBotFlatsFences.push_back(bottomFigurePlane[i - 1]);

                midAndBotFlatsFences.push_back(bottomFigurePlane[i]);
                midAndBotFlatsFences.push_back(middleFigurePlane[i]);
                insertColorInVertexes(midAndBotFlatsColors, 0, 0, 1);
            }
        }

        insertColorInVertexes(midAndBotFlatsColors, 0, 0, 1);

        midAndBotFlatsFences.push_back(middleFigurePlane[valueOfEdges - 1]);
        midAndBotFlatsFences.push_back(bottomFigurePlane[valueOfEdges - 1]);

        midAndBotFlatsFences.push_back(bottomFigurePlane[0]);
        midAndBotFlatsFences.push_back(middleFigurePlane[0]);


        //NORMALS FOR BOT FLAT
        glm::vec3 vec01Bot = bottomFigurePlane[2] -bottomFigurePlane[0];
        glm::vec3 vec02Bot = bottomFigurePlane[1] -bottomFigurePlane[0];
        glm::vec3 normalVecBot = glm::cross(vec01Bot, vec02Bot);
        //normalVecBot = glm::normalize(normalVecBot);
        for(int i = 0; i < valueOfEdges; i++){
            bottomFlatNormals.push_back(normalVecBot);
        }


        //NORMALS FOR MID AND BOT FENCES
        for(int i = 0; i < midAndBotFlatsFences.size(); i+=4){
            countAndInsertNormals(midAndBotFlatsFences, midAndBotFenceNormals,  i, 4);
        }


        colorsBottom = colorsUpper;
}

void MyGLWidget::insertDataInBuffer(GLuint* indexBuffer, std::vector<glm::vec3> &data, const int index)
{
    glGenBuffers(1, &indexBuffer[index]);
    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer[index]);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW
}

void MyGLWidget::insertFigureInBuffer()
{
        insertDataInBuffer(flatsVBO, upperFigurePlane, 0);
        insertDataInBuffer(flatsVBO, middleFigurePlane, 1);
        insertDataInBuffer(flatsVBO, bottomFigurePlane, 2);

        insertDataInBuffer(flatsColor, colorsUpper, 0);
        insertDataInBuffer(flatsColor, colorsMiddle, 1);
        insertDataInBuffer(flatsColor, colorsBottom, 2);

        insertDataInBuffer(fencesVBO, upAndMidFlatsFences, 0);
        insertDataInBuffer(fencesVBO, midAndBotFlatsFences, 1);

        insertDataInBuffer(fencesColor, upAndMidFlatsColors, 0);
        insertDataInBuffer(fencesColor, midAndBotFlatsColors, 1);

        insertDataInBuffer(normalsVBO, upperFlatNormals, 0);
        insertDataInBuffer(normalsVBO, middleFlatNormals, 1);
        insertDataInBuffer(normalsVBO, bottomFlatNormals, 2);
        insertDataInBuffer(normalsVBO, upAndMidFenceNormals, 3);
        insertDataInBuffer(normalsVBO, midAndBotFenceNormals, 4);

}



void MyGLWidget::transformFigure()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    //glTranslatef(0, 0, -1);
    glRotatef(xRotTheta, 1, 0, 0);
    glRotatef(yRotTheta, 0, 1, 0);
    glRotatef(zRotTheta, 0, 0, 1);
    glTranslatef(0, 0, 1);
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

    for(int i = 0; i < 3; i++){ //TODO: probably middle flat could be just a empty circle
        glBindBuffer(GL_ARRAY_BUFFER, flatsVBO[i]);
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, flatsColor[i]);
        glColorPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, normalsVBO[i]);
        glNormalPointer(GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        drawArrays(GL_TRIANGLE_FAN, 0,valueOfEdges);
    }

    for(int i = 0; i < 2; i++){ //TODO: probably middle flat could be just a empty circle
        glBindBuffer(GL_ARRAY_BUFFER, fencesVBO[i]);
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, fencesColor[i]);
        glColorPointer(3, GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, normalsVBO[i + 3]);
        glNormalPointer(GL_FLOAT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        drawArrays(GL_QUADS, 0, valueOfEdges * 4);
    }

}

void MyGLWidget::clearFigure()
{
    upperFigurePlane.clear();
    colorsUpper.clear();

    middleFigurePlane.clear();
    colorsMiddle.clear();

    bottomFigurePlane.clear();
    colorsBottom.clear();

    upAndMidFlatsFences.clear();
    upAndMidFlatsColors.clear();

    midAndBotFlatsFences.clear();
    midAndBotFlatsColors.clear();

    upperFlatNormals.clear();
    bottomFlatNormals.clear();
    middleFlatNormals.clear();
    upAndMidFenceNormals.clear();
    midAndBotFenceNormals.clear();
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

void MyGLWidget::insertColorInVertexes(std::vector<glm::vec3> &colorData, const float r, const float g, const float b)
{
    colorData.push_back(glm::vec3(r, g, b));
    colorData.push_back(glm::vec3(r, g, b));
    colorData.push_back(glm::vec3(r, g, b));
    colorData.push_back(glm::vec3(r, g, b));
}

void MyGLWidget::countAndInsertNormals(const std::vector<glm::vec3>& fences, std::vector<glm::vec3>& normals, const int i, const int valueOfPush)
{
    glm::vec3 vec01 = fences[i+1] -fences[i];
    glm::vec3 vec02 = fences[i+3] -fences[i];
    glm::vec3 normalVec = glm::cross(vec01, vec02);
    //normalVec = glm::normalize(normalVec);
    for(int j = 0; j < valueOfPush; j++){
        normals.push_back(normalVec);
    }
}
