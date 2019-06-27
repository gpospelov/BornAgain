// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedSample.h
//! @brief     Defines class ProcessedSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PROCESSEDSAMPLE_H
#define PROCESSEDSAMPLE_H

#include "Material.h"
#include "Vectors3D.h"
#include <map>
#include <memory>
#include <vector>

class HomogeneousRegion;
class IFresnelMap;
class LayerRoughness;
class MultiLayer;
class ProcessedLayout;
class SimulationOptions;
class Slice;

//! Data structure that contains all the necessary data for scattering calculations.
//!
//! If the usage of average materials is requested, layers and particles are sliced into multiple
//! slices and the average material is calculated for each slice.
//!
//! @ingroup algorithms_internal

class ProcessedSample
{
public:
    ProcessedSample(const MultiLayer& sample, const SimulationOptions& options);
    ~ProcessedSample();

    size_t numberOfSlices() const;
    const std::vector<ProcessedLayout>& layouts() const;
    const IFresnelMap* fresnelMap() const;


private:
    void initSlices(const MultiLayer& sample, const SimulationOptions& options);
    void initLayouts(const MultiLayer& sample);
    void addSlice(double thickness, const Material& material,
                  const LayerRoughness* p_roughness = nullptr);
    void addNSlices(size_t n, double thickness, const Material& material,
                    const LayerRoughness* p_roughness = nullptr);
    void initBFields();
    void mergeRegionMap(const std::map<size_t, std::vector<HomogeneousRegion>>& region_map);
    void initFresnelMap(const SimulationOptions& sim_options);
    std::unique_ptr<IFresnelMap> mP_fresnel_map;
    std::vector<Slice> m_slices;
    double m_top_z;
    std::vector<ProcessedLayout> m_layouts;
    double m_crossCorrLength;
    kvector_t m_ext_field;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // PROCESSEDSAMPLE_H
