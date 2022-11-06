#include "mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <GL/gl.h>
#include <Sliders/classicslider.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainHorLay = new QVBoxLayout();
    menuVertLayout = new QVBoxLayout();

    rotationSlidersLay =new QHBoxLayout();
    approxSliderLayAndCutOff = new QHBoxLayout();
    lightPositionsLay = new QHBoxLayout();
    lightIntensitiesLay = new QHBoxLayout();
    atenuationFactorsLay = new QHBoxLayout();


    menuVertLayout->addLayout(rotationSlidersLay);
    menuVertLayout->addLayout(approxSliderLayAndCutOff);
    menuVertLayout->addLayout(lightPositionsLay);
    menuVertLayout->addLayout(lightIntensitiesLay);
    menuVertLayout->addLayout(atenuationFactorsLay);
    myGLWidget = new MyGLWidget();

    mainHorLay->addWidget(myGLWidget, 1);
    mainHorLay->addLayout(menuVertLayout, 6);

    this->centralWidget()->setLayout(mainHorLay);
    setRotateSliders();
    setApproximateSlider();
    setCutOffSliders();
    setLightPositionsSliders();
    setIntensitySliders();
    setAtenuationSliders();
}

void MainWindow::setRotateSliders() {
    setXRotateSlider();
    setYRotateSlider();
    setZRotateSlider();
}

void MainWindow::setXRotateSlider() {
    createSlider(xRotateSlider, rotationSlidersLay, XROT, -180, 180, 0);
}

void MainWindow::setYRotateSlider() {
    createSlider(yRotateSlider, rotationSlidersLay, YROT, -180, 180, 0);
}

void MainWindow::setZRotateSlider() {
    createSlider(zRotateSlider, rotationSlidersLay, ZROT, -180, 180, 0);
}

void MainWindow::createSlider(AbstractSlider *&slider, QBoxLayout *lay, CHANGE_TYPE type, const int left, const int right, const int curr)
{

    slider = new ClassicSlider();
    slider->createSlider(*lay, type, left, right, curr);
    slider->addObserver(myGLWidget);
}

void MainWindow::setApproximateSlider(){
    createSlider(approximateSlider, approxSliderLayAndCutOff, APROX, 3, 100, 3);
}

void MainWindow::setCutOffSliders(){
    createSlider(spotCutOff, approxSliderLayAndCutOff, SPOT_CUT_OFF, 0, 180, 0);
    createSlider(spotExponent, approxSliderLayAndCutOff, SPOT_EXPONENT, 0, 180, 0);
}

void MainWindow::setLightPositionsSliders(){
    createSlider(xLightPos, lightPositionsLay, XLIGHT, -100, 100, 0);
    createSlider(yLightPos, lightPositionsLay, YLIGHT, -100, 100, 0);
    createSlider(zLightPos, lightPositionsLay, ZLIGHT, -100, 100, 0);
}

void MainWindow::setIntensitySliders()
{
    createSlider(rIntensity, lightIntensitiesLay, RINTENSITY, 0, 200, 200); //DON`T FORGET TO CHANGE VALUE IN MYGLWIDGET.H IN SWITCH CASE
    createSlider(gIntensity, lightIntensitiesLay, GINTENSITY, 0, 200, 200);
    createSlider(bIntensity, lightIntensitiesLay, BINTENSITY, 0, 200, 200);
}

void MainWindow::setAtenuationSliders()
{
    createSlider(constantAtenuationFactor, atenuationFactorsLay, ATENUATION_CONST, 0, 50, 0);
    createSlider(linearAtenuationFactor, atenuationFactorsLay, ATENUATION_LIN, 0, 50, 0);
    createSlider(quadraticAtenuationFactor, atenuationFactorsLay, ATENUATION_QUAD, 0, 50, 0);
}



MainWindow::~MainWindow()
{
    delete ui;
}

