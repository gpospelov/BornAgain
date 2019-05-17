// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedSample.cpp
//! @brief     Implements class ProcessedSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ProcessedSample.h"
#include "IFresnelMap.h"
#include "Layer.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "MultiLayerUtils.h"
#include "ProcessedLayout.h"
#include "SimulationOptions.h"
#include "Slice.h"

ProcessedSample::ProcessedSample(const MultiLayer& sample, const SimulationOptions& options)
    : m_slices{}, m_crossCorrLength{sample.crossCorrLength()}, m_ext_field{sample.externalField()}
{
    initSlices(sample, options);
    initLayouts(sample);
}

ProcessedSample::~ProcessedSample() = default;

size_t ProcessedSample::numberOfSlices() const
{
    return m_slices.size();
}

// Creates a array of slices with the correct thickness, roughness and material
void ProcessedSample::initSlices(const MultiLayer& sample, const SimulationOptions& options)
{
    if (sample.numberOfLayers() == 0)
        return;
    bool use_slicing = options.useAvgMaterials() && sample.numberOfLayers() > 1;
    auto layer_limits = MultiLayerUtils::ParticleRegions(sample, use_slicing);
    for (size_t i = 0; i < sample.numberOfLayers(); ++i) {
        auto p_layer = sample.layer(i);
        auto n_slices = p_layer->numberOfSlices();
        const ZLimits& slice_limits = layer_limits[i];
        double tl = p_layer->thickness();
        const Material* p_material = p_layer->material();
        auto p_roughness = sample.layerTopRoughness(i);
        if (p_roughness && p_roughness->getSigma() <= 0)
            p_roughness = nullptr;
        // if no slicing is needed, create single slice for the layer
        if (!slice_limits.isFinite() || n_slices == 0) {
            if (i == sample.numberOfLayers() - 1)
                tl = 0.0;
            addSlice(tl, *p_material, p_roughness);
            continue;
        }
        double top = slice_limits.upperLimit().m_value;
        double bottom = slice_limits.lowerLimit().m_value;
        // top layer
        if (i == 0) {
            if (top <= 0)
                throw std::runtime_error("ProcessedSample::ProcessedSample: "
                                         "top limit for top layer must be > 0.");
            addSlice(0.0, *p_material);
            addNSlices(n_slices, top - bottom, *p_material);
            if (bottom > 0) {
                addSlice(bottom, *p_material);
            }
        }
        // middle or bottom layer
        else {
            if (top < 0) {
                addSlice(-top, *p_material, p_roughness);
                addNSlices(n_slices, top - bottom, *p_material);
            } else {
                addNSlices(n_slices, top - bottom, *p_material, p_roughness);
            }
            // middle layer
            if (i < sample.numberOfLayers() - 1 && bottom > -tl) {
                addSlice(bottom + tl, *p_material);
            }
            // bottom layer
            if (i == sample.numberOfLayers() - 1) {
                addSlice(0.0, *p_material);
            }
        }
    }
}

void ProcessedSample::initLayouts(const MultiLayer &sample)
{
    double z_ref = 0.0;
    for (size_t i=0; i<sample.numberOfLayers(); ++i) {
        if (i>1)
            z_ref += sample.layerThickness(i-1);
        auto p_layer = sample.layer(i);
        for (auto p_layout : p_layer->layouts()) {
            m_layouts.emplace_back(*p_layout, m_slices, z_ref, mp_fresnel_map.get(), false);
        }
    }
}

void ProcessedSample::addSlice(double thickness, const Material& material, const LayerRoughness* p_roughness)
{
    if (p_roughness) {
        m_slices.emplace_back(thickness, material, *p_roughness);
    } else {
        m_slices.emplace_back(thickness, material);
    }
}

void ProcessedSample::addNSlices(size_t n, double thickness, const Material& material, const LayerRoughness* p_roughness)
{
    if (thickness <= 0.0)
        return;
    if (n == 0)
        throw std::runtime_error("ProcessedSample::addNSlices: number of slices should be "
                                 "bigger than zero.");
    double slice_thickness = thickness / n;
    addSlice(slice_thickness, material, p_roughness);
    for (size_t i = 1; i < n; ++i) {
        addSlice(slice_thickness, material);
    }
}
