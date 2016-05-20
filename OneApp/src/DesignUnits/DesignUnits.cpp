/*
 * DesignUnits.cpp
 *
 *  Created on: 2014-10-26
 *      Author: Roger
 */

#include <src/DesignUnits/DesignUnits.h>

DesignUnits::DesignUnits(QObject *_parent) :
    QObject(_parent),
    thisDevice(new bb::device::HardwareInfo())
{
}

DesignUnits::~DesignUnits()
{
    thisDevice->deleteLater();
}

int DesignUnits::du(const double& units) {
    QString modelName = thisDevice->modelName();

    if (modelName.contains("Passport", Qt::CaseInsensitive))
        return (12 * units);
    else if (modelName.contains("Z10", Qt::CaseInsensitive) || modelName.contains("P'9982", Qt::CaseInsensitive))
        return (10 * units);
    else if (modelName.contains("Q10", Qt::CaseInsensitive) || modelName.contains("Q5", Qt::CaseInsensitive) || modelName.contains("P'9983", Qt::CaseInsensitive))
        return (9 * units);
    else if (modelName.contains("Z30", Qt::CaseInsensitive) || modelName.contains("Z3", Qt::CaseInsensitive) || modelName.contains("Classic", Qt::CaseInsensitive) || modelName.contains("Leap", Qt::CaseInsensitive))
        return (8 * units);
    else return (10 * units);
}
