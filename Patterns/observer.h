/***************************************************************************
 *                                                                         *
 *   Copyright (C) 27.10.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/

#ifndef OBSERVER_H
#define OBSERVER_H
#include <QImage>
typedef enum {XROT, YROT, ZROT, APROX} CHANGE_TYPE;
class InterfaceObserver
{
public:
    virtual ~InterfaceObserver() = default;
    virtual void updateObserver(const float value, CHANGE_TYPE changeType) = 0;
};

#endif // OBSERVER_H

