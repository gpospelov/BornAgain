// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultipleLayoutBuilder.h
//! @brief     Defines class MultipleLayoutBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTIPLELAYOUTBUILDER_H
#define MULTIPLELAYOUTBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

class ISample;

//! Builds sample: mixture of cylinders and prisms without interference,
//! using multiple particle layouts
//! @ingroup standard_samples

class BA_CORE_API_ MultipleLayoutBuilder : public IMultiLayerBuilder
{
public:
    MultipleLayoutBuilder();
    MultiLayer* buildSample() const;

private:
    double m_cylinder_height;
    double m_cylinder_radius;
    double m_prism_height;
    double m_prism_length;
    double m_cylinder_weight;
};

#endif // MULTIPLELAYOUTBUILDER_H
