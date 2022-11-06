#pragma once
#include <QLayout>
#include <qlabel.h>
#include <qslider.h>
#include <qlcdnumber.h>
#include <QList>
#include "abstractslider.h"

class RotationSlider : public AbstractSlider
{
    Q_OBJECT
public:
    RotationSlider() = default;
    void createSlider(QBoxLayout& layout, CHANGE_TYPE changeType, const int left, const int right, const int curr) override;
    ~RotationSlider() = default;

private slots:
    void onValueChanged(int val);

private:
    QLabel* axisLabel = nullptr;
    QSlider* axisSlider = nullptr;
    QLCDNumber* axisNumGadget = nullptr;
    QHBoxLayout* axisHorLay = nullptr;

};
