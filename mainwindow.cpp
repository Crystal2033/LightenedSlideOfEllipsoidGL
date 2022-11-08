#include "mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <GL/gl.h>
#include <Sliders/classicslider.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Crystal3D");
    this->setWindowIcon(QIcon(":/Pics/Crystal.png"));

    mainVertLay = new QVBoxLayout();
    menuVertLayout = new QVBoxLayout();

    lightingLayout = new QVBoxLayout();
    menuHorLayout = new QHBoxLayout();

    myGLWidget = new MyGLWidget();


    setSliders();

    menuHorLayout->addLayout(lightingLayout, 6);
    lightingLayout->setContentsMargins(QMargins(0, 0, 20, 0));
    menuHorLayout->addWidget(myGLWidget, 20);
    menuHorLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    mainVertLay->addLayout(menuHorLayout, 15);
    mainVertLay->addLayout(menuVertLayout, 1);

    this->centralWidget()->setLayout(mainVertLay);

    sendStartValuesToGLWidget();
}


QBoxLayout* MainWindow::createSlider(AbstractSlider *&slider, Qt::Orientation sliderOrientation, QBoxLayout *lay, CHANGE_TYPE type, const int left, const int right, const int curr)
{

    slider = new ClassicSlider();
    QBoxLayout* sliderLay = slider->createSlider(*lay, sliderOrientation, type, left, right, curr);
    slider->addObserver(myGLWidget);
    return sliderLay;
}

void MainWindow::setRotateSliders(Qt::Orientation sliderOrientation) {

    rotationSlidersLay = new QHBoxLayout();
    createSlider(xRotateSlider, sliderOrientation, rotationSlidersLay, XROT, -180, 180, 0);
    createSlider(yRotateSlider, sliderOrientation, rotationSlidersLay, YROT, -180, 180, 0);
    createSlider(zRotateSlider, sliderOrientation, rotationSlidersLay, ZROT, -180, 180, 0);

    createGroupBox(rotationGroup, rotationSlidersLay, QString("Rotation angles"));
}

void MainWindow::setApproximateAndStretchSlider(Qt::Orientation sliderOrientation){

    ellipsoidFormSlidersLay = new QHBoxLayout();
    createSlider(approximateSlider, sliderOrientation, ellipsoidFormSlidersLay, APROX, 3, 100, 3);
    createSlider(xEllipsoidStretch, sliderOrientation, ellipsoidFormSlidersLay, XSTRETCH, 1, 20, 10);
    createSlider(yEllipsoidStretch, sliderOrientation, ellipsoidFormSlidersLay, YSTRETCH, 1, 20, 5);

    createGroupBox(ellipsoidSettingsGroup, ellipsoidFormSlidersLay, QString("Ellipsoid settings"));
}

void MainWindow::setShinessAndCutOffSliders(Qt::Orientation sliderOrientation){

    shinessAndCuts = new QHBoxLayout();
    createSlider(shiness, sliderOrientation, shinessAndCuts, SHINESS, 0, 128, 25);
    createSlider(spotCutOff, sliderOrientation, shinessAndCuts, SPOT_CUT_OFF, 0, 180, 180);
    createSlider(spotExponent, sliderOrientation, shinessAndCuts, SPOT_EXPONENT, 0, 180, 0);

    createGroupBox(shinessAndCutsGroup, shinessAndCuts, QString("Shiness and cut off settings"));
}

void MainWindow::createGroupBox(QGroupBox *groupBox, QBoxLayout *lay, QString groupName)
{
    groupBox = new QGroupBox(groupName);
    groupBox->setLayout(lay);

    if(lay->expandingDirections() == Qt::Orientation::Vertical){
        lightingLayout->addWidget(groupBox, 1);
    }
    else if(lay->expandingDirections() == Qt::Orientation::Horizontal){
        menuVertLayout->addWidget(groupBox, 1);
    }
}

void MainWindow::setSliders()
{
    setRotateSliders(Qt::Horizontal);

    setApproximateAndStretchSlider(Qt::Horizontal);

    setLightPositionsSliders(Qt::Horizontal);

    setIntensitySliders(Qt::Vertical);
    setSpecularColors(Qt::Vertical);
    setAtenuationSliders(Qt::Vertical);

    setShinessAndCutOffSliders(Qt::Horizontal);
}



void MainWindow::setLightPositionsSliders(Qt::Orientation sliderOrientation){


    lightPositionsLay = new QHBoxLayout();
    createSlider(xLightPos, sliderOrientation, lightPositionsLay, XLIGHT, -100, 100, 0);
    createSlider(yLightPos, sliderOrientation, lightPositionsLay, YLIGHT, -100, 100, 2);
    createSlider(zLightPos, sliderOrientation, lightPositionsLay, ZLIGHT, -100, 100, 5);

    createGroupBox(lightPosGroup, lightPositionsLay, QString("Position of light"));
}

void MainWindow::setIntensitySliders(Qt::Orientation sliderOrientation){

    lightIntensitiesLay = new QHBoxLayout();
    QBoxLayout* sliderLay = createSlider(rIntensity, sliderOrientation, lightIntensitiesLay, RINTENSITY, 0, 200, 200);
    rIntensCheckBox = new QCheckBox("Animate");
    sliderLay->addWidget(rIntensCheckBox, 1, Qt::AlignLeft);

    sliderLay = createSlider(gIntensity, sliderOrientation, lightIntensitiesLay, GINTENSITY, 0, 200, 200);
    gIntensCheckBox = new QCheckBox("Animate");
    sliderLay->addWidget(gIntensCheckBox, 1, Qt::AlignLeft);

    sliderLay = createSlider(bIntensity, sliderOrientation, lightIntensitiesLay, BINTENSITY, 0, 200, 200);
    bIntensCheckBox = new QCheckBox("Animate");
    sliderLay->addWidget(bIntensCheckBox, 1, Qt::AlignLeft);

    createGroupBox(lightIntensivityGroup, lightIntensitiesLay, QString("Light intensivity"));
}

void MainWindow::setAtenuationSliders(Qt::Orientation sliderOrientation)
{
    atenuationFactorsLay = new QHBoxLayout();
    createSlider(constantAtenuationFactor, sliderOrientation, atenuationFactorsLay, ATENUATION_CONST, 0, 50, 20);
    createSlider(linearAtenuationFactor, sliderOrientation, atenuationFactorsLay, ATENUATION_LIN, 0, 50, 0);
    createSlider(quadraticAtenuationFactor, sliderOrientation, atenuationFactorsLay, ATENUATION_QUAD, 0, 50, 0);

    createGroupBox(atenuationGroup, atenuationFactorsLay, QString("Light atenuation"));
}

void MainWindow::setSpecularColors(Qt::Orientation sliderOrientation)
{
    specularColorsLay = new QHBoxLayout();
    createSlider(rSpecularColor, sliderOrientation, specularColorsLay, RSPECULAR ,0, 200, 200);
    createSlider(gSpecularColor, sliderOrientation, specularColorsLay, GSPECULAR ,0, 200, 200);
    createSlider(bSpecularColor, sliderOrientation, specularColorsLay, BSPECULAR ,0, 200, 200);

    createGroupBox(specularSettingsGroup, specularColorsLay, QString("Specularity settings"));
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

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    myGLWidget->getKeyBoardEvent(ev);
}


