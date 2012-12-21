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


#include "Numeric.h"
#include "IMinimizer.h"
#include "Math/Functor.h"
#include "Math/FitMethodFunction.h"
#include <vector>
#include <cmath>

//- -------------------------------------------------------------------
//! @class ROOTMinimizerFunction
//! @brief Basic minimizer function
//- -------------------------------------------------------------------
class ROOTMinimizerFunction : public ROOT::Math::Functor
{
public:
    ROOTMinimizerFunction(IMinimizer::function_chi2_t fcn, int ndims ) : ROOT::Math::Functor(fcn, ndims), m_fcn(fcn) {}
    virtual ~ROOTMinimizerFunction(){}
    IMinimizer::function_chi2_t m_fcn;
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

    ROOTMinimizerElementFunction(IMinimizer::function_gradient_t fun_gradient, size_t npars, size_t ndatasize)
        : ROOT::Math::FitMethodFunction(npars, ndatasize)
        , m_fun_gradient(fun_gradient) { }

    virtual ~ROOTMinimizerElementFunction(){}

    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
    ROOT::Math::IMultiGenFunction * Clone() const { return new ROOTMinimizerElementFunction(m_fun_gradient, NDim(), NPoints()); }

    //! evaluation of chi2
    double DoEval(const double * pars) const
    {
        std::cout << "ROOTMinimizerFuncion::DoEval() -> 1.1 ndim:" <<NDim() <<" npoint:" << NPoints() << std::endl;
        double chi2 = 0.0;
        for(size_t i_data=0; i_data<NPoints(); ++i_data) {
            double  res = DataElement(pars, i_data);
            chi2 += res*res;
        }
        std::cout << "ROOTMinimizerFuncion::DoEval() -> 1.2  chi:" <<chi2 << " ndim:" << NDim() << " np:" << NPoints() << std::endl;
        return chi2/double(NPoints());
        //return chi2;
    }

    //! evaluation of single data element residual
    double DataElement(const double *pars, unsigned int i_data, double *gradient = 0) const
    {
        return m_fun_gradient(pars, i_data, gradient);
    }

private:
    IMinimizer::function_gradient_t m_fun_gradient;
};




#endif // ROOTMINIMIZERFUNCTION_H
