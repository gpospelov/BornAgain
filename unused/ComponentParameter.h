// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      unused/ComponentParameter.h
//! @brief     Defines class ComponentParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTPARAMETER_H
#define COMPONENTPARAMETER_H

#include "IParameter.h"
#include "ISample.h"
#include <string>

//! Wraps a parameter of type ISample.
//! @ingroup tools_internal

class BA_CORE_API_ ComponentParameter : public IParameter<ISample> {
public:
    ComponentParameter(
        const std::string& name, volatile ISample* par,
        const std::string& parent_name, const std::function<void()>& onChange)
    : IParameter<ISample>(name, par, parent_name, onChange) {}

    ComponentParameter* clone( const std::string& new_name="" ) const {
        return new ComponentParameter(
            new_name=="" ? getName() : new_name, m_data, m_parent_name, m_onChange); }

    bool operator==(const ComponentParameter& other) const {
        return *static_cast<const IParameter*>(this)==*static_cast<const IParameter*>(&other); }

protected:
};

#endif // COMPONENTPARAMETER_H
