#include "rotationslider.h"

void RotationSlider::createSlider(QBoxLayout& layout, CHANGE_TYPE changeType, const int left, const int right, const int curr) {

    axisHorLay = new QHBoxLayout();
    this->changeType = changeType;
    axisLabel = new QLabel(getNameByChangeType());
    axisSlider = new QSlider(Qt::Horizontal);
    axisSlider->setRange(left, right);
    axisSlider->setValue(curr);
    axisSlider->setTickPosition(QSlider::TicksBelow);

    axisNumGadget = new QLCDNumber();
    axisNumGadget->display(axisSlider->value());
    axisNumGadget->setFixedSize(65, 65);

    axisHorLay->addWidget(axisLabel, 1);
    axisHorLay->addWidget(axisSlider, 5);
    axisHorLay->addWidget(axisNumGadget, 1);

    layout.addLayout(axisHorLay);
    connect(axisSlider, &QSlider::valueChanged, this, &RotationSlider::onValueChanged);
}

void RotationSlider::onValueChanged(int val) {
    value = val;
    axisNumGadget->display(value);
    notifyObservers();
}

