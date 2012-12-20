#ifndef ROOTGSLNLSMINIMIZER_H
#define ROOTGSLNLSMINIMIZER_H

#ifndef ROOT_Math_Minimizer
#include "Math/Minimizer.h"
#endif


#ifndef ROOT_Math_IFunctionfwd
#include "Math/IFunctionfwd.h"
#endif

#ifndef ROOT_Math_IParamFunctionfwd
#include "Math/IParamFunctionfwd.h"
#endif

#ifndef ROOT_Math_FitMethodFunction
#include "Math/FitMethodFunction.h"
#endif

#ifndef ROOT_Math_MinimizerVariable
#include "Math/MinimizerVariable.h"
#endif


#include <vector>
#include <map>
#include <string>

// from GSLMultiFitFunctionAdapter.h
#include "gsl/gsl_vector.h"
#include "gsl/gsl_matrix.h"
#include <cassert>
#include <iostream>
// from GSLMultiFitFunctionWrapper.h
#include "gsl/gsl_multifit.h"
// from GSLMultiFit.h
#include "gsl/gsl_vector.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_multifit_nlin.h"
#include "gsl/gsl_blas.h"
#include "Math/IFunction.h"
#include <string>
#include <cassert>

#include "Fit/Fitter.h"
#include "Math/MinimTransformFunction.h"
#include "Math/MultiNumGradFunction.h"
#include "Math/MinimizerVariable.h"

namespace ROOT {

namespace Patch {

typedef ROOT::Math::IMultiGradFunction IMultiGradFunction;
typedef ROOT::Math::IMultiGenFunction IMultiGenFunction;
typedef ROOT::Math::FitMethodFunction FitMethodFunction;
typedef ROOT::Math::MinimTransformFunction MinimTransformFunction;
typedef ROOT::Math::MultiNumGradFunction MultiNumGradFunction;

template<class FuncVector>
class GSLMultiFitFunctionAdapter {

public:

    static int F( const gsl_vector * x, void * p, gsl_vector * f ) {
        // p is a pointer to an iterator of functions
        unsigned int n = f->size;
        // need to copy iterator otherwise next time the function is called it wont work
        FuncVector  & funcVec = *( reinterpret_cast< FuncVector *> (p) );
        if (n == 0) return -1;
        for (unsigned int i = 0; i < n ; ++i) {
            gsl_vector_set(f, i, (funcVec[i])(x->data) );
        }
        return 0;
    }


    static int Df(  const gsl_vector * x, void * p, gsl_matrix * h) {

        // p is a pointer to an iterator of functions
        unsigned int n = h->size1;
        unsigned int npar = h->size2;
        if (n == 0) return -1;
        if (npar == 0) return -2;
        FuncVector  & funcVec = *( reinterpret_cast< FuncVector *> (p) );
        for (unsigned int i = 0; i < n ; ++i) {
            double * g = (h->data)+i*npar;   //pointer to start  of i-th row
            assert ( npar == (funcVec[i]).NDim() );
            (funcVec[i]).Gradient(x->data, g);
        }
        return 0;
    }

    /// evaluate derivative and function at the same time
    static int FDf(  const gsl_vector * x, void * p,  gsl_vector * f, gsl_matrix * h) {
        // should be implemented in the function
        // p is a pointer to an iterator of functions
        unsigned int n = h->size1;
        unsigned int npar = h->size2;
        if (n == 0) return -1;
        if (npar == 0) return -2;
        FuncVector  & funcVec = *( reinterpret_cast< FuncVector *> (p) );
        assert ( f->size == n);
        for (unsigned int i = 0; i < n ; ++i) {
            assert ( npar == (funcVec[i]).NDim() );
            double fval = 0;
            double * g = (h->data)+i*npar;   //pointer to start  of i-th row
            (funcVec[i]).FdF(x->data, fval, g);
            gsl_vector_set(f, i, fval  );
        }
        return 0;
    }

};



typedef double ( * GSLMultiFitFPointer ) ( const gsl_vector *, void *, gsl_vector *);
typedef void   ( * GSLMultiFitDfPointer )   ( const gsl_vector *, void *, gsl_matrix *);
typedef void   ( * GSLMultiFitFdfPointer ) ( const gsl_vector *, void *, gsl_vector *, gsl_matrix *);


/**
wrapper to a multi-dim function withtout  derivatives for multi-dimensional
minimization algorithm

@ingroup MultiMin
*/

class GSLMultiFitFunctionWrapper {

public:

    GSLMultiFitFunctionWrapper()
    {
        fFunc.f = 0;
        fFunc.df = 0;
        fFunc.fdf = 0;
        fFunc.n = 0;
        fFunc.p = 0;
        fFunc.params = 0;
    }


    /// Fill gsl function structure from a C++ function iterator and size and number of residuals
    template<class FuncVector>
    void SetFunction(const FuncVector & f, unsigned int nres, unsigned int npar  ) {
        const void * p = &f;
        assert (p != 0);
        fFunc.f   = &GSLMultiFitFunctionAdapter<FuncVector >::F;
        fFunc.df  = &GSLMultiFitFunctionAdapter<FuncVector >::Df;
        fFunc.fdf = &GSLMultiFitFunctionAdapter<FuncVector >::FDf;
        fFunc.n = nres;
        fFunc.p = npar;
        fFunc.params =  const_cast<void *>(p);
    }

    gsl_multifit_function_fdf * GetFunc() { return &fFunc; }


private:

    gsl_multifit_function_fdf fFunc;

};



class GSLMultiFit {

public:

   /**
      Default constructor
      No need to specify the type so far since only one solver exists so far
   */
   GSLMultiFit (const gsl_multifit_fdfsolver_type * type = 0) :
      fSolver(0),
      fVec(0),
      fCov(0),
      fType(type)
   {
      if (fType == 0) fType = gsl_multifit_fdfsolver_lmsder; // default value
   }

   /**
      Destructor (no operations)
   */
   ~GSLMultiFit ()  {
      if (fSolver) gsl_multifit_fdfsolver_free(fSolver);
      if (fVec != 0) gsl_vector_free(fVec);
      if (fCov != 0) gsl_matrix_free(fCov);
   }

private:
   // usually copying is non trivial, so we make this unaccessible

   /**
      Copy constructor
   */
   GSLMultiFit(const GSLMultiFit &) {}

   /**
      Assignment operator
   */
   GSLMultiFit & operator = (const GSLMultiFit & rhs)  {
      if (this == &rhs) return *this;  // time saving self-test
      return *this;
   }


public:

   /// create the minimizer from the type and size of number of fitting points and number of parameters
   void CreateSolver(unsigned int npoints, unsigned int npar) {
      if (fSolver) gsl_multifit_fdfsolver_free(fSolver);
      fSolver = gsl_multifit_fdfsolver_alloc(fType, npoints, npar);
   }

   /// set the solver parameters
   template<class Func>
   int Set(const std::vector<Func> & funcVec, const double * x) {
      // create a vector of the fit contributions
      // create function wrapper from an iterator of functions
      unsigned int npts = funcVec.size();
      if (npts == 0) return -1;

      unsigned int npar = funcVec[0].NDim();
      typedef typename std::vector<Func>  FuncVec;
      //FuncIt funcIter = funcVec.begin();
      fFunc.SetFunction(funcVec, npts, npar);
      // create solver object
      CreateSolver( npts, npar );
      // set initial values
      if (fVec != 0) gsl_vector_free(fVec);
      fVec = gsl_vector_alloc( npar );
      std::copy(x,x+npar, fVec->data);
      assert(fSolver != 0);
      return gsl_multifit_fdfsolver_set(fSolver, fFunc.GetFunc(), fVec);
   }

   std::string Name() const {
      if (fSolver == 0) return "undefined";
      return std::string(gsl_multifit_fdfsolver_name(fSolver) );
   }

   int Iterate() {
      if (fSolver == 0) return -1;
      return gsl_multifit_fdfsolver_iterate(fSolver);
   }

   /// parameter values at the minimum
   const double * X() const {
      if (fSolver == 0) return 0;
      gsl_vector * x =  gsl_multifit_fdfsolver_position(fSolver);
      return x->data;
   }

   /// gradient value at the minimum
   const double * Gradient() const {
      if (fSolver == 0) return 0;
      gsl_multifit_gradient(fSolver->J, fSolver->f,fVec);
      return fVec->data;
   }

   /// return covariance matrix of the parameters
   const double * CovarMatrix() const {
      if (fSolver == 0) return 0;
      if (fCov != 0) gsl_matrix_free(fCov);
      unsigned int npar = fSolver->fdf->p;
      fCov = gsl_matrix_alloc( npar, npar );
      static double kEpsrel = 0.0001;
      int ret = gsl_multifit_covar(fSolver->J, kEpsrel, fCov);
      if (ret != GSL_SUCCESS) return 0;
      return fCov->data;
   }

   /// test gradient (ask from solver gradient vector)
   int TestGradient(double absTol) const {
      if (fSolver == 0) return -1;
      Gradient();
      return gsl_multifit_test_gradient( fVec, absTol);
   }

   /// test using abs and relative tolerance
   ///  |dx| < absTol + relTol*|x| for every component
   int TestDelta(double absTol, double relTol) const {
      if (fSolver == 0) return -1;
      return gsl_multifit_test_delta(fSolver->dx, fSolver->x, absTol, relTol);
   }

   // calculate edm  1/2 * ( grad^T * Cov * grad )
   double Edm() const {
      // product C * g
      double edm = -1;
      const double * g = Gradient();
      if (g == 0) return edm;
      const double * c = CovarMatrix();
      if (c == 0) return edm;
      gsl_vector * tmp = gsl_vector_alloc( fSolver->fdf->p );
      int status =   gsl_blas_dgemv(CblasNoTrans, 1.0, fCov, fVec, 0.,tmp);
      if (status == 0) status |= gsl_blas_ddot(fVec, tmp, &edm);
      gsl_vector_free(tmp);
      if (status != 0) return -1;
      // need to divide by 2 ??
      return 0.5*edm;

   }


private:

   GSLMultiFitFunctionWrapper fFunc;
   gsl_multifit_fdfsolver * fSolver;
   // cached vector to avoid re-allocating every time a new one
   mutable gsl_vector * fVec;
   mutable gsl_matrix * fCov;
   const gsl_multifit_fdfsolver_type * fType;

};



//________________________________________________________________________________
/**
    LSResidualFunc class description.
    Internal class used for accessing the residuals of the Least Square function
    and their derivates which are estimated numerically using GSL numerical derivation.
    The class contains a pointer to the fit method function and an index specifying
    the i-th residual and wraps it in a multi-dim gradient function interface
    ROOT::Math::IGradientFunctionMultiDim.
    The class is used by ROOT::Math::GSLNLSMinimizer (GSL non linear least square fitter)

    @ingroup MultiMin
*/
class LSResidualFunc : public IMultiGradFunction {
public:

   //default ctor (required by CINT)
   LSResidualFunc() : fIndex(0), fChi2(0)
   {}


   LSResidualFunc(const ROOT::Math::FitMethodFunction & func, unsigned int i) :
      fIndex(i),
      fChi2(&func),
      fX2(std::vector<double>(func.NDim() ) )
   {}


   // copy ctor
   LSResidualFunc(const LSResidualFunc & rhs) :
      IMultiGenFunction(),
      IMultiGradFunction()
   {
      operator=(rhs);
   }

   // assignment
   LSResidualFunc & operator= (const LSResidualFunc & rhs)
   {
      fIndex = rhs.fIndex;
      fChi2 = rhs.fChi2;
      fX2 = rhs.fX2;
      return *this;
   }

   IMultiGenFunction * Clone() const {
      return new LSResidualFunc(*fChi2,fIndex);
   }

   unsigned int NDim() const { return fChi2->NDim(); }

   void Gradient( const double * x, double * g) const {
      double f0 = 0;
      FdF(x,f0,g);
   }

   void FdF (const double * x, double & f, double * g) const {
       std::cout << "LSResidual::Fdf " << std::endl;
//      unsigned int n = NDim();
//      std::copy(x,x+n,fX2.begin());
//      const double kEps = 1.0E-4;
      f = DoEval(x);
//      for (unsigned int i = 0; i < n; ++i) {
//         fX2[i] += kEps;
//         g[i] =  ( DoEval(&fX2.front()) - f )/kEps;
//         fX2[i] = x[i];
//      }
       fChi2->DataElement(x, fIndex, g);
   }


private:

   double DoEval (const double * x) const {
       std::cout << "LSResidual::DoEval " << std::endl;
      return fChi2->DataElement(x, fIndex);
   }

   double DoDerivative(const double * x, unsigned int icoord) const {
       std::cout << " LSResidual::DoDerivative:" << std::endl;
       throw 1;
      //return  ROOT::Math::Derivator::Eval(*this, x, icoord, 1E-8);
      std::copy(x,x+NDim(),fX2.begin());
      const double kEps = 1.0E-4;
      fX2[icoord] += kEps;
      return ( DoEval(&fX2.front()) - DoEval(x) )/kEps;
   }

   unsigned int fIndex;
   const ROOT::Math::FitMethodFunction * fChi2;
   mutable std::vector<double> fX2;  // cached vector
};


//_____________________________________________________________________________________________________
/**
   GSLNLSMinimizer class for Non Linear Least Square fitting
   It Uses the Levemberg-Marquardt algorithm from
   <A HREF="http://www.gnu.org/software/gsl/manual/html_node/Nonlinear-Least_002dSquares-Fitting.html">
   GSL Non Linear Least Square fitting</A>.

   @ingroup MultiMin
*/
class GSLNLSMinimizer : public  ROOT::Math::Minimizer {

public:

   /**
      Default constructor
   */
   GSLNLSMinimizer (int type = 0);

   /**
      Destructor (no operations)
   */
   ~GSLNLSMinimizer ();

private:
   // usually copying is non trivial, so we make this unaccessible

   /**
      Copy constructor
   */
   GSLNLSMinimizer(const GSLNLSMinimizer &) : ROOT::Math::Minimizer() {}

   /**
      Assignment operator
   */
   GSLNLSMinimizer & operator = (const GSLNLSMinimizer & rhs)  {
      if (this == &rhs) return *this;  // time saving self-test
      return *this;
   }

public:

   /// set the function to minimize
   virtual void SetFunction(const ROOT::Math::IMultiGenFunction & func);

   /// set gradient the function to minimize
   virtual void SetFunction(const ROOT::Math::IMultiGradFunction & func);

   /// set free variable
   virtual bool SetVariable(unsigned int ivar, const std::string & name, double val, double step);

   /// set lower limited variable
   virtual bool SetLowerLimitedVariable(unsigned int  ivar , const std::string & name , double val , double step , double lower );
   /// set upper limited variable
   virtual bool SetUpperLimitedVariable(unsigned int ivar , const std::string & name , double val , double step , double upper );
   /// set upper/lower limited variable
   virtual bool SetLimitedVariable(unsigned int ivar , const std::string & name , double val , double step , double lower , double upper );
   /// set fixed variable
   virtual bool SetFixedVariable(unsigned int ivar , const std::string & name , double val );

   /// set the value of an existing variable
   virtual bool SetVariableValue(unsigned int ivar, double val );
   /// set the values of all existing variables (array must be dimensioned to the size of existing parameters)
   virtual bool SetVariableValues(const double * x);

   /// method to perform the minimization
   virtual  bool Minimize();

   /// return minimum function value
   virtual double MinValue() const { return fMinVal; }

   /// return expected distance reached from the minimum
   virtual double Edm() const { return fEdm; } // not impl. }

   /// return  pointer to X values at the minimum
   virtual const double *  X() const { return &fValues.front(); }

   /// return pointer to gradient values at the minimum
   virtual const double *  MinGradient() const;

   /// number of function calls to reach the minimum
   virtual unsigned int NCalls() const { return (fObjFunc) ? fObjFunc->NCalls() : 0; }

   /// this is <= Function().NDim() which is the total
   /// number of variables (free+ constrained ones)
   virtual unsigned int NDim() const { return fDim; }

   /// number of free variables (real dimension of the problem)
   /// this is <= Function().NDim() which is the total
   virtual unsigned int NFree() const { return fNFree; }

   /// minimizer provides error and error matrix
   virtual bool ProvidesError() const { return true; }

   /// return errors at the minimum
   virtual const double * Errors() const { return (fErrors.size() > 0) ? &fErrors.front() : 0; }
//  {
//       static std::vector<double> err;
//       err.resize(fDim);
//       return &err.front();
//    }

   /** return covariance matrices elements
       if the variable is fixed the matrix is zero
       The ordering of the variables is the same as in errors
   */
   virtual double CovMatrix(unsigned int , unsigned int ) const;

   /// return covariance matrix status
   virtual int CovMatrixStatus() const;

protected:

private:


   unsigned int fDim;        // dimension of the function to be minimized
   unsigned int fNFree;      // dimension of the internal function to be minimized
   unsigned int fSize;        // number of fit points (residuals)


   //ROOT::Math::GSLMultiFit * fGSLMultiFit;        // pointer to GSL multi fit solver
   GSLMultiFit * fGSLMultiFit;        // pointer to GSL multi fit solver
   const ROOT::Math::FitMethodFunction * fObjFunc;      // pointer to Least square function

   double fMinVal;                                // minimum function value
   double fEdm;                                   // edm value
   double fLSTolerance;                           // Line Search Tolerance
   std::vector<double> fValues;
   std::vector<double> fErrors;
   std::vector<double> fCovMatrix;              //  cov matrix (stored as cov[ i * dim + j]
   std::vector<double> fSteps;
   std::vector<std::string> fNames;
   std::vector<LSResidualFunc> fResiduals;   //! transient Vector of the residual functions

   std::vector<ROOT::Math::EMinimVariableType> fVarTypes;  // vector specifyng the type of variables
   std::map< unsigned int, std::pair<double, double> > fBounds; // map specifying the bound using as key the parameter index


};

   } // end namespace Patch

} // end namespace ROOT


#endif // ROOTGSLNLSMINIMIZER_H
