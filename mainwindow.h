#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QHBoxLayout>
#include "myglwidget.h"
#include <QSurface>
#include "rotationslider.h"


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
    MyGLWidget* myGLWidget = nullptr;
    QVBoxLayout* mainHorLay = nullptr;
    QHBoxLayout* menuHorLayout = nullptr;
    Ui::MainWindow* ui;
    void setRotateSliders();
    RotationSlider* xRotateSlider = nullptr;
    RotationSlider* yRotateSlider = nullptr;
    RotationSlider* zRotateSlider = nullptr;
    void setXRotateSlider();
    void setYRotateSlider();
    void setZRotateSlider();
};
