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
    ellipsoidFormSlidersLay = new QHBoxLayout();
    lightPositionsLay = new QHBoxLayout();
    lightIntensitiesLay = new QHBoxLayout();
    shinessAndCuts = new QHBoxLayout();
    specularColorsLay = new QHBoxLayout();
    atenuationFactorsLay = new QHBoxLayout();


    menuVertLayout->addLayout(rotationSlidersLay);
    menuVertLayout->addLayout(ellipsoidFormSlidersLay);
    menuVertLayout->addLayout(lightPositionsLay);
    menuVertLayout->addLayout(lightIntensitiesLay);
    menuVertLayout->addLayout(shinessAndCuts);
    menuVertLayout->addLayout(specularColorsLay);
    menuVertLayout->addLayout(atenuationFactorsLay);
    myGLWidget = new MyGLWidget();

    mainHorLay->addWidget(myGLWidget, 1);
    mainHorLay->addLayout(menuVertLayout, 6);

    this->centralWidget()->setLayout(mainHorLay);
    setRotateSliders();

    setApproximateAndStretchSlider();

    setLightPositionsSliders();
    setIntensitySliders();

    setSpecularColors();
    setAtenuationSliders();
    setShinessAndCutOffSliders();

    sendStartValuesToGLWidget();
}


void MainWindow::createSlider(AbstractSlider *&slider, QBoxLayout *lay, CHANGE_TYPE type, const int left, const int right, const int curr)
{
    slider = new ClassicSlider();
    slider->createSlider(*lay, type, left, right, curr);
    slider->addObserver(myGLWidget);
}

void MainWindow::setRotateSliders() {
    createSlider(xRotateSlider, rotationSlidersLay, XROT, -180, 180, 0);
    createSlider(yRotateSlider, rotationSlidersLay, YROT, -180, 180, 0);
    createSlider(zRotateSlider, rotationSlidersLay, ZROT, -180, 180, 0);
}

void MainWindow::setApproximateAndStretchSlider(){
    createSlider(approximateSlider, ellipsoidFormSlidersLay, APROX, 3, 100, 3);
    createSlider(xEllipsoidStretch, ellipsoidFormSlidersLay, XSTRETCH, 1, 20, 10);
    createSlider(yEllipsoidStretch, ellipsoidFormSlidersLay, YSTRETCH, 1, 20, 5);
}

void MainWindow::setShinessAndCutOffSliders(){
    createSlider(shiness, shinessAndCuts, SHINESS, 0, 128, 10);
    createSlider(spotCutOff, shinessAndCuts, SPOT_CUT_OFF, 0, 180, 180);
    createSlider(spotExponent, shinessAndCuts, SPOT_EXPONENT, 0, 180, 0);
}

void MainWindow::setLightPositionsSliders(){
    createSlider(xLightPos, lightPositionsLay, XLIGHT, -100, 100, 0);
    createSlider(yLightPos, lightPositionsLay, YLIGHT, -100, 100, 2);
    createSlider(zLightPos, lightPositionsLay, ZLIGHT, -100, 100, 5);
}

void MainWindow::setIntensitySliders(){
    createSlider(rIntensity, lightIntensitiesLay, RINTENSITY, 0, 200, 200);
    createSlider(gIntensity, lightIntensitiesLay, GINTENSITY, 0, 200, 200);
    createSlider(bIntensity, lightIntensitiesLay, BINTENSITY, 0, 200, 200);
}

void MainWindow::setAtenuationSliders()
{
    createSlider(constantAtenuationFactor, atenuationFactorsLay, ATENUATION_CONST, 0, 50, 11);
    createSlider(linearAtenuationFactor, atenuationFactorsLay, ATENUATION_LIN, 0, 50, 0);
    createSlider(quadraticAtenuationFactor, atenuationFactorsLay, ATENUATION_QUAD, 0, 50, 0);
}

void MainWindow::setSpecularColors()
{
    createSlider(rSpecularColor, specularColorsLay, RSPECULAR ,0, 200, 0);
    createSlider(gSpecularColor, specularColorsLay, GSPECULAR ,0, 200, 100);
    createSlider(bSpecularColor, specularColorsLay, BSPECULAR ,0, 200, 100);
}

void MainWindow::sendStartValuesToGLWidget() const
{
    myGLWidget->setSlidersValues(xRotateSlider->getValue(), XROT);
    myGLWidget->setSlidersValues(yRotateSlider->getValue(), YROT);
    myGLWidget->setSlidersValues(zRotateSlider->getValue(), ZROT);

    myGLWidget->setSlidersValues(xLightPos->getValue(), XLIGHT);
    myGLWidget->setSlidersValues(yLightPos->getValue(), YLIGHT);
    myGLWidget->setSlidersValues(zLightPos->getValue(), ZLIGHT);

    myGLWidget->setSlidersValues(rIntensity->getValue(), RINTENSITY);
    myGLWidget->setSlidersValues(gIntensity->getValue(), GINTENSITY);
    myGLWidget->setSlidersValues(bIntensity->getValue(), BINTENSITY);

    myGLWidget->setSlidersValues(spotCutOff->getValue(), SPOT_CUT_OFF);
    myGLWidget->setSlidersValues(spotExponent->getValue(), SPOT_EXPONENT);
    myGLWidget->setSlidersValues(shiness->getValue(), SHINESS);

    myGLWidget->setSlidersValues(rSpecularColor->getValue(), RSPECULAR);
    myGLWidget->setSlidersValues(gSpecularColor->getValue(), GSPECULAR);
    myGLWidget->setSlidersValues(bSpecularColor->getValue(), BSPECULAR);

    myGLWidget->setSlidersValues(constantAtenuationFactor->getValue(), ATENUATION_CONST);
    myGLWidget->setSlidersValues(linearAtenuationFactor->getValue(), ATENUATION_LIN);
    myGLWidget->setSlidersValues(quadraticAtenuationFactor->getValue(), ATENUATION_QUAD);

}

MainWindow::~MainWindow()
{
    delete ui;
}

