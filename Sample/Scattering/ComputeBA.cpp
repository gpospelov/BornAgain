//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/ComputeBA.cpp
//! @brief     Implements class FormFactorBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Scattering/ComputeBA.h"
#include "Sample/Material/WavevectorInfo.h"

FormFactorBA::FormFactorBA(const IFormFactor& ff) : m_ff(ff.clone())
{
    setName("FormFactorBA");
}

FormFactorBA::~FormFactorBA() = default;

FormFactorBA* FormFactorBA::clone() const
{
    return new FormFactorBA(*m_ff);
}

complex_t FormFactorBA::evaluate(const WavevectorInfo& wavevectors) const
{
    return m_ff->evaluate(wavevectors);
}

void FormFactorBA::setAmbientMaterial(const Material& material)
{
    m_ff->setAmbientMaterial(material);
}

double FormFactorBA::volume() const
{
    return m_ff->volume();
}

double FormFactorBA::radialExtension() const
{
    return m_ff->radialExtension();
}

double FormFactorBA::bottomZ(const IRotation& rotation) const
{
    return m_ff->bottomZ(rotation);
}

double FormFactorBA::topZ(const IRotation& rotation) const
{
    return m_ff->topZ(rotation);
}
