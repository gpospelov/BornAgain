// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedLayout.cpp
//! @brief     Implements class ProcessedLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ProcessedLayout.h"
#include "FormFactorBAPol.h"
#include "FormFactorCoherentSum.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "IInterferenceFunction.h"
#include "ILayout.h"
#include "IParticle.h"
#include "Slice.h"
#include "SlicedFormFactorList.h"

namespace
{
void ScaleRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map, double factor);
}

ProcessedLayout::ProcessedLayout(const ILayout& layout, const std::vector<Slice>& slices,
                                 double z_ref, const IMultiLayerFresnelMap* p_fresnel_map, bool polarized)
    : mp_fresnel_map(p_fresnel_map), m_polarized(polarized)
{
    collectFormFactors(layout, slices, z_ref);
    if (auto p_iff = layout.interferenceFunction())
        mP_iff.reset(p_iff->clone());
}

ProcessedLayout::ProcessedLayout(ProcessedLayout &&other)
{

}

ProcessedLayout::~ProcessedLayout() = default;

void ProcessedLayout::collectFormFactors(const ILayout& layout, const std::vector<Slice>& slices,
                                         double z_ref)
{
    SafePointerVector<class FormFactorCoherentSum> result;
    double layout_abundance = layout.getTotalAbundance();
    for (auto p_particle : layout.particles()) {
        auto p_ff_coh = ProcessParticle(*p_particle, slices, z_ref);
        p_ff_coh->scaleRelativeAbundance(layout_abundance);
        m_formfactors.push_back(p_ff_coh);
    }
    double weight = layout.weight();
    double scale_factor = weight * layout.totalParticleSurfaceDensity() / layout_abundance;
    ScaleRegionMap(m_region_map, scale_factor);
}

FormFactorCoherentSum* ProcessedLayout::ProcessParticle(const IParticle& particle,
                                                        const std::vector<Slice>& slices,
                                                        double z_ref)
{
    double abundance = particle.abundance();
    auto sliced_ffs = SlicedFormFactorList::CreateSlicedFormFactors(particle, slices, z_ref);
    auto region_map = sliced_ffs.regionMap();
    ScaleRegionMap(region_map, abundance);
    mergeRegionMap(region_map);
    std::unique_ptr<FormFactorCoherentSum> P_result(new FormFactorCoherentSum(abundance));
    for (size_t i = 0; i < sliced_ffs.size(); ++i) {
        auto ff_pair = sliced_ffs[i];
        std::unique_ptr<IFormFactor> P_ff_framework;
        if (slices.size() > 1) {
            if (m_polarized)
                P_ff_framework.reset(new FormFactorDWBAPol(*ff_pair.first));
            else
                P_ff_framework.reset(new FormFactorDWBA(*ff_pair.first));
        } else {
            if (m_polarized)
                P_ff_framework.reset(new FormFactorBAPol(*ff_pair.first));
            else
                P_ff_framework.reset(ff_pair.first->clone());
        }

        size_t slice_index = ff_pair.second;
        const Material slice_material = slices[slice_index].material();
        P_ff_framework->setAmbientMaterial(slice_material);

        auto part = FormFactorCoherentPart(P_ff_framework.release());
        part.setSpecularInfo(mp_fresnel_map, slice_index);

        P_result->addCoherentPart(part);
    }
    return P_result.release();
}

void ProcessedLayout::mergeRegionMap(
    const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    for (auto& entry : region_map) {
        size_t layer_index = entry.first;
        auto regions = entry.second;
        m_region_map[layer_index].insert(m_region_map[layer_index].begin(), regions.begin(),
                                         regions.end());
    }
}

namespace
{
void ScaleRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map, double factor)
{
    for (auto& entry : region_map) {
        for (auto& region : entry.second) {
            region.m_volume *= factor;
        }
    }
}
} // namespace
