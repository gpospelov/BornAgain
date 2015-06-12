// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestComponentLocator.h
//! @brief     Defines class FunctionalTestComponentLocator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTCOMPONENTLOCATOR_H
#define FUNCTIONALTESTCOMPONENTLOCATOR_H

#include "IComponentLocator.h"

class IFormFactor;
class ISampleBuilder;

//! @class FunctionalTestComponentLocator
//! @ingroup standard_samples
//! @brief Provides FunctionalTest with all components it needs to run

class BA_CORE_API_ FunctionalTestComponentLocator : public IComponentLocator
{
public:
    FunctionalTestComponentLocator();

    void register_component(IFormFactor *form_factor) { m_form_factor = form_factor;}
    IFormFactor *getFormFactor();

    void register_component(ISampleBuilder *sample_builder) { m_sample_builder = sample_builder;}
    ISampleBuilder *getSampleBuilder();

private:
    IFormFactor *m_form_factor;
    ISampleBuilder *m_sample_builder;
};

#endif
