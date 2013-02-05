#ifndef FORMFACTORCONE_H
#define FORMFACTORCONE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorCone.h
//! @brief  Definition of FormFactorCone
//! @author Scientific Computing Group at FRM II
//! @date   03.07.2012

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//- -------------------------------------------------------------------
//! @class FormFactorCone
//! @brief Form factor of Cone
//- -------------------------------------------------------------------
class FormFactorCone : public IFormFactorBorn
{
public:
    //! @brief Cone constructor
    //! @param height of Conee
    //! @param radius half of Cone's base
    //! @param angle in radians between base and facet
    FormFactorCone(double radius, double height,  double alpha);

    ~FormFactorCone();
    virtual FormFactorCone* clone() const;

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q (const cvector_t &q) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:

    //    double ConeIntegral(double Z, void* params) const;
    double evaluate_for_q_real() const;
    complex_t evaluate_for_q_imag() const;
    double ConeIntegralReal(double Z, void* params) const;
    double ConeIntegralImaginary(double Z, void* params) const;

    double m_radius;
    double m_height;
    double m_alpha;
    mutable cvector_t m_q;

};

#endif // FORMFACTORCONE_H
