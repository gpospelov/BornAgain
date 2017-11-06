// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LayersWithAbsorptionBuilder.cpp
//! @brief     Implements class LayersWithAbsorptionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayersWithAbsorptionBuilder.h"
#include "MaterialFactoryFuncs.h"
#include "Exceptions.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"
#include "SampleComponents.h"
#include "FormFactors.h"

LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
    : m_ff(new FormFactorFullSphere(5.0*Units::nanometer))
{

}

LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder() = default;

MultiLayer* LayersWithAbsorptionBuilder::buildSample() const
{
    Material mAmbience = HomogeneousMaterial("Air", 0.0, 0.0);
    Material mMiddle = HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9);
    Material mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8);
    Material mParticle = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);

    const double middle_layer_thickness(60.0*Units::nanometer);

    Particle particle(mParticle, *m_ff);
    particle.setRotation(RotationZ(10.0*Units::degree));
    particle.rotate(RotationY(10.0*Units::degree));
    particle.rotate(RotationX(10.0*Units::degree));
    particle.setPosition(kvector_t(0.0, 0.0, -middle_layer_thickness/2.0 ));

    ParticleLayout layout;
    layout.addParticle(particle);

    Layer air_layer(mAmbience);
    Layer middle_layer(mMiddle, middle_layer_thickness);
    Layer substrate(mSubstrate);

    middle_layer.addLayout(layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}

MultiLayer* LayersWithAbsorptionBuilder::createSample(size_t index)
{
    if(index >= size())
        throw std::runtime_error("ParticleInTheAirBuilder::createSample() -> Error. "
                                 "Sample index is out of range.");

    auto ff_names = ff_components().keys();
    m_ff.reset(ff_components().getItem(ff_names[index])->clone());

    setName(ff_names[index]);

    return buildSample();
}

size_t LayersWithAbsorptionBuilder::size()
{
    return ff_components().size();
}

FormFactorComponents& LayersWithAbsorptionBuilder::ff_components()
{
    static FormFactorComponents result = FormFactorComponents();
    return result;
}

