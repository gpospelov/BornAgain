#ifndef MESOCRYSTAL_H_
#define MESOCRYSTAL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MesoCrystal.h
//! @brief  Definition of MesoCrystal class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 11, 2012

#include "IClusteredNanoParticles.h"
#include "IFormFactor.h"
#include "NanoParticle.h"

class MesoCrystal : public NanoParticle
{
public:
    MesoCrystal(IClusteredNanoParticles *p_nano_particle_structure, IFormFactor *p_form_factor);
    MesoCrystal(const IClusteredNanoParticles &nano_particle_structure, IFormFactor &form_factor);

    virtual ~MesoCrystal();
    virtual MesoCrystal *clone() const;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    {
        mp_nano_particle_structure->setAmbientRefractiveIndex(refractive_index);
    }

    virtual IFormFactor* createFormFactor() const
    {
        return mp_nano_particle_structure->createTotalFormFactor(*mp_meso_form_factor, m_ambient_refractive_index);
    }

    virtual void setFormFactor(IFormFactor* p_form_factor)
    {
        if (p_form_factor != mp_meso_form_factor) {
            delete mp_meso_form_factor;
            mp_meso_form_factor = p_form_factor;
        }
    }

private:
    IClusteredNanoParticles *mp_nano_particle_structure;
    IFormFactor *mp_meso_form_factor;
};


#endif /* MESOCRYSTAL_H_ */
