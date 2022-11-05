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
    ~MainWindow();

protected:

public slots:

private:
    void setRotateSliders();
    void setXRotateSlider();
    void setYRotateSlider();
    void setZRotateSlider();
    void createSlider(AbstractSlider*& slider, QBoxLayout* lay, CHANGE_TYPE type);

    void setApproximateSlider();

    MyGLWidget* myGLWidget = nullptr;
    QVBoxLayout* mainHorLay = nullptr;
    QVBoxLayout* menuVertLayout = nullptr;
    QHBoxLayout* rotationSlidersLay = nullptr;
    QHBoxLayout* approxSliderLay = nullptr;
    Ui::MainWindow* ui;

    AbstractSlider* xRotateSlider = nullptr;
    AbstractSlider* yRotateSlider = nullptr;
    AbstractSlider* zRotateSlider = nullptr;
    AbstractSlider* approximateSlider = nullptr;

};
