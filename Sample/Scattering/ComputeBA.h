//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/ComputeBA.h
//! @brief     Defines class ComputeBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SCATTERING_COMPUTEBA_H
#define BORNAGAIN_SAMPLE_SCATTERING_COMPUTEBA_H

#include "Sample/Scattering/IComputeFF.h"
#include <memory>

//! Evaluates the scalar Born form factor.
//! @ingroup formfactors_internal

class ComputeBA final : public IComputeFF
{
public:
    ComputeBA(const IFormFactor& ff);
    ~ComputeBA() override;

    ComputeBA* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setAmbientMaterial(const Material& material) override;

    //! Calculates and returns a form factor calculation in BA
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    double volume() const override;

    double radialExtension() const override;

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override;

private:
    //! The form factor for BA
    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_COMPUTEBA_H
