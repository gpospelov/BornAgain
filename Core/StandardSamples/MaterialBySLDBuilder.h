// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MaterialBySLDBuilder.h
//! @brief     Defines class MaterialBySLDBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALBYSLDBUILDER_H_
#define MATERIALBYSLDBUILDER_H_

#include "IMultiLayerBuilder.h"

//! Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate.
//! Ti is 70 angstroms thick, Ni is 30 angstroms thick.
//! As opposed to HomogeneousMultilayerBuilder, uses MaterialBySLD. No absorption, no roughness.
//! @ingroup standard_samples

class BA_CORE_API_ MaterialBySLDBuilder : public IMultiLayerBuilder
{
public:
    MaterialBySLDBuilder();
    virtual MultiLayer* buildSample() const override;

protected:
    struct MaterialData {
        double product() const
        {
            return density * scat_length;
        }
        double scat_length; //!< bound coherent scattering length
        double density;     //!< number density
    };
    size_t m_number_of_layers;
    MaterialData m_si;
    MaterialData m_ti;
    MaterialData m_ni;
    double m_thick_ti; //!< thickness of titanium layer
    double m_thick_ni; //!< thickness of Ni layer
};

#endif /* MATERIALBYSLDBUILDER_H_ */
