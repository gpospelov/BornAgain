// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/FresnelInputData.h
//! @brief     Defines class FresnelInputData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FRESNELINPUTDATA_H
#define FRESNELINPUTDATA_H

#include <vector>

class MultiLayer;
class LayerRoughness;
class SimulationOptions;
class Slice;

//! Data structure that contains all the necessary data for calculating the Fresnel coefficients.
//!
//! If the usage of average materials is requested, layers are sliced into multiple slices and
//! the average material is calculated for each slice.
//!
//! @ingroup algorithms_internal

class FresnelInputData
{
public:
    FresnelInputData(const MultiLayer& sample, const SimulationOptions& options);
    ~FresnelInputData();

    size_t numberOfSlices() const;

private:
    void initSlices(const MultiLayer& sample, const SimulationOptions& options);
    void addSlice(double thickness, const LayerRoughness* p_roughness=nullptr);
    void addNSlices(double thickness, size_t n, const LayerRoughness* p_roughness=nullptr);
    std::vector<Slice> m_slices;
};

#endif // FRESNELINPUTDATA_H
