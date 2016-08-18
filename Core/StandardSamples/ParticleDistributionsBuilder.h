// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleDistributionsBuilder.h
//! @brief     Defines classes of with different types of particle distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONSBUILDER_H
#define PARTICLEDISTRIBUTIONSBUILDER_H

#include "IMultiLayerBuilder.h"

//! Cylinders in BA with size distributions (IsGISAXS example #3, part II).
//! @ingroup standard_samples

class CylindersWithSizeDistributionBuilder : public IMultiLayerBuilder
{
public:
    CylindersWithSizeDistributionBuilder();
    MultiLayer* buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};


//! Builds mixture of cylinder particles with different size distribution (IsGISAXS example #2)
//! @ingroup standard_samples

class BA_CORE_API_ TwoTypesCylindersDistributionBuilder : public IMultiLayerBuilder
{
public:
    TwoTypesCylindersDistributionBuilder();
    MultiLayer* buildSample() const;

protected:
    void init_parameters();

private:
    double m_radius1;
    double m_radius2;
    double m_height1;
    double m_height2;
    double m_sigma1_ratio;
    double m_sigma2_ratio;
};

#endif // PARTICLEDISTRIBUTIONSBUILDER_H
