/***************************************************************************
 *                                                                         *
 *   Copyright (C) 02.11.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef ABSTRACTSLIDER_H
#define ABSTRACTSLIDER_H
#include "Patterns/subject.h"
#include <QBoxLayout>
#include <QWidget>

class AbstractSlider : public QWidget, InterfaceSubject
{
    Q_OBJECT
public:
    explicit AbstractSlider(QWidget *parent = nullptr);
    virtual void createSlider(QBoxLayout& layout, CHANGE_TYPE changeType) {};
    void addObserver(InterfaceObserver *observer);
    void removeObserver(InterfaceObserver *observer);

signals:

protected:
    void notifyObservers() const;
    QString getNameByChangeType() const;
    int value = 0.0;
    CHANGE_TYPE changeType;
    QList<InterfaceObserver*> observers;
    int getValue()const;
};

#endif // ABSTRACTSLIDER_H
