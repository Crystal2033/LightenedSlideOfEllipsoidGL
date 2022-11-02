#include "rotationslider.h"

void RotationSlider::createSlider(QBoxLayout& layout, CHANGE_TYPE changeType) {

    axisHorLay = new QHBoxLayout();
    this->changeType = changeType;
    axisLabel = new QLabel(getNameByChangeType());
    axisSlider = new QSlider(Qt::Horizontal);
    axisSlider->setRange(-180, 180);
    axisSlider->setValue(0);
    axisSlider->setTickPosition(QSlider::TicksBelow);

    axisNumGadget = new QLCDNumber();
    axisNumGadget->display(value);
    axisNumGadget->setFixedSize(70, 70);

    axisHorLay->addWidget(axisLabel, 1);
    axisHorLay->addWidget(axisSlider, 6);
    axisHorLay->addWidget(axisNumGadget, 1);

    layout.addLayout(axisHorLay);
    connect(axisSlider, SIGNAL(valueChanged(int)), SLOT(onValueChanged(int)));
}

void RotationSlider::onValueChanged(int val) {
    value = val;
    axisNumGadget->display(value);
    notifyObservers();
}

