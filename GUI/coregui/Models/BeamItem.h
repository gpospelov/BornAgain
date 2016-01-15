// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.h
//! @brief     Defines class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAMITEM_H
#define BEAMITEM_H

#include "ParameterizedItem.h"

class BA_CORE_API_ BeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    static const QString P_INCLINATION_ANGLE;
    static const QString P_AZIMUTHAL_ANGLE;
    explicit BeamItem(ParameterizedItem *parent=0);
    virtual ~BeamItem(){}

    double getIntensity() const;
    void setIntensity(double value);

    double getWavelength() const;
    void setWavelength(double value, const QString &distribution_name = QString());

    double getInclinationAngle() const;
    void setInclinationAngle(double value, const QString &distribution_name = QString());

    double getAzimuthalAngle() const;
    void setAzimuthalAngle(double value, const QString &distribution_name = QString());
};

#endif

