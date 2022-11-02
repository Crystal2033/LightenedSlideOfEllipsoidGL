/***************************************************************************
 *                                                                         *
 *   Copyright (C) 02.11.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "abstractslider.h"

#include <QLCDNumber>
#include <QLabel>
#include <QSlider>

class ApproximateSlider : public AbstractSlider
{

public:
    ApproximateSlider();
    void createSlider(QBoxLayout& layout, CHANGE_TYPE changeType) override;
    ~ApproximateSlider() = default;

private slots:
    void onValueChanged(int val);

private:
    QLabel* approxLabel = nullptr;
    QSlider* approxSlider = nullptr;
    QLCDNumber* approxNumGadget = nullptr;
    QHBoxLayout* approxHorLay = nullptr;
};

