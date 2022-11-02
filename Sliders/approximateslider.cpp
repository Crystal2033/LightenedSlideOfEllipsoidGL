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

void ApproximateSlider::createSlider(QBoxLayout &layout, CHANGE_TYPE changeType)
{
    approxHorLay = new QHBoxLayout();
    this->changeType = changeType;
    approxLabel = new QLabel(getNameByChangeType());
    approxSlider = new QSlider(Qt::Horizontal);
    approxSlider->setRange(3, 40);
    approxSlider->setValue(3);
    approxSlider->setTickPosition(QSlider::TicksBelow);

    approxNumGadget = new QLCDNumber(this);
    approxNumGadget->display(approxSlider->minimum());
    approxNumGadget->setFixedSize(70, 70);

    approxHorLay->addWidget(approxLabel, 1);
    approxHorLay->addWidget(approxSlider, 6);
    approxHorLay->addWidget(approxNumGadget, 1);

    layout.addLayout(approxHorLay);
    connect(approxSlider, &QSlider::valueChanged, this, &ApproximateSlider::onValueChanged);
}

void ApproximateSlider::onValueChanged(int val)
{
    qInfo() << val;
    value = val;
    approxNumGadget->display(value);
    notifyObservers();
}
