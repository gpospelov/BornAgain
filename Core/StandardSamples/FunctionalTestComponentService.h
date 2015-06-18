// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestComponentService.h
//! @brief     Defines class FunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTCOMPONENTSERVICE_H
#define FUNCTIONALTESTCOMPONENTSERVICE_H

#include <vector>
class IComponentLocator;

class FunctionalTestComponentService {
public:
    typedef std::vector<IComponentLocator *> components_t;
    typedef std::vector<IComponentLocator *>::iterator iterator;

    FunctionalTestComponentService(const std::string &simulation_name,
                                   const std::string &sample_builder_name,
                                   const std::string &factory_name);

    iterator begin() { return m_components.begin(); }
    iterator end() { return m_components.end(); }

private:
    components_t m_components;
};


#endif

