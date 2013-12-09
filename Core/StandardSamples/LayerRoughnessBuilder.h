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
