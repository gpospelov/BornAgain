#include "SpecularComputationTerm.h"
#include "SimulationElement.h"
#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MultiLayer.h"

SpecularComputationTerm::SpecularComputationTerm(const MultiLayer* p_multi_layer,
                                                 const IFresnelMap* p_fresnel_map)
    : IComputationTerm(p_multi_layer, p_fresnel_map)
{}

void SpecularComputationTerm::eval(ProgressHandler*,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it) const
{
    if (mp_multilayer->requiresMatrixRTCoefficients())
        return;

    for (auto it = begin_it; it != end_it; ++it)
        if (it->containsSpecularWavevector())
            evalSingle(it);
}

void SpecularComputationTerm::evalSingle(const std::vector<SimulationElement>::iterator& iter) const
{
    complex_t R = mp_fresnel_map->getInCoefficients(*iter, 0)->getScalarR();
    iter->setIntensity(std::norm(R));
}
