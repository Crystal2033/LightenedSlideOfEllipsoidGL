/***************************************************************************
 *                                                                         *
 *   Copyright (C) 08.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef SLIDEDELLIPSOID_H
#define SLIDEDELLIPSOID_H
#include <glm.hpp>
#include <vector>

class SlidedEllipsoid
{
friend class MyGLWidget;

public:
    SlidedEllipsoid();
private:
    int valueOfEdges = 3;
    float xStretch = 2.0f;
    float yStretch = 1.0f;

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

    void insertColorInVertexes(std::vector<glm::vec3>& colorData, const float r, const float g, const float b);
    void countAndInsertNormals(const std::vector<glm::vec3>& fences, std::vector<glm::vec3>& normals, const int index, const int valueOfPush);
    void clearFigure();
    void makeFigure();
};

#endif // SLIDEDELLIPSOID_H
