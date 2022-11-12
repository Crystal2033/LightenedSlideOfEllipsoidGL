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
    glWidgetAndLabelsLay= new QVBoxLayout();

    myGLWidget = new MyGLWidget();
    setNewPositionOnLabel();
    glWidgetAndLabelsLay->addWidget(myGLWidget, 20);
    glWidgetAndLabelsLay->addWidget(&positionLabel, 1, Qt::AlignCenter);


    setSliders();

    menuHorLayout->addLayout(lightingLayout, 6);
    lightingLayout->setContentsMargins(QMargins(0, 0, 20, 0));
    menuHorLayout->addLayout(glWidgetAndLabelsLay, 20);
    menuHorLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    mainVertLay->addLayout(menuHorLayout, 15);
    mainVertLay->addLayout(menuVertLayout, 1);

    this->centralWidget()->setLayout(mainVertLay);

    sendStartValuesToGLWidget();

    rgbIntensiveTimer = new QTimer();
    connect(rgbIntensiveTimer, &QTimer::timeout, this, &MainWindow::rgbIntensiveAnimation);
    setStyles();
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
    createSlider(approximateSlider, sliderOrientation, ellipsoidFormSlidersLay, APROX, 3, 1000, 3);
    createSlider(xEllipsoidStretchSlider, sliderOrientation, ellipsoidFormSlidersLay, XSTRETCH, 1, 20, 15);
    createSlider(yEllipsoidStretchSlider, sliderOrientation, ellipsoidFormSlidersLay, YSTRETCH, 1, 20, 10);

    createGroupBox(ellipsoidSettingsGroup, ellipsoidFormSlidersLay, QString("Ellipsoid settings"));
}

void MainWindow::setShinessAndCutOffSliders(Qt::Orientation sliderOrientation){

    shinessAndCuts = new QHBoxLayout();
    createSlider(shinessSlider, sliderOrientation, shinessAndCuts, SHINESS, 0, 128, 25);
    createSlider(spotCutOffSlider, sliderOrientation, shinessAndCuts, SPOT_CUT_OFF, 0, 180, 180);
    createSlider(spotExponentSlider, sliderOrientation, shinessAndCuts, SPOT_EXPONENT, 0, 180, 0);

    createGroupBox(shinessAndCutsGroup, shinessAndCuts, QString("Shiness and cut off settings"));
}

void MainWindow::createGroupBox(QGroupBox *groupBox, QBoxLayout *lay, QString groupName)
{
    groupBox = new QGroupBox(groupName);
    groupBox->setLayout(lay);
    groupBox->setStyleSheet("QGroupBox:title {"
                            "color: white;"
                            "}"
                            "QGroupBox > *{"
                            "background-color: rgb(48, 107, 103);"
                            "}"
                            "QGroupBox{"
                            "background-color: rgb(48, 107, 103);"
                            "}"
                            ""
                            "");

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
    createSlider(xLightPosSlider, sliderOrientation, lightPositionsLay, XLIGHT, -100, 100, 0);
    createSlider(yLightPosSlider, sliderOrientation, lightPositionsLay, YLIGHT, -100, 100, 2);
    createSlider(zLightPosSlider, sliderOrientation, lightPositionsLay, ZLIGHT, -100, 100, 5);

    createGroupBox(lightPosGroup, lightPositionsLay, QString("Position of light"));
}

void MainWindow::setIntensitySliders(Qt::Orientation sliderOrientation){

    lightIntensitiesLay = new QHBoxLayout();
    QBoxLayout* sliderLay = createSlider(rIntensitySlider, sliderOrientation, lightIntensitiesLay, RINTENSITY, 0, 200, 0);
    currRIntensValue = rIntensitySlider->getValue();
    rIntensCheckBox = new QCheckBox("Animate");

    sliderLay->addWidget(rIntensCheckBox, 1, Qt::AlignLeft);

    sliderLay = createSlider(gIntensitySlider, sliderOrientation, lightIntensitiesLay, GINTENSITY, 0, 200, 0);
    currGIntensValue = gIntensitySlider->getValue();
    gIntensCheckBox = new QCheckBox("Animate");
    sliderLay->addWidget(gIntensCheckBox, 1, Qt::AlignLeft);

    sliderLay = createSlider(bIntensitySlider, sliderOrientation, lightIntensitiesLay, BINTENSITY, 0, 200, 0);
    currBIntensValue = bIntensitySlider->getValue();
    bIntensCheckBox = new QCheckBox("Animate");

    sliderLay->addWidget(bIntensCheckBox, 1, Qt::AlignLeft);

    createGroupBox(lightIntensivityGroup, lightIntensitiesLay, QString("Light intensivity"));

    connect(rIntensCheckBox, &QCheckBox::clicked, this, &MainWindow::checkBoxStateChanged);
    connect(gIntensCheckBox, &QCheckBox::clicked, this, &MainWindow::checkBoxStateChanged);
    connect(bIntensCheckBox, &QCheckBox::clicked, this, &MainWindow::checkBoxStateChanged);
}

void MainWindow::setAtenuationSliders(Qt::Orientation sliderOrientation)
{
    atenuationFactorsLay = new QHBoxLayout();
    createSlider(constantAtenuationFactorSlider, sliderOrientation, atenuationFactorsLay, ATENUATION_CONST, 0, 50, 20);
    createSlider(linearAtenuationFactorSlider, sliderOrientation, atenuationFactorsLay, ATENUATION_LIN, 0, 50, 0);
    createSlider(quadraticAtenuationFactorSlider, sliderOrientation, atenuationFactorsLay, ATENUATION_QUAD, 0, 50, 0);

    createGroupBox(atenuationGroup, atenuationFactorsLay, QString("Light atenuation"));
}

void MainWindow::setSpecularColors(Qt::Orientation sliderOrientation)
{
    specularColorsLay = new QHBoxLayout();
    createSlider(rSpecularColorSlider, sliderOrientation, specularColorsLay, RSPECULAR ,0, 200, 200);
    createSlider(gSpecularColorSlider, sliderOrientation, specularColorsLay, GSPECULAR ,0, 200, 200);
    createSlider(bSpecularColorSlider, sliderOrientation, specularColorsLay, BSPECULAR ,0, 200, 200);

    createGroupBox(specularSettingsGroup, specularColorsLay, QString("Specularity settings"));
}

void MainWindow::sendStartValuesToGLWidget() const
{
    myGLWidget->setSlidersValues(xRotateSlider->getValue(), XROT);
    myGLWidget->setSlidersValues(yRotateSlider->getValue(), YROT);
    myGLWidget->setSlidersValues(zRotateSlider->getValue(), ZROT);

    myGLWidget->setSlidersValues(xLightPosSlider->getValue(), XLIGHT);
    myGLWidget->setSlidersValues(yLightPosSlider->getValue(), YLIGHT);
    myGLWidget->setSlidersValues(zLightPosSlider->getValue(), ZLIGHT);

    myGLWidget->setSlidersValues(rIntensitySlider->getValue(), RINTENSITY);
    myGLWidget->setSlidersValues(gIntensitySlider->getValue(), GINTENSITY);
    myGLWidget->setSlidersValues(bIntensitySlider->getValue(), BINTENSITY);

    myGLWidget->setSlidersValues(spotCutOffSlider->getValue(), SPOT_CUT_OFF);
    myGLWidget->setSlidersValues(spotExponentSlider->getValue(), SPOT_EXPONENT);
    myGLWidget->setSlidersValues(shinessSlider->getValue(), SHINESS);

    myGLWidget->setSlidersValues(rSpecularColorSlider->getValue(), RSPECULAR);
    myGLWidget->setSlidersValues(gSpecularColorSlider->getValue(), GSPECULAR);
    myGLWidget->setSlidersValues(bSpecularColorSlider->getValue(), BSPECULAR);

    myGLWidget->setSlidersValues(constantAtenuationFactorSlider->getValue(), ATENUATION_CONST);
    myGLWidget->setSlidersValues(linearAtenuationFactorSlider->getValue(), ATENUATION_LIN);
    myGLWidget->setSlidersValues(quadraticAtenuationFactorSlider->getValue(), ATENUATION_QUAD);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getNewIntensityForAnimation(const AbstractSlider* slider, int* delta, int* currIntensValue)
{
    *currIntensValue +=*delta;

    int sinusIntens = abs(sin(*currIntensValue*M_PI/180))* (int)INTENSITY_DENUM;


    if(*currIntensValue > INTENSITY_DENUM){
        *currIntensValue = INTENSITY_DENUM;
        *delta = -*delta;
    }
    else if(*currIntensValue < 0){
        *currIntensValue = 0;
        *delta = -*delta;
    }

    return sinusIntens;
}

void MainWindow::setNewPositionOnLabel()
{
    QString stringPosition = "xPos: ";
    glm::vec3 currPos = myGLWidget->getCurrPosInWorld();
    stringPosition += QString::number(currPos.x);
    stringPosition += "                                      yPos: ";
    stringPosition += QString::number(currPos.y);
    stringPosition += "                                      zPos: ";
    stringPosition += QString::number(currPos.z);
    positionLabel.setStyleSheet("color: white;"
                                "font-weight: bold;"
                                "font-family: \"Times New Roman\", Times, serif;"
                                "font-size: 20px;");
    positionLabel.setText(stringPosition);
}

void MainWindow::setStyles()
{
    rIntensCheckBox->setStyleSheet("color: white;"
                                   "font-weight: bold;"
                                   "font-family: \"Times New Roman\", Times, serif;"
                                   "font-size: 15px;");
    gIntensCheckBox->setStyleSheet("color: white;"
                                   "font-weight: bold;"
                                   "font-family: \"Times New Roman\", Times, serif;"
                                   "font-size: 15px;");
    bIntensCheckBox->setStyleSheet("color: white;"
                                   "font-weight: bold;"
                                   "font-family: \"Times New Roman\", Times, serif;"
                                   "font-size: 15px;");
}

void MainWindow::rgbIntensiveAnimation()
{

    if(!rIntensCheckBox->isChecked() && !gIntensCheckBox->isChecked() && !bIntensCheckBox->isChecked()){
        rgbIntensiveTimer->stop();
        return;
    }

    if(rIntensCheckBox->isChecked()){
        rIntensitySlider->setValue(getNewIntensityForAnimation(rIntensitySlider, &rIntensDelta, &currRIntensValue));
    }
    if(gIntensCheckBox->isChecked()){
        gIntensitySlider->setValue(getNewIntensityForAnimation(gIntensitySlider, &gIntensDelta, &currGIntensValue));
    }
    if(bIntensCheckBox->isChecked()){
        bIntensitySlider->setValue(getNewIntensityForAnimation(bIntensitySlider, &bIntensDelta, &currBIntensValue));
    }

}

void MainWindow::checkBoxStateChanged()
{
    currRIntensValue = rIntensitySlider->getValue();
    currGIntensValue = gIntensitySlider->getValue();
    currBIntensValue = bIntensitySlider->getValue();
    if(!rgbIntensiveTimer->isActive()){
        rgbIntensiveTimer->start(20);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    myGLWidget->getKeyBoardEvent(ev);
    setNewPositionOnLabel();
}


