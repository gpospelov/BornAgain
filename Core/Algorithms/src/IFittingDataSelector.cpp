// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IFittingDataSelector.cpp
//! @brief     Implements class DefaultAllDataSelector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFittingDataSelector.h"

OutputData<double> *DefaultAllDataSelector::createWeightMap(const OutputData<double>& real_data,
        const OutputData<double>& simulated_data) const
{
    if (simulated_data.getAllocatedSize() != real_data.getAllocatedSize()) {
        throw RuntimeErrorException("DefaultAllDataSelector::createWeightMap() -> Size of simulated data should be equal to the size of real data.");
    }
    OutputData<double> *p_result = real_data.clone();
    p_result->setAllTo(1.0);
    return p_result;
}
