#include "LayerDecoratorDWBASimulation.h"
#include "LayerDecorator.h"
#include "DWBAFormFactorConstZ.h"

LayerDecoratorDWBASimulation::LayerDecoratorDWBASimulation(
        const LayerDecorator *p_layer_decorator)
{
    mp_layer_decorator = p_layer_decorator->clone();
}

LayerDecoratorDWBASimulation::~LayerDecoratorDWBASimulation()
{
    delete mp_layer_decorator;
}

void LayerDecoratorDWBASimulation::init(const Experiment& experiment)
{
    m_dwba_intensity.clear();
    Detector detector = experiment.getDetector();
    size_t detector_dimension = detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_dwba_intensity.addAxis(new NamedVector<double>(detector.getAxis(dim)));
    }
    Beam beam = experiment.getBeam();
    m_ki = beam.getCentralK();
    m_alpha_i = std::asin(m_ki.z()/m_ki.mag());
}

void LayerDecoratorDWBASimulation::run()
{
    m_dwba_intensity.resetIndex();
    NanoParticle *p_particle = mp_layer_decorator->getDecoration()->getNanoParticle(0);
    complex_t n_decoration = p_particle->getRefractiveIndex();
    complex_t n_layer = mp_layer_decorator->getRefractiveIndex();
    double lambda = 2.0*M_PI/m_ki.mag();
    double normalizing_factor = std::norm((n_layer*n_layer - n_decoration*n_decoration)*M_PI/lambda/lambda);
    DWBAFormFactorConstZ dwba_z(p_particle->getFormFactor()->clone());
    dwba_z.setReflectionFunction(mp_R_function);
    dwba_z.setTransmissionFunction(mp_T_function);
    complex_t k_iz = -mp_kz_function->evaluate(-m_alpha_i);
    const IInterferenceFunction *p_interference_function = mp_layer_decorator->getDecoration()->getInterferenceFunction();
    while (m_dwba_intensity.hasNext())
    {
        double phi_f = m_dwba_intensity.getCurrentValueOfAxis<double>("phi_f");
        double alpha_f = m_dwba_intensity.getCurrentValueOfAxis<double>("alpha_f");
        kvector_t k_f;
        complex_t k_fz = mp_kz_function->evaluate(alpha_f);
        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
        complex_t ff = dwba_z.evaluateForComplexkz(m_ki, k_f, k_iz, k_fz);
        m_dwba_intensity.next() = normalizing_factor*std::norm(ff)*p_interference_function->evaluate(m_ki-k_f);
    }
}
