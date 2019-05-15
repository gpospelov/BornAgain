// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedLayout.cpp
//! @brief     Implements class ProcessedLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ProcessedLayout.h"
#include "ILayout.h"
#include "IInterferenceFunction.h"

ProcessedLayout::ProcessedLayout(const ILayout& layout)
{
    if (auto p_iff = layout.interferenceFunction())
        mP_iff.reset(p_iff->clone());
}
