/***************************************************************************
 *                                                                         *
 *   Copyright (C) 06.11.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "classicslider.h"


ClassicSlider::ClassicSlider()
{

}

void ClassicSlider::createSlider(QBoxLayout &layout, CHANGE_TYPE changeType, const int left, const int right, const int curr)
{
    classicHorLay = new QHBoxLayout();
    this->changeType = changeType;
    classicLabel = new QLabel(getNameByChangeType());
    classicSlider = new QSlider(Qt::Horizontal);
    classicSlider->setRange(left, right);
    classicSlider->setValue(curr);
    classicSlider->setTickPosition(QSlider::TicksBelow);

    classicNumGadget = new QLCDNumber(this);
    classicNumGadget->display(classicSlider->value());
    classicNumGadget->setFixedSize(65, 65);

    classicHorLay->addWidget(classicLabel, 1);
    classicHorLay->addWidget(classicSlider, 5);
    classicHorLay->addWidget(classicNumGadget, 1);

    layout.addLayout(classicHorLay);
    connect(classicSlider, &QSlider::valueChanged, this, &ClassicSlider::onValueChanged);
    notifyObservers();
}

void ClassicSlider::onValueChanged(int val)
{
    value = val;
    classicNumGadget->display(value);
    notifyObservers();
}
