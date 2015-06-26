// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/MultiLayerWithRoughnessBuilder.h
//! @brief     Defines class MultiLayerWithRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERWITHROUGHNESSBUILDER_H
#define MULTILAYERWITHROUGHNESSBUILDER_H

#include "ISampleBuilder.h"

//! @class MultiLayerWithRoughnessBuilder
//! @ingroup standard_samples
//! @brief Builds sample: layers with correlated roughness

class BA_CORE_API_ MultiLayerWithRoughnessBuilder : public ISampleBuilder
{
public:
    MultiLayerWithRoughnessBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_thicknessA;
    double m_thicknessB;
    double m_sigma;
    double m_hurst;
    double m_latteralCorrLength;
    double m_crossCorrLength;
};

#endif // MULTILAYERWITHROUGHNESSBUILDER_H
