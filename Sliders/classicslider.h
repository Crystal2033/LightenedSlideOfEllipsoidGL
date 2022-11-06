/***************************************************************************
 *                                                                         *
 *   Copyright (C) 06.11.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef CLASSICSLIDER_H
#define CLASSICSLIDER_H
#include "abstractslider.h"
#include <QLCDNumber>
#include <QLabel>
#include <qslider.h>

class ClassicSlider : public AbstractSlider
{
    Q_OBJECT
public:
    ClassicSlider();
    void createSlider(QBoxLayout& layout, CHANGE_TYPE changeType, const int left, const int right, const int curr) override;
    ~ClassicSlider() = default;

private slots:
    void onValueChanged(int val);

private:
    QLabel* classicLabel = nullptr;
    QSlider* classicSlider = nullptr;
    QLCDNumber* classicNumGadget = nullptr;
    QHBoxLayout* classicHorLay = nullptr;
};

#endif // CLASSICSLIDER_H
