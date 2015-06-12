// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestComponentLocator.cpp
//! @brief     Implements class FunctionalTestComponentLocator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestComponentLocator.h"
#include "ISampleBuilder.h"


FunctionalTestComponentLocator::FunctionalTestComponentLocator()
    : m_form_factor(0)
    , m_sample_builder(0)
{

}

IFormFactor *FunctionalTestComponentLocator::getFormFactor()
{
    return m_form_factor;
}

ISampleBuilder *FunctionalTestComponentLocator::getSampleBuilder()
{
    if(m_sample_builder) {
        m_sample_builder->init(this);
    }
    return m_sample_builder;
}
