// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/LayerRoughnessBuilder.cpp
//! @brief     Implement class LayerRoughnessBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerRoughnessBuilder.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "Units.h"
#include "IRoughness.h"

LayerRoughnessBuilder::LayerRoughnessBuilder()
    : m_thicknessA(2.5*Units::nanometer)
    , m_thicknessB(5.0*Units::nanometer)
    , m_sigma(1.0*Units::nanometer)
    , m_hurst(0.3)
    , m_latteralCorrLength(5.0*Units::nanometer)
    , m_crossCorrLength(1e-4)
{
    init_parameters();
}


void LayerRoughnessBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("thicknessA", &m_thicknessA);
    registerParameter("thicknessB", &m_thicknessB);
    registerParameter("sigma", &m_sigma);
    registerParameter("hurst", &m_hurst);
    registerParameter("latteralCorrLength", &m_latteralCorrLength);
    registerParameter("crossCorrLength", &m_crossCorrLength);
}


ISample *LayerRoughnessBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0., 0.);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 15e-6, 0.0);
    const IMaterial *p_part_a_material =
            MaterialManager::getHomogeneousMaterial("PartA", 5e-6, 0.0);
   const IMaterial *p_part_b_material =
            MaterialManager::getHomogeneousMaterial("PartB", 10e-6, 0.0);


    Layer air_layer;
    air_layer.setMaterialAndThickness(p_air_material, 0);
	Layer partA_layer;
    partA_layer.setMaterialAndThickness(p_part_a_material, m_thicknessA);
	Layer partB_layer;
    partB_layer.setMaterialAndThickness(p_part_b_material, m_thicknessB);
    Layer substrate_layer;
    substrate_layer.setMaterialAndThickness(p_substrate_material, 0);

    LayerRoughness *roughness = new LayerRoughness();
    roughness->setSigma(m_sigma);
    roughness->setHurstParameter(m_hurst);
    roughness->setLatteralCorrLength(m_latteralCorrLength);

    multi_layer->addLayer(air_layer);
    for (int i = 0; i<5; ++i) {
        multi_layer->addLayerWithTopRoughness(partA_layer, *roughness);
        multi_layer->addLayerWithTopRoughness(partB_layer, *roughness);
    }

    multi_layer->addLayerWithTopRoughness(substrate_layer, *roughness);
    multi_layer->setCrossCorrLength(m_crossCorrLength);
    return multi_layer;
}

