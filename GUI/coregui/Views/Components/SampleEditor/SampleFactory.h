#ifndef SAMPLEFACTORY_H
#define SAMPLEFACTORY_H

#include "IFactory.h"
#include "ISample.h"
#include <string>


#include "Units.h"
#include "MaterialManager.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "FormFactorPyramid.h"
#include "InterferenceFunctionNone.h"


class SampleIsGISAXS9_Rotated : public MultiLayer
{
public:
    SampleIsGISAXS9_Rotated()
    {
        const double angle_around_z = 45.*Units::degree;
        complex_t n_air(1.0, 0.0);
        complex_t n_substrate(1.0-6e-6, 2e-8);
        complex_t n_particle(1.0-6e-4, 2e-8);
        const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", n_air);
        const IMaterial *p_substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        Particle *pyramid = new Particle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73)) );

        Geometry::Transform3D *transform = new Geometry::RotateZ3D(angle_around_z);

        ParticleDecoration particle_decoration;

        particle_decoration.addParticle(pyramid, transform);
        particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        addLayer(air_layer_decorator);
        addLayer(substrate_layer);
    }

    virtual ~SampleIsGISAXS9_Rotated(){}


};


class SampleFactory : public ISingleton<SampleFactory>, public IFactory<std::string, ISample>
{
public:
    SampleFactory();

    static ISample *createSample(const std::string &sample_name) { return instance().createItem(sample_name); }
};


#endif // SAMPLEFACTORY_H
