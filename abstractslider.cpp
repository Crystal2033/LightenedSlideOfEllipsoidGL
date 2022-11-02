/***************************************************************************
 *                                                                         *
 *   Copyright (C) 02.11.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "abstractslider.h"

AbstractSlider::AbstractSlider(QWidget *parent)
    : QWidget{parent}
{

}

void AbstractSlider::addObserver(InterfaceObserver *observer)
{
    this->observers.append(observer);
}

void AbstractSlider::removeObserver(InterfaceObserver *observer)
{
    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for (; it != observers.constEnd(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void AbstractSlider::notifyObservers() const
{
    for (auto obs : observers) {
        obs->updateObserver(float(value), changeType);
    }
}

QString AbstractSlider::getNameByChangeType() const
{
    switch (changeType)
    {
        case XROT:{
            return "X";
        }
        case YROT:{
            return "Y";
        }
        case ZROT:{
            return "Z";
        }
        case APROX:
        {
            return "Edges";
        }
        default:{
           qInfo() << "Unpredictable value";
           break;
        }
    }
    return "";
}

int AbstractSlider::getValue() const
{
    return value;
}
