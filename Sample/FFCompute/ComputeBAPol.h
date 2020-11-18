//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/ComputeBAPol.h
//! @brief     Defines class ComputeBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SCATTERING_COMPUTEBAPOL_H
#define BORNAGAIN_SAMPLE_SCATTERING_COMPUTEBAPOL_H

#include "Sample/FFCompute/IComputeFF.h"
#include "Sample/Scattering/IFormFactor.h"
#include <memory>

//! Evaluates the matrix BA term in a polarized IFormFactor.

//! @ingroup formfactors_internal

class ComputeBAPol final : public IComputeFF
{
public:
    ComputeBAPol(const IFormFactor& ff);
    ~ComputeBAPol() override;

    ComputeBAPol* clone() const override;

    //! Throws not-implemented exception
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    //! Calculates and returns a polarized form factor calculation in BA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_COMPUTEBAPOL_H
