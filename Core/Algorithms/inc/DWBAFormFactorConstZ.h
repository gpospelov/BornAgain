#ifndef DWBAFORMFACTORCONSTZ_H_
#define DWBAFORMFACTORCONSTZ_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DWBAFormFactorConstZ.h
//! @brief  Definition of DWBAFormFactorConstZ
//! @author herck
//! @date   15.06.2012

#include "DWBAFormFactor.h"

class DWBAFormFactorConstZ: public DWBAFormFactor
{
public:
	DWBAFormFactorConstZ(IFormFactor* p_form_factor, double depth=0.0);
    virtual ~DWBAFormFactorConstZ();
    virtual DWBAFormFactorConstZ *clone() const;

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;
    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f,
    		complex_t k_iz, complex_t k_fz) const;
protected:
    double m_depth;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    DWBAFormFactorConstZ(const DWBAFormFactorConstZ &);
    DWBAFormFactorConstZ &operator=(const DWBAFormFactorConstZ &);

    complex_t getDepthPhase(complex_t q_z) const;
};

#endif /* DWBAFORMFACTORCONSTZ_H_ */
