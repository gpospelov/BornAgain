// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DiffuseDWBASimulation.h
//! @brief     Defines class DiffuseDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef DIFFUSEDWBASIMULATION_H_
#define DIFFUSEDWBASIMULATION_H_

#include "LayerDWBASimulation.h"
#include "DiffuseParticleInfo.h"

class DiffuseDWBASimulation: public LayerDWBASimulation
{
 public:
    DiffuseDWBASimulation()
        : m_refractive_index(1., 0.), m_surface_density(1.) {}
    virtual ~DiffuseDWBASimulation() {}

    virtual void run();
    size_t getSize() const { return m_np_infos.size(); }
    void addParticleInfo(DiffuseParticleInfo *p_info);
    void setRefractiveIndex(complex_t n) { m_refractive_index = n; }
    void setSurfaceDensity(double surface_density)
    { m_surface_density = surface_density; }
    void rescaleAbundances(double factor);

 protected:
    complex_t m_refractive_index;
    double m_surface_density;
    SafePointerVector<DiffuseParticleInfo> m_np_infos;
    struct DiffuseFormFactorTerm {
        DiffuseFormFactorTerm()
            : m_form_factors(), m_probabilities(), m_factor(0.) {}
        ~DiffuseFormFactorTerm();
        std::vector<IFormFactor*> m_form_factors;
        std::vector<double> m_probabilities;
        double m_factor;
    };
    void initDiffuseFormFactorTerms(
        std::vector<DiffuseFormFactorTerm *>& terms,
        size_t nbr_heights, size_t samples_per_particle);
};

#endif /* DIFFUSEDWBASIMULATION_H_ */
