// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxesSquareLatticeBuilder.h
//! @brief     Defines class BoxesSquareLatticeBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BOXESSQUARELATTICEBUILDER_H
#define BOXESSQUARELATTICEBUILDER_H

#include "IMultiLayerBuilder.h"

class ISample;

//! Builds sample: square boxes in a square lattice
//! @ingroup standard_samples

class BA_CORE_API_ BoxesSquareLatticeBuilder : public IMultiLayerBuilder
{
public:
    BoxesSquareLatticeBuilder();
    MultiLayer* buildSample() const;

protected:
    void init_parameters();

private:
    double m_length;
    double m_height;
};

#endif // BOXESSQUARELATTICEBUILDER_H
