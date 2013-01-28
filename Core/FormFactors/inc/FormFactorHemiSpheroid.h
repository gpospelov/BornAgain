#ifndef FORMFACTORHEMISPHEROID_H
#define FORMFACTORHEMISPHEROID_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorHemiSpheroid.h
//! @brief  Definition of FormFactorHemiSpheroid
//! @author Scientific Computing Group at FRM II
//! @date   03.07.2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"

//- -------------------------------------------------------------------
//! @class FormFactorHemiSpheroid
//! @brief Form factor of Cone
//- -------------------------------------------------------------------
class FormFactorHemiSpheroid : public IFormFactorBorn
{
public:
    //! @brief Cone constructor
    //! @param height of Conee
    //! @param radius half of Cone's base
    //! @param angle in radians between base and facet
    FormFactorHemiSpheroid(double radius,  double width, double height);
    double HemiSpheroidIntegral(double Z, void* params) const;

    ~FormFactorHemiSpheroid();
    virtual FormFactorHemiSpheroid* clone() const;

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q (const cvector_t &q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorHemiSpheroid(const FormFactorHemiSpheroid &);
    FormFactorHemiSpheroid &operator=(const FormFactorHemiSpheroid &);

    double evaluate_for_q_real() const;
    complex_t evaluate_for_q_imag() const;
    double HemiSpheroidIntegralReal(double Z, void* params) const;

    double HemiSpheroidIntegralImaginary(double Z, void* params) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_radius;
    double m_width;
    double m_height;
    mutable cvector_t m_q;

};


#endif // FormFactorHemiSpheroid_H
