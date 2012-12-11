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



//#include "Math/Minimizer.h"
//#include "Math/Factory.h"
//#include "Math/FitMethodFunction.h"


////- -------------------------------------------------------------------
////! @class ROOTMinimizerFunction
////! @brief
////- -------------------------------------------------------------------

//class ROOTMinimizerFunction : public ROOT::Math::FitMethodFunction
//{
//public:
//    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t  Type_t;
//    typedef boost::function<double(const double *)> function_eval_t;
//    typedef boost::function<double(const double *, unsigned int, double *)> function_element_t;

//    ROOTMinimizerFunction();
//    virtual ~ROOTMinimizerFunction(){}

//    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
//    ROOT::Math::IMultiGenFunction * Clone() const { return new MyChi2Function(m_test); }

//    double DoEval(const double * par) const {


//};


//class MyChi2Function : public ROOT::Math::FitMethodFunction
//{
//public:
//    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t  Type_t;

//    MyChi2Function(TestFumiliLMA *test) : ROOT::Math::FitMethodFunction(test->m_ndim, test->m_real_data->getAllocatedSize()), m_test(test) {}
//    virtual ~MyChi2Function(){}

//    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
//    ROOT::Math::IMultiGenFunction * Clone() const { return new MyChi2Function(m_test); }

//    // evaluation of the all chi2
//    double DoEval(const double * par) const {
//       int ndata = NPoints();
//       std::cout << "DoEval: " << ndata << std::endl;
//       double chi2 = 0;
//       for (int i = 0; i <  ndata; ++i) {
//          double res = DataElement( par, i);
//          chi2 += res*res;
//       }
//       //std::cout << "DoEval: chi" << chi2/double(ndata) << std::endl;
//       return chi2/double(ndata);
//    }

//    double DataElement(const double *par, unsigned int i, double *g = 0) const;

//    TestFumiliLMA *m_test;
//};



#endif // ROOTMINIMIZERFUNCTION_H
