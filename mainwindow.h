#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QHBoxLayout>
#include "myglwidget.h"
#include <QSurface>
#include "Sliders/abstractslider.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QTimer>
#include <QLabel>

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void sendStartValuesToGLWidget() const;
    ~MainWindow();

private slots:
    void rgbIntensiveAnimation();
    void checkBoxStateChanged();
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

    int getNewIntensityForAnimation(const AbstractSlider* slider, int* delta);
    void setNewPositionOnLabel();

    void setStyles();
    QLabel positionLabel;

    MyGLWidget* myGLWidget = nullptr;
    QVBoxLayout* mainVertLay = nullptr;

    QVBoxLayout* menuVertLayout = nullptr;
    QHBoxLayout* menuHorLayout = nullptr;
    QVBoxLayout* glWidgetAndLabelsLay = nullptr;

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
    AbstractSlider* xEllipsoidStretchSlider = nullptr;
    AbstractSlider* yEllipsoidStretchSlider = nullptr;


    AbstractSlider* xLightPosSlider = nullptr;
    AbstractSlider* yLightPosSlider = nullptr;
    AbstractSlider* zLightPosSlider = nullptr;

    AbstractSlider* rIntensitySlider = nullptr;
    AbstractSlider* gIntensitySlider = nullptr;
    AbstractSlider* bIntensitySlider = nullptr;
    QCheckBox* rIntensCheckBox = nullptr;
    QCheckBox* gIntensCheckBox = nullptr;
    QCheckBox* bIntensCheckBox = nullptr;
    int rIntensDelta = -1;
    int gIntensDelta = -1;
    int bIntensDelta = -1;
    QTimer* rgbIntensiveTimer;


    AbstractSlider* spotCutOffSlider = nullptr;
    AbstractSlider* spotExponentSlider = nullptr;
    AbstractSlider* shinessSlider = nullptr;

    AbstractSlider* rSpecularColorSlider = nullptr;
    AbstractSlider* gSpecularColorSlider = nullptr;
    AbstractSlider* bSpecularColorSlider = nullptr;

    AbstractSlider* constantAtenuationFactorSlider = nullptr;
    AbstractSlider* linearAtenuationFactorSlider = nullptr;
    AbstractSlider* quadraticAtenuationFactorSlider = nullptr;
};
