#ifndef ROOTMINIMIZER_H
#define ROOTMINIMIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ROOTMinimizer.h
//! @brief  Definition of ROOTMinimizer class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012

#include "IMinimizer.h"
#include "OutputData.h"
#include "Exceptions.h"
#include <string>
// from ROOT
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"


//- -------------------------------------------------------------------
//! @class ROOTMinimizer
//! @brief Wrapper for ROOT minimizers to interface with FitSuite
//- -------------------------------------------------------------------
class ROOTMinimizer : public IMinimizer
{
public:
    ROOTMinimizer(const std::string &minimizer_name, const std::string &algo_type);
    virtual ~ROOTMinimizer();

    virtual void setVariable(int i, const FitParameter *par) ;
    virtual void setFunction(boost::function<double(const double *)> fcn, int ndim=1);
    virtual void minimize();

    //! return pointer to created minimizer
    ROOT::Math::Minimizer *getROOTMinimizer() { return m_root_minimizer; }

    //! return minimum function value
    virtual double getMinValue() { return m_root_minimizer->MinValue(); }

    //! return value of variable corresponding the minimum of the function
    virtual double getValueOfVariableAtMinimum(size_t i) {
        if(i >= m_root_minimizer->NDim() ) throw OutOfBoundsException("ROOTMinimizer::getVariableAtMinimum() -> Wrong number of the variable");
        return m_root_minimizer->X()[i];
    }

private:
    ROOT::Math::Minimizer *m_root_minimizer;
    ROOT::Math::Functor *m_fcn;
};

#endif // ROOTMINIMIZER_H
