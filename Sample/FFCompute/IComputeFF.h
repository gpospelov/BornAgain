//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/IComputeFF.h
//! @brief     Defines and implements pure virtual interface IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SCATTERING_ICOMPUTEFF_H
#define BORNAGAIN_SAMPLE_SCATTERING_ICOMPUTEFF_H

#include "Sample/Scattering/IFormFactor.h"

class IComputeFF : public IFormFactor {

public:
    IComputeFF() = delete;
    void setAmbientMaterial(const Material& material) final;

    double volume() const final;
    double radialExtension() const final;
    double bottomZ(const IRotation& rotation) const final;
    double topZ(const IRotation& rotation) const final;

protected:
    IComputeFF(const IFormFactor&);

    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_ICOMPUTEFF_H
