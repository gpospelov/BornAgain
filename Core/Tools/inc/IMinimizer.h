#ifndef IMINIMIZER_H
#define IMINIMIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IMinimizer.h
//! @brief  Definition of Minimizer class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012


#include "FitParameter.h"
#include <boost/function.hpp>
#include <map>
#include "Exceptions.h"


//- -------------------------------------------------------------------
//! @class IMinimizer
//! @brief Common interface for all kind minimizer's
//- -------------------------------------------------------------------
class IMinimizer
{
public:
    IMinimizer(){}
    virtual ~IMinimizer(){}

    //! set variable
    virtual void setVariable(int index, const FitParameter *par) = 0;

    //! set function to minimize
    virtual void setFunction(boost::function<double(const double *)> fcn, int ndim=1) = 0;

//    //! set function and its gradient
//    virtual void setFunctionAndGradient(boost::function<double(const double *)> fcn, boost::function<double(const double *, int)> fcn_deriv, int ndim = 1) = 0;

    //! run minimization
    virtual void minimize() = 0;

    //! get number of variables to fit
    virtual size_t getNumberOfVariables() const = 0;

    //! return minimum function value
    virtual double getMinValue() const = 0;

    //! return pointer to the parameters values at the minimum
    virtual double getValueOfVariableAtMinimum(size_t i) const = 0;

    //! return pointer to the parameters values at the minimum
    virtual double getErrorOfVariable(size_t i) const = 0;

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear() = 0;

    //! print fit results
    virtual void printResults() const = 0;

};



//- -------------------------------------------------------------------
//! @class TestMinimizer
//! @brief Minimizer which calls minimization function once to test whole chain
//- -------------------------------------------------------------------
class TestMinimizer : public IMinimizer
{
public:
    TestMinimizer(){}
    virtual ~TestMinimizer(){}

    //! set variable
    virtual void setVariable(int index, const FitParameter *par) { m_values[index] = par->getValue(); }

    //! set function to minimize
    virtual void setFunction(boost::function<double(const double *)> fcn, int ndim=1) { m_fcn = fcn, m_ndim = ndim; }
//    virtual void setFunctionAndGradient(boost::function<double(const double *)> fcn, boost::function<double(const double *, int)> fcn_deriv, int ndim = 1) { (void)fcn; (void)fcn_deriv; (void)ndim; throw NotImplementedException("TestMinimizer::setFunctionGradient"); }

    //! run minimization
    virtual void minimize()
    {
        std::vector<double > buffer;
        buffer.resize(m_values.size(), 0.0);
        for(std::map<int, double >::iterator it=m_values.begin(); it!= m_values.end(); ++it ) {
            buffer[it->first] = it->second;
            std::cout << " minimize(): " << it->first << " " << it->second << std::endl;
        }
        std::cout << "TestMinimizer::minimize() -> Info. Calling fcn" << std::endl;
        m_fcn(&buffer[0]);
    }

    //! get number of variables to fit
    virtual size_t getNumberOfVariables() const { return m_values.size(); }

    //! return minimum function value
    virtual double getMinValue() const { throw NotImplementedException("TestMinimizer::getMinValue() -> Not implemented. "); return 0.0; }

    //! return pointer to the parameters values at the minimum
    virtual double getValueOfVariableAtMinimum(size_t i) const
    {
        std::map<int, double >::const_iterator pos = m_values.find((int)i);
        if(pos != m_values.end()){
            return pos->second;
        } else {
            throw LogicErrorException("TestMinimizer::getValueOfVariableAtMinimum() -> Not found!");
        }
    }

    //! return pointer to the parameters values at the minimum
    virtual double getErrorOfVariable(size_t /* i*/)  const { throw NotImplementedException("TestMinimizer::getMinValue() -> Not implemented. "); return 0.0; }

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear()  { throw NotImplementedException("TestMinimizer::getMinValue() -> Not implemented. "); }

    //! print fit results
    virtual void printResults() const  { throw NotImplementedException("TestMinimizer::getMinValue() -> Not implemented. "); }

private:
    std::map<int, double > m_values;
    boost::function<double(const double *)> m_fcn;
    int m_ndim;
};



#endif // IMINIMIZER_H
