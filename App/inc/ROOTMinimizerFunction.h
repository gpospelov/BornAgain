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

    ROOTMinimizerElementFunction(IMinimizer::function_t fcn, size_t ndims, IMinimizer::element_function_t element_fcn, size_t nelements)
        : ROOT::Math::FitMethodFunction(ndims, nelements)
        , m_fcn(fcn)
        , m_element_fcn(element_fcn)
        , m_ndims(ndims)
        , m_nelements(nelements)
        , m_ncalls(0)
        , m_ncalls_element(0)
        , m_prev_element(0)
    {
        m_parameter_values.resize(ndims, 0.0);
        m_residuals.resize(nelements, 0.0);
        m_gradients.resize(ndims);
        for(size_t i_dim=0; i_dim<ndims; ++i_dim) {
            m_gradients[i_dim].resize(nelements, 0.0);
        }
    }

    virtual ~ROOTMinimizerElementFunction(){}

    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
    ROOT::Math::IMultiGenFunction * Clone() const { return new ROOTMinimizerElementFunction(m_fcn, m_ndims, m_element_fcn, m_nelements); }

    //! evaluation of chi2
    double DoEval(const double * pars) const
    {
        double chi2 = 0.0;
        for(size_t i_data=0; i_data<m_nelements; ++i_data) {
            chi2 += DataElement(pars, i_data);
        }
        ++m_ncalls;
        std::cout << " ROOTMinimizerElementFunction::DoEval() -> " << chi2 << std::endl;
        return chi2;
    }

    //! evaluation of single data element residual
    double DataElement(const double *pars, unsigned int i_selected_element, double *gradient = 0) const ;

    virtual unsigned int NCalls() const { return m_ncalls; }
    virtual unsigned int NCallsElement() const { return m_ncalls_element; }

    bool isEqual(double a, double b) const
    {
        return std::abs(a-b) < 2.*Numeric::double_epsilon;
    }

    bool parametersHaveChanged(const double *pars) const
    {
        for(size_t i=0; i<m_ndims; ++i) {
            if( !isEqual(pars[i], m_parameter_values[i])) {
                std::copy(pars, pars+m_ndims, m_parameter_values.begin());
                return true;
            }
        }
        return false;
    }


private:

    IMinimizer::function_t m_fcn;
    IMinimizer::element_function_t m_element_fcn;
    size_t m_ndims;
    size_t m_nelements;
    mutable std::vector<double > m_parameter_values;
    mutable size_t m_ncalls;
    mutable size_t m_ncalls_element;
    mutable size_t m_prev_element;
    mutable std::vector<double > m_residuals; // [m_nelements]
    mutable std::vector<std::vector<double> > m_gradients; // [m_ndims][m_nelements]
};




#endif // ROOTMINIMIZERFUNCTION_H
