/***************************************************************************
 *                                                                         *
 *   Copyright (C) 02.11.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "approximateslider.h"


ApproximateSlider::ApproximateSlider()
{

}

void ApproximateSlider::createSlider(QBoxLayout &layout, CHANGE_TYPE changeType, const int left, const int right, const int curr)
{
    approxHorLay = new QHBoxLayout();
    this->changeType = changeType;
    approxLabel = new QLabel(getNameByChangeType());
    approxSlider = new QSlider(Qt::Horizontal);
    approxSlider->setRange(left, right);
    approxSlider->setValue(curr);
    approxSlider->setTickPosition(QSlider::TicksBelow);

    approxNumGadget = new QLCDNumber(this);
    approxNumGadget->display(approxSlider->value());
    approxNumGadget->setFixedSize(65, 65);

    approxHorLay->addWidget(approxLabel, 1);
    approxHorLay->addWidget(approxSlider, 5);
    approxHorLay->addWidget(approxNumGadget, 1);

    layout.addLayout(approxHorLay);
    connect(approxSlider, &QSlider::valueChanged, this, &ApproximateSlider::onValueChanged);
}

void ApproximateSlider::onValueChanged(int val)
{
    value = val;
    approxNumGadget->display(value);
    notifyObservers();
}
