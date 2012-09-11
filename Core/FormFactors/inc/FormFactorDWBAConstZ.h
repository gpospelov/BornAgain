#ifndef FORMFACTORDWBACONSTZ_H_
#define FORMFACTORDWBACONSTZ_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorDWBAConstZ.h
//! @brief  Definition of FormFactorDWBAConstZ
//! @author herck
//! @date   15.06.2012

#include "FormFactorDWBA.h"

class FormFactorDWBAConstZ: public FormFactorDWBA
{
public:
	FormFactorDWBAConstZ(IFormFactor* p_form_factor, double depth=0.0);
    virtual ~FormFactorDWBAConstZ();
    virtual FormFactorDWBAConstZ *clone() const;

    virtual complex_t evaluate(cvector_t k_i, cvector_t k_f,
    		double alpha_i, double alpha_f) const;
protected:
    double m_depth;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorDWBAConstZ(const FormFactorDWBAConstZ &);
    FormFactorDWBAConstZ &operator=(const FormFactorDWBAConstZ &);

    complex_t getDepthPhase(complex_t q_z) const;
};

#endif /* FORMFACTORDWBACONSTZ_H_ */
