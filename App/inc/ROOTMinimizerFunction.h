#ifndef ROOTMINIMIZERFUNCTION_H
#define ROOTMINIMIZERFUNCTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ROOTMinimizerFunction.h
//! @brief  Definition of ROOTMinimizerFunction
//! @author Scientific Computing Group at FRM II
//! @date   Dec 10, 2012


#include "IMinimizer.h"
#include "Math/Functor.h"
#include "Math/FitMethodFunction.h"

//- -------------------------------------------------------------------
//! @class ROOTMinimizerFunction
//! @brief Basic minimizer function
//- -------------------------------------------------------------------
class ROOTMinimizerFunction : public ROOT::Math::Functor
{
public:
    ROOTMinimizerFunction(IMinimizer::function_t fcn, int ndims ) : ROOT::Math::Functor(fcn, ndims), m_fcn(fcn) {}
    virtual ~ROOTMinimizerFunction(){}
    IMinimizer::function_t m_fcn;
};


//- -------------------------------------------------------------------
//! @class ROOTMinimizerElementFunction
//! @brief Minimizer function with access to single data element residuals.
//! Required by Fumili, Fumili2 and GSLMultiMin minimizers
//- -------------------------------------------------------------------
class ROOTMinimizerElementFunction : public ROOT::Math::FitMethodFunction
{
public:
    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t  Type_t;

    ROOTMinimizerElementFunction(IMinimizer::function_t fcn, int ndims, IMinimizer::element_function_t element_fcn, int nelements)
        : ROOT::Math::FitMethodFunction(ndims, nelements)
        , m_fcn(fcn)
        , m_element_fcn(element_fcn)
        , m_ndims(ndims)
        , m_nelements(nelements)
        , m_ncalls(0)
        , m_ncalls_element(0) { }

    virtual ~ROOTMinimizerElementFunction(){}

    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
    ROOT::Math::IMultiGenFunction * Clone() const { return new ROOTMinimizerElementFunction(m_fcn, m_ndims, m_element_fcn, m_nelements); }

    //! evaluation of chi2
    double DoEval(const double * par) const { ++m_ncalls; return m_fcn(par); }

    //! evaluation of single data element residual
    double DataElement(const double *par, unsigned int i, double *g = 0) const { m_ncalls_element++; return m_element_fcn(par,i,g); }

    virtual unsigned int NCalls() const { return (unsigned int)m_ncalls; }
    virtual unsigned int NCallsElement() const { return (unsigned int)m_ncalls_element; }
private:
    IMinimizer::function_t m_fcn;
    IMinimizer::element_function_t m_element_fcn;
    int m_ndims;
    int m_nelements;
    mutable size_t m_ncalls;
    mutable size_t m_ncalls_element;
};




#endif // ROOTMINIMIZERFUNCTION_H
