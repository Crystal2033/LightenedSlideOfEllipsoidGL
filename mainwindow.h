#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QHBoxLayout>
#include "myglwidget.h"
#include <QSurface>
#include "Sliders/abstractslider.h"
#include <QGroupBox>
#include <QCheckBox>

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void sendStartValuesToGLWidget() const;
    ~MainWindow();

private:
    void keyPressEvent(QKeyEvent *ev) override;

    QBoxLayout* createSlider(AbstractSlider*& slider, Qt::Orientation sliderOrientation, QBoxLayout* lay, CHANGE_TYPE type, const int left, const int right, const int curr);

    void setRotateSliders(Qt::Orientation sliderOrientation);

    void setApproximateAndStretchSlider(Qt::Orientation sliderOrientation);

    void setLightPositionsSliders(Qt::Orientation sliderOrientation);
    void setIntensitySliders(Qt::Orientation sliderOrientation);
    void setAtenuationSliders(Qt::Orientation sliderOrientation);

    void setSpecularColors(Qt::Orientation sliderOrientation);
    void setShinessAndCutOffSliders(Qt::Orientation sliderOrientation);

    void createGroupBox(QGroupBox* groupBox, QBoxLayout* lay, QString groupName);
    void setSliders();

    MyGLWidget* myGLWidget = nullptr;
    QVBoxLayout* mainVertLay = nullptr;

    QVBoxLayout* menuVertLayout = nullptr;
    QHBoxLayout* menuHorLayout = nullptr;

    QGroupBox* rotationGroup;
    QBoxLayout* rotationSlidersLay = nullptr;

    QGroupBox* ellipsoidSettingsGroup;
    QBoxLayout* ellipsoidFormSlidersLay = nullptr;

    QGroupBox* lightPosGroup;
    QBoxLayout* lightPositionsLay = nullptr;

    QGroupBox* shinessAndCutsGroup;
    QBoxLayout* shinessAndCuts = nullptr;


    QVBoxLayout* lightingLayout;

    QGroupBox* lightIntensivityGroup;
    QBoxLayout* lightIntensitiesLay = nullptr;


    QGroupBox* specularSettingsGroup;
    QBoxLayout* specularColorsLay = nullptr;

    QGroupBox* atenuationGroup;
    QBoxLayout* atenuationFactorsLay = nullptr;

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
    QCheckBox* rIntensCheckBox = nullptr;
    QCheckBox* gIntensCheckBox = nullptr;
    QCheckBox* bIntensCheckBox = nullptr;


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
