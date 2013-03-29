// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "Layer.h"
#include "Exceptions.h"
#include <iomanip>

//! Sets layer thickness in Angstrom.

void Layer::setThickness(double thickness)
{
    if (thickness<=0.0)
        throw DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
}

//! Sets _material_ of the layer.

void Layer::setMaterial(const IMaterial* material)
{ 
    if ( !material )
        throw NullPointerException("The material doesn't exist");
    mp_material = material;
}

//! Prints description.

void Layer::print(std::ostream& ostr) const
{
    ICompositeSample::print(ostr);
    ostr << "-->Layer{" <<  *getMaterial() << "}";
}
