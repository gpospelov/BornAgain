//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/ComputeDWBA.h
//! @brief     Defines class ComputeDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SCATTERING_COMPUTEDWBA_H
#define BORNAGAIN_SAMPLE_SCATTERING_COMPUTEDWBA_H

#include "Sample/Scattering/IComputeFF.h"
#include <memory>

class ILayerRTCoefficients;

//! Evaluates the coherent sum of the four DWBA terms in a scalar IFormFactor.
//! @ingroup formfactors_internal

class ComputeDWBA final : public IComputeFF
{
public:
    ComputeDWBA(const IFormFactor& ff);
    ~ComputeDWBA() override;

    ComputeDWBA* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Calculates and returns a form factor calculation in DWBA
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    void setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients> p_in_coeffs,
                         std::unique_ptr<const ILayerRTCoefficients> p_out_coeffs) override;

    friend class TestPolarizedDWBATerms;

private:
    std::unique_ptr<const ILayerRTCoefficients> m_in_coeffs;
    std::unique_ptr<const ILayerRTCoefficients> m_out_coeffs;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_COMPUTEDWBA_H
