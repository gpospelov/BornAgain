// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamItem.h
//! @brief     Declares class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BEAMITEM_H
#define BEAMITEM_H

#include "SessionItem.h" // inheriting from

class BA_CORE_API_ BeamItem : public SessionItem
{

public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    static const QString P_INCLINATION_ANGLE;
    static const QString P_AZIMUTHAL_ANGLE;
    explicit BeamItem();
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

#endif // BEAMITEM_H

