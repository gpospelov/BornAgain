#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MultiLayer.h"
#include "SpecularComputationTerm.h"
#include "SpecularData.h"
#include "SpecularSimulationElement.h"

SpecularComputationTerm::SpecularComputationTerm(const MultiLayer* p_multi_layer,
                                                 const IFresnelMap* p_fresnel_map)
    : mp_multilayer(p_multi_layer)
    , mp_fresnel_map(p_fresnel_map)
{}

void SpecularComputationTerm::eval(ProgressHandler*, const SpecularElementIter& begin_it,
                                   const SpecularElementIter& end_it) const
{
    if (mp_multilayer->requiresMatrixRTCoefficients())
        return;

    for (auto it = begin_it; it != end_it; ++it)
        evalSingle(it);
}

void SpecularComputationTerm::evalSingle(const SpecularElementIter& iter) const
{
    mp_fresnel_map->fillSpecularData(*iter);
    const ILayerRTCoefficients& layer_data = (*iter->specularData())[0];
    iter->setIntensity(std::norm(layer_data.getScalarR()));
}
