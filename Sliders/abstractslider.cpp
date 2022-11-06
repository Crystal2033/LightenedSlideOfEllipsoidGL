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
            return "X rotation";
        }
        case YROT:{
            return "Y rotation";
        }
        case ZROT:{
            return "Z rotation";
        }
        case APROX:{
            return "Edges";
        }
        case SPOT_CUT_OFF:{
            return "Cut off";
        }
        case SPOT_EXPONENT:{
            return "Spot exponent";
        }
        case XLIGHT:{
            return "X light";
        }
        case YLIGHT:{
            return "Y light";
        }
        case ZLIGHT:{
            return "Z light";
        }
        case RINTENSITY:{
            return "Red intens";
        }
        case GINTENSITY:{
            return "Green intens";
        }
        case BINTENSITY:{
            return "Blue intens";
        }
        case ATENUATION_CONST:{
            return "Const aten";
        }
        case ATENUATION_LIN:{
            return "Linear aten";
        }
        case ATENUATION_QUAD:{
            return "Quadric aten";
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
