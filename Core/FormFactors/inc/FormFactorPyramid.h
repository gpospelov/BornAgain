#ifndef FORMFACTORPYRAMID_H
#define FORMFACTORPYRAMID_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorPyramid.h
//! @brief  Definition of FormFactorPyramid
//! @author Scientific Computing Group at FRM II
//! @date   03.07.2012

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"


//- -------------------------------------------------------------------
//! @class FormFactorPyramid
//! @brief Form factor of pyramid
//- -------------------------------------------------------------------
class FormFactorPyramid : public IFormFactorBorn
{
public:
    //! @brief pyramid constructor
    //! @param height of pyramide
    //! @param half_side half of pyramid's base
    //! @param angle in radians between base and facet
    FormFactorPyramid(double height, double half_side, double alpha);

    ~FormFactorPyramid();
    virtual FormFactorPyramid *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorPyramid(const FormFactorPyramid &);
    FormFactorPyramid &operator=(const FormFactorPyramid &);

    double m_height;
    double m_half_side;
    double m_alpha;
};


#endif // FORMFACTORPYRAMID_H
