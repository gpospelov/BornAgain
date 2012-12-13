#ifndef TESTFUMILILMA_H
#define TESTFUMILILMA_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFittingModule1.h
//! @brief  Definition of TestFittingModule class
//! @author Scientific Computing Group at FRM II
//! @date   Dec 5, 2012

#include "MathFunctions.h"
#include "IFunctionalTest.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/FitMethodFunction.h"
#include "OutputData.h"
#include "Math/Functor.h"
#include "gsl/gsl_sf_trig.h"
#include "Fit/Fitter.h"
#include <cmath>

class TF2;
class IFunctionObject;
class IChiSquaredModule;
class TCanvas;


//- -------------------------------------------------------------------
//! @class TestFumiliLMA
//! @brief Test of ROOT's LMA-based minimizers Fumili and GSLMultiFit
//- -------------------------------------------------------------------
class TestFumiliLMA : public IFunctionalTest
{
public:
    friend class MyChi2Function;

    TestFumiliLMA();
    virtual ~TestFumiliLMA();
    virtual void execute();

    double functionToMinimize(const double *pars);

private:
    void FillOutputDataFromFunction(OutputData<double> &data, TF2 *fun, int nbinsx=100, int nbinsy=100);

    ROOT::Math::Minimizer *m_root_minimizer; //! minimizer
    ROOT::Math::Functor *m_fcn; //! fit function
    IFunctionObject *m_func_object; //! simulation function
    TF2 *m_func; //! ROOT representation of the simulation function with min, max defined
    IChiSquaredModule *m_chi_module; //! chi squared module
    OutputData<double > *m_real_data; //! real data
    size_t m_ndim; //! number of fit parametrs
    double m_sigma; //! gaussian noise
    TCanvas *m_c1;
};


class IFunctionObject
{
public:
    virtual ~IFunctionObject(){}
    virtual double operator()(const double *xx, const double *pars ) = 0;
};


class RosenBrockFunctionObject : public IFunctionObject
{
public:
    double operator()(const double *xx, const double *pars )
    {
        const double x = xx[0];
        const double y = xx[1];
        const double tmp1 = y-x*x;
        const double tmp2 = 1-x;
        const double p0=pars[0];
        const double p1=pars[1];
        return p0*100*tmp1*tmp1 + p1*tmp2*tmp2;
    }
};


class SincXSincYFunctionObject : public IFunctionObject
{
public:
    double operator()(const double *xx, const double *pars )
    {
        const double x = xx[0];
        const double y = xx[1];
        const double p0=pars[0];
        const double p1=pars[1];
        const double p2=pars[2];
        double value = p0 * MathFunctions::Sinc(x-p1) * MathFunctions::Sinc(y-p2);
        return value;
    }
};


class MyChi2Function : public ROOT::Math::FitMethodFunction
{
public:
    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t  Type_t;

    MyChi2Function(TestFumiliLMA *test) : ROOT::Math::FitMethodFunction(test->m_ndim, test->m_real_data->getAllocatedSize()), m_test(test) {}
    virtual ~MyChi2Function(){}

    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
    ROOT::Math::IMultiGenFunction * Clone() const { return new MyChi2Function(m_test); }

    // evaluation of the all chi2
    double DoEval(const double * par) const {
       int ndata = NPoints();
       std::cout << "DoEval: " << ndata << std::endl;
       double chi2 = 0;
       for (int i = 0; i <  ndata; ++i) {
          double res = DataElement( par, i);
          chi2 += res*res;
       }
       //std::cout << "DoEval: chi" << chi2/double(ndata) << std::endl;
       return chi2/double(ndata);
    }

    double DataElement(const double *par, unsigned int i, double *g = 0) const;

    TestFumiliLMA *m_test;
};


#endif // TESTFUMILILMA_H
