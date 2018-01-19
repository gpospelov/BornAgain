// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MaterialBySLDBuilder.h
//! @brief     Defines class MaterialBySLDBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALBYSLDBUILDER_H_
#define MATERIALBYSLDBUILDER_H_

#include "IMultiLayerBuilder.h"

//! Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate.
//! Ti is 70 angstroms thick, Ni is 30 angstroms thick.
//! Titanium absorption coefficient is exaggerated 10^4 times for its effect to be noticeable
//! @ingroup standard_samples

class BA_CORE_API_ MaterialBySLDBuilder : public IMultiLayerBuilder
{
public:
    MaterialBySLDBuilder();
    MultiLayer* buildSample() const override;

protected:
    struct MaterialData {
        double sld() const
        {
            return density * scat_length;
        }

        //! Returns macroscopic cross-section for 2200 m/s neutrons
        double abs_term() const
        {
            return density * abs_cx;
        }

        double scat_length; //!< bound coherent scattering length
        double density;     //!< number density
        double abs_cx;      //!< absorption cross-section for 2200 m/s neutrons
    };
    size_t m_number_of_layers;
    MaterialData m_si;
    MaterialData m_ti;
    MaterialData m_ni;
    double m_thick_ti; //!< thickness of titanium layer
    double m_thick_ni; //!< thickness of Ni layer
};

#endif /* MATERIALBYSLDBUILDER_H_ */
