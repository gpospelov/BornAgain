// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedLayout.h
//! @brief     Defines class ProcessedLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PROCESSEDLAYOUT_H
#define PROCESSEDLAYOUT_H

#include <memory>
#include <vector>

class FormFactorCoherentSum;
class IInterferenceFunction;

//! Data structure that contains preprocessed data for a single layout.
//!
//! If particles in the layout crossed the limits of the layer slices, these particles will
//! be sliced themselves.
//!
//! @ingroup algorithms_internal

class ProcessedLayout
{
public:

private:
    std::vector<FormFactorCoherentSum> m_formfactors;
    std::unique_ptr<IInterferenceFunction> mP_iff;
};

#endif // PROCESSEDLAYOUT_H
