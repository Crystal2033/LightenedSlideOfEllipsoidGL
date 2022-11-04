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
    xRotateSlider = new RotationSlider();
    xRotateSlider->createSlider(*rotationSlidersLay, XROT);
    xRotateSlider->addObserver(myGLWidget);
}

void MainWindow::setYRotateSlider() {
    yRotateSlider = new RotationSlider();
    yRotateSlider->createSlider(*rotationSlidersLay, YROT);
    yRotateSlider->addObserver(myGLWidget);
}

void MainWindow::setZRotateSlider() {
    zRotateSlider = new RotationSlider();
    zRotateSlider->createSlider(*rotationSlidersLay, ZROT);
    zRotateSlider->addObserver(myGLWidget);
}

void MainWindow::setApproximateSlider()
{
    approximateSlider = new ApproximateSlider();
    approximateSlider->createSlider(*approxSliderLay, APROX);
    approximateSlider->addObserver(myGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

