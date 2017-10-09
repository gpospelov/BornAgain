// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TwoLayerRoughnessBuilder.h
//! @brief     Defines class TwoLayerRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TWOLAYERROUGHNESSBUILDER_H
#define TWOLAYERROUGHNESSBUILDER_H

#include "IMultiLayerBuilder.h"

class ISample;

//! Builds sample: two layers with rough interface.
//! @ingroup standard_samples

class BA_CORE_API_ TwoLayerRoughnessBuilder : public IMultiLayerBuilder
{
public:
    TwoLayerRoughnessBuilder();
    MultiLayer* buildSample() const;

private:
    double m_sigma;
    double m_hurst;
    double m_lateralCorrLength;
};

#endif // TWOLAYERROUGHNESSBUILDER_H
