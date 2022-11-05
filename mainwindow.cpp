#include "mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <GL/gl.h>
#include "Sliders/rotationslider.h"
#include "Sliders/approximateslider.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainHorLay = new QVBoxLayout();
    menuVertLayout = new QVBoxLayout();

    rotationSlidersLay =new QHBoxLayout();
    approxSliderLay = new QHBoxLayout();

    menuVertLayout->addLayout(rotationSlidersLay);
    menuVertLayout->addLayout(approxSliderLay);
    myGLWidget = new MyGLWidget();

    mainHorLay->addWidget(myGLWidget, 1);
    mainHorLay->addLayout(menuVertLayout, 6);

    this->centralWidget()->setLayout(mainHorLay);
    setRotateSliders();
    setApproximateSlider();
}

void MainWindow::setRotateSliders() {
    setXRotateSlider();
    setYRotateSlider();
    setZRotateSlider();
}

void MainWindow::setXRotateSlider() {
    createSlider(xRotateSlider, rotationSlidersLay, XROT);
}

void MainWindow::setYRotateSlider() {
    createSlider(yRotateSlider, rotationSlidersLay, YROT);
}

void MainWindow::setZRotateSlider() {
    createSlider(zRotateSlider, rotationSlidersLay, ZROT);
}

void MainWindow::createSlider(AbstractSlider *&slider, QBoxLayout *lay, CHANGE_TYPE type)
{
    if(type == XROT || type == YROT || type == ZROT){
           slider = new RotationSlider();
    }
    else if(type == APROX){
        slider = new ApproximateSlider();
    }

    slider->createSlider(*lay, type);
    slider->addObserver(myGLWidget);
}

void MainWindow::setApproximateSlider(){
    createSlider(approximateSlider, approxSliderLay, APROX);
}

MainWindow::~MainWindow()
{
    delete ui;
}

