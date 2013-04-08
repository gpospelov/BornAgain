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
//! @class ROOTMinimizerChiSquaredFunction
//! @brief minimizer chi2 function
//- -------------------------------------------------------------------
class ROOTMinimizerChiSquaredFunction : public ROOT::Math::Functor
{
 public:
    ROOTMinimizerChiSquaredFunction(IMinimizer::function_chi2_t fcn, int ndims ) : ROOT::Math::Functor(fcn, ndims), m_fcn(fcn) {}
    virtual ~ROOTMinimizerChiSquaredFunction(){}
    IMinimizer::function_chi2_t m_fcn;
};


//- -------------------------------------------------------------------
//! @class ROOTMinimizerGradientFunction
//! @brief Minimizer function with access to single data element residuals.
//! Required by Fumili, Fumili2 and GSLMultiMin minimizers
//- -------------------------------------------------------------------
class ROOTMinimizerGradientFunction : public ROOT::Math::FitMethodFunction
{
 public:
    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t  Type_t;

    ROOTMinimizerGradientFunction(IMinimizer::function_gradient_t fun_gradient, size_t npars, size_t ndatasize)
        : ROOT::Math::FitMethodFunction((int)npars, (int)ndatasize)
        , m_fun_gradient(fun_gradient) { }

    virtual ~ROOTMinimizerGradientFunction(){}

    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
    ROOT::Math::IMultiGenFunction * Clone() const { return new ROOTMinimizerGradientFunction(m_fun_gradient, NDim(), NPoints()); }

    //! evaluation of single data element residual
    double DataElement(const double *pars, unsigned int i_data, double *gradient = 0) const {
        return m_fun_gradient(pars, i_data, gradient);
    }

 private:
    //! evaluation of chi2
    double DoEval(const double * pars) const {
        double chi2 = 0.0;
        for(size_t i_data=0; i_data<NPoints(); ++i_data) {
            double  res = DataElement(pars, (unsigned)i_data);
            chi2 += res*res;
        }
        return chi2/double(NPoints());
    }

    IMinimizer::function_gradient_t m_fun_gradient;
};


#endif // ROOTMINIMIZERFUNCTION_H
