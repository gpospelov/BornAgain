// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamItem.h
//! @brief     Defines class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BEAMITEM_H
#define BEAMITEM_H

#include "SessionItem.h"

class Beam;

class BA_CORE_API_ BeamItem : public SessionItem
{

public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    static const QString P_INCLINATION_ANGLE;
    static const QString P_AZIMUTHAL_ANGLE;
    static const QString P_POLARIZATION;

    explicit BeamItem(const QString& beam_model = Constants::BeamType);
    virtual ~BeamItem();

    double getIntensity() const;
    void setIntensity(double value);

    double getWavelength() const;
    void setWavelength(double value, const QString& distribution_name = QString());

    double getInclinationAngle() const;
    void setInclinationAngle(double value, const QString& distribution_name = QString());

    double getAzimuthalAngle() const;
    void setAzimuthalAngle(double value, const QString& distribution_name = QString());

    std::unique_ptr<Beam> createBeam() const;
};

class BA_CORE_API_ SpecularBeamItem : public BeamItem
{
public:
    SpecularBeamItem();
    virtual ~SpecularBeamItem();
};

#endif // BEAMITEM_H

