#ifndef DIFFUSEDWBASIMULATION_H_
#define DIFFUSEDWBASIMULATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DiffuseDWBASimulation.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Sep 4, 2012

#include "LayerDWBASimulation.h"
#include "DiffuseParticleInfo.h"

class DiffuseDWBASimulation: public LayerDWBASimulation
{
public:
    DiffuseDWBASimulation();
    virtual ~DiffuseDWBASimulation();

    virtual void run();
    size_t getSize() const { return m_np_infos.size(); }
    void addParticleInfo(DiffuseParticleInfo *p_info);
    void setRefractiveIndex(complex_t n) { m_refractive_index = n; }
    void setSurfaceDensity(double surface_density) { m_surface_density = surface_density; }
    void rescaleAbundances(double factor);

protected:
    complex_t m_refractive_index;
    double m_surface_density;
    std::vector<DiffuseParticleInfo *> m_np_infos;
};

#endif /* DIFFUSEDWBASIMULATION_H_ */
