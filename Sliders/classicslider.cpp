/***************************************************************************
 *                                                                         *
 *   Copyright (C) 06.11.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "classicslider.h"

#include <QPalette>

void ClassicSlider::setValue(int value)
{
    AbstractSlider::setValue(value);
    classicSlider->setValue(value);
}

QBoxLayout* ClassicSlider::createSlider(QBoxLayout &layout, Qt::Orientation sliderOrientation, CHANGE_TYPE changeType, const int left, const int right, const int curr)
{
    value = curr;
     if(sliderOrientation == Qt::Horizontal){
         classicLay = new QHBoxLayout();
     }
     else if(sliderOrientation == Qt::Vertical){
         classicLay = new QVBoxLayout();
     }
    this->changeType = changeType;
    classicLabel = new QLabel(getNameByChangeType());
    classicSlider = new QSlider(sliderOrientation);
    classicSlider->setRange(left, right);
    classicSlider->setValue(curr);
    classicSlider->setTickPosition(QSlider::TicksBelow);

    classicNumGadget = new QLCDNumber(this);
    classicNumGadget->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
    classicNumGadget->display(classicSlider->value());
    setStyles();


    if(sliderOrientation == Qt::Horizontal){
        classicLay->setContentsMargins(QMargins(50, 0,50,10));
        classicLay->addWidget(classicLabel, 1);
        classicLay->addWidget(classicSlider, 10);
        classicLay->addWidget(classicNumGadget, 1);
    }
    else if(sliderOrientation == Qt::Vertical){
        classicNumGadget->setFixedSize(45, 40);
        classicLay->addWidget(classicLabel, 1, Qt::AlignLeft);
        classicLay->addWidget(classicSlider, 10, Qt::AlignLeft);
        classicLay->addWidget(classicNumGadget, 1, Qt::AlignLeft);
    }

    layout.addLayout(classicLay);
    connect(classicSlider, &QSlider::valueChanged, this, &ClassicSlider::onValueChanged);
    notifyObservers();
    return classicLay;
}

void ClassicSlider::onValueChanged(int val)
{
    value = val;
    classicNumGadget->display(value);
    notifyObservers();
}

void ClassicSlider::setStyles()
{
    classicNumGadget->setStyleSheet("QLCDNumber{"
                                    "background-color: rgb(77, 138, 113);"
                                    "border-radius: 5px;"
                                    "}"
                                    ""
                                    "");
    classicLabel->setStyleSheet("color:rgb(204, 230, 228);"
                                "font-weight: bold;"
                                "font-family: \"Times New Roman\", Times, serif;"
                                "font-size: 15px;"
                                "");
    classicSlider->setStyleSheet("QSlider::handle{"
                                 "background-color:white;"
                                 "}"
                                 ""
                                 ""
                                 "");
}
