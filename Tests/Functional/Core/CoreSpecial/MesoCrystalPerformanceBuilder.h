// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/MesoCrystalPerformanceBuilder.h
//! @brief     Defines MesoCrystalPerformanceBuilder class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MESOCRYSTALPERFORMANCEBUILDER_H
#define MESOCRYSTALPERFORMANCEBUILDER_H

#include "Core/Material/Material.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"

class MesoCrystal;
class IFormFactor;

//! Runs heavy mesocrystal simulation to investigate where it spends time.

class MesoCrystalPerformanceBuilder : public IMultiLayerBuilder
{
public:
    MesoCrystalPerformanceBuilder();
    ~MesoCrystalPerformanceBuilder();

protected:
    MultiLayer* buildSample() const;

private:
    std::unique_ptr<MesoCrystal> createMeso(Material material,
                                            const IFormFactor& form_factor) const;

    double m_lattice_length_a;
    double m_lattice_length_c;
    double m_nanoparticle_radius;
    double m_sigma_nanoparticle_radius;
    double m_meso_height;
    double m_meso_radius;
    double m_sigma_lattice_length_a;
    double m_roughness;
    double m_surface_filling_ratio;
    double m_phi_start;
    double m_phi_stop;
    int m_phi_rotation_steps;
    double m_tilt_start;
    double m_tilt_stop;
    int m_tilt_steps;
};

#endif // FOURIERTRANSFORMATIONTEST_H
