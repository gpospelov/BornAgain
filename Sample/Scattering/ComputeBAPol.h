//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/ComputeBAPol.h
//! @brief     Defines class ComputeBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORBAPOL_H
#define BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORBAPOL_H

#include "Sample/Scattering/IFormFactor.h"
#include <memory>

//! Evaluates the matrix BA term in a polarized IFormFactor.

//! @ingroup formfactors_internal

class ComputeBAPol final : public IFormFactor
{
public:
    ComputeBAPol(const IFormFactor& ff);
    ~ComputeBAPol() override;

    ComputeBAPol* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setAmbientMaterial(const Material& material) override;

    //! Throws not-implemented exception
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    //! Calculates and returns a polarized form factor calculation in BA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;

    double volume() const override;

    double radialExtension() const override;

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override;

private:
    //! The form factor for BA
    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORBAPOL_H
