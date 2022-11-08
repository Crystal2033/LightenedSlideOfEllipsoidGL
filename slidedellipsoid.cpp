/***************************************************************************
 *                                                                         *
 *   Copyright (C) 08.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "slidedellipsoid.h"
#include "qmath.h"

SlidedEllipsoid::SlidedEllipsoid()
{

}

void SlidedEllipsoid::insertColorInVertexes(std::vector<glm::vec3> &colorData, const float r, const float g, const float b)
{
    colorData.push_back(glm::vec3(r, g, b));
    colorData.push_back(glm::vec3(r, g, b));
    colorData.push_back(glm::vec3(r, g, b));
    colorData.push_back(glm::vec3(r, g, b));
}

void SlidedEllipsoid::countAndInsertNormals(const std::vector<glm::vec3> &fences, std::vector<glm::vec3> &normals, const int i, const int valueOfPush)
{
    glm::vec3 vec01 = fences[i+1] -fences[i];
    glm::vec3 vec02 = fences[i+3] -fences[i];
    glm::vec3 normalVec = glm::cross(vec01, vec02);
    for(int j = 0; j < valueOfPush; j++){
        normals.push_back(normalVec);
    }
}

void SlidedEllipsoid::clearFigure()
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

void SlidedEllipsoid::makeFigure()
{
    float x, y, z;

        for(int i = 0; i < valueOfEdges; i++){
            x = xStretch*cos(i*2*M_PI/valueOfEdges);
            y = yStretch*sin(i*2*M_PI/valueOfEdges);
            z = 0;
            upperFigurePlane.push_back(glm::vec3(x, y, z));
            colorsUpper.push_back(glm::vec3(abs(1), abs(1), abs(1)));
        }
        //NORMALS FOR TOP FLAT
        glm::vec3 vec01Up = upperFigurePlane[1] -upperFigurePlane[0];
        glm::vec3 vec02Up = upperFigurePlane[2] -upperFigurePlane[0];
        glm::vec3 normalVec = glm::cross(vec01Up, vec02Up);

        for(int i = 0; i < valueOfEdges; i++){
            upperFlatNormals.push_back(normalVec);
        }

        for(int i = 0; i < valueOfEdges; i++){
            middleFlatNormals.push_back(glm::vec3(0,0,0));
        }

        for(int i = 0; i < valueOfEdges; i++){
            x = 1.2*xStretch*cos(i*2*M_PI/valueOfEdges);
            y = 1.2*yStretch*sin(i*2*M_PI/valueOfEdges);
            z = upperFigurePlane[0].z - 0.25;

            middleFigurePlane.push_back(glm::vec3(x, y, z));
            colorsMiddle.push_back(glm::vec3(abs(1), abs(1), abs(1)));
            if(i != 0){
                upAndMidFlatsFences.push_back(upperFigurePlane[i - 1]);
                upAndMidFlatsFences.push_back(middleFigurePlane[i - 1]);

                upAndMidFlatsFences.push_back(middleFigurePlane[i]);
                upAndMidFlatsFences.push_back(upperFigurePlane[i]);

                insertColorInVertexes(upAndMidFlatsColors, 1, 1, 1);
            }
        }
        insertColorInVertexes(upAndMidFlatsColors, 1, 1, 1);
        upAndMidFlatsFences.push_back(upperFigurePlane[valueOfEdges - 1]);
        upAndMidFlatsFences.push_back(middleFigurePlane[valueOfEdges - 1]);

        upAndMidFlatsFences.push_back(middleFigurePlane[0]);
        upAndMidFlatsFences.push_back(upperFigurePlane[0]);


        //NORMALS FOR UP AND MID FENCES
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
                insertColorInVertexes(midAndBotFlatsColors, 1, 1, 1);
            }
        }

        insertColorInVertexes(midAndBotFlatsColors, 1, 1, 1);

        midAndBotFlatsFences.push_back(middleFigurePlane[valueOfEdges - 1]);
        midAndBotFlatsFences.push_back(bottomFigurePlane[valueOfEdges - 1]);

        midAndBotFlatsFences.push_back(bottomFigurePlane[0]);
        midAndBotFlatsFences.push_back(middleFigurePlane[0]);

        //NORMALS FOR BOT FLAT
        glm::vec3 vec01Bot = bottomFigurePlane[2] -bottomFigurePlane[0];
        glm::vec3 vec02Bot = bottomFigurePlane[1] -bottomFigurePlane[0];
        glm::vec3 normalVecBot = glm::cross(vec01Bot, vec02Bot);
        for(int i = 0; i < valueOfEdges; i++){
            bottomFlatNormals.push_back(normalVecBot);
        }

        //NORMALS FOR MID AND BOT FENCES
        for(int i = 0; i < midAndBotFlatsFences.size(); i+=4){
            countAndInsertNormals(midAndBotFlatsFences, midAndBotFenceNormals,  i, 4);
        }

        colorsBottom = colorsUpper;
}
