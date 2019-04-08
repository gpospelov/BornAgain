// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/FresnelInputData.cpp
//! @brief     Implements class FresnelInputData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FresnelInputData.h"
#include "MultiLayer.h"
#include "SimulationOptions.h"
#include "Slice.h"


FresnelInputData::FresnelInputData(const MultiLayer &sample, const SimulationOptions &options)
    : m_slices{}
{}

FresnelInputData::~FresnelInputData() =default;

size_t FresnelInputData::numberOfSlices() const
{
    return m_slices.size();
}
