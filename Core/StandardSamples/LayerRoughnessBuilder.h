// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/LayerRoughnessBuilder.h
//! @brief     Defines class LayerRoughnessBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERROUGHNESSBUILDER_H
#define LAYERROUGHNESSBUILDER_H

#include "ISampleBuilder.h"

//! The LayerRoughnessBuilder class to build sample: 
//! Layers with correlated roughness
class LayerRoughnessBuilder : public ISampleBuilder
{
public:
    LayerRoughnessBuilder();
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

#endif // ISGISAXS01BUILDER_H
