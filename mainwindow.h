#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QHBoxLayout>
#include "myglwidget.h"
#include <QSurface>
#include "Sliders/abstractslider.h"

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void sendStartValuesToGLWidget() const;
    ~MainWindow();

private:
    void createSlider(AbstractSlider*& slider, QBoxLayout* lay, CHANGE_TYPE type, const int left, const int right, const int curr);

    void setRotateSliders();

    void setApproximateAndStretchSlider();

    void setLightPositionsSliders();
    void setIntensitySliders();
    void setAtenuationSliders();

    void setSpecularColors();
    void setShinessAndCutOffSliders();


    MyGLWidget* myGLWidget = nullptr;
    QVBoxLayout* mainHorLay = nullptr;
    QVBoxLayout* menuVertLayout = nullptr;

    QHBoxLayout* rotationSlidersLay = nullptr;

    QHBoxLayout* ellipsoidFormSlidersLay = nullptr;

    QHBoxLayout* lightPositionsLay = nullptr;

    QHBoxLayout* lightIntensitiesLay = nullptr;

    QHBoxLayout* shinessAndCuts = nullptr;

    QHBoxLayout* specularColorsLay = nullptr;

    QHBoxLayout* atenuationFactorsLay = nullptr;

    Ui::MainWindow* ui;

    AbstractSlider* xRotateSlider = nullptr;
    AbstractSlider* yRotateSlider = nullptr;
    AbstractSlider* zRotateSlider = nullptr;

    AbstractSlider* approximateSlider = nullptr;
    AbstractSlider* xEllipsoidStretch = nullptr;
    AbstractSlider* yEllipsoidStretch = nullptr;


    AbstractSlider* xLightPos = nullptr;
    AbstractSlider* yLightPos = nullptr;
    AbstractSlider* zLightPos = nullptr;

    AbstractSlider* rIntensity = nullptr;
    AbstractSlider* gIntensity = nullptr;
    AbstractSlider* bIntensity = nullptr;

    AbstractSlider* spotCutOff = nullptr;
    AbstractSlider* spotExponent = nullptr;
    AbstractSlider* shiness = nullptr;

    AbstractSlider* rSpecularColor = nullptr;
    AbstractSlider* gSpecularColor = nullptr;
    AbstractSlider* bSpecularColor = nullptr;

    AbstractSlider* constantAtenuationFactor = nullptr;
    AbstractSlider* linearAtenuationFactor = nullptr;
    AbstractSlider* quadraticAtenuationFactor = nullptr;
};
