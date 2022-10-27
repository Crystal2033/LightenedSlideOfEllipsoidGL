#include "mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <GL/gl.h>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainHorLay = new QVBoxLayout();
    menuHorLayout =new QHBoxLayout();
    myGLWidget = new MyGLWidget();

    mainHorLay->addWidget(myGLWidget);
    mainHorLay->addLayout(menuHorLayout);

    this->centralWidget()->setLayout(mainHorLay);
    setRotateSliders();
}

void MainWindow::setRotateSliders() {
    setXRotateSlider();
    setYRotateSlider();
    setZRotateSlider();
}

void MainWindow::setXRotateSlider() {
    xRotateSlider = new RotationSlider();
    xRotateSlider->createAxisSlider(*menuHorLayout, 'X');
    xRotateSlider->addObserver(myGLWidget);
}

void MainWindow::setYRotateSlider() {
    yRotateSlider = new RotationSlider();
    yRotateSlider->createAxisSlider(*menuHorLayout, 'Y');
    yRotateSlider->addObserver(myGLWidget);
}

void MainWindow::setZRotateSlider() {
    zRotateSlider = new RotationSlider();
    zRotateSlider->createAxisSlider(*menuHorLayout, 'Z');
    zRotateSlider->addObserver(myGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
