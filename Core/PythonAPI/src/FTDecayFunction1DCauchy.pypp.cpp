// This file has been generated by Py++.

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "PythonCoreList.h"
#include "FTDecayFunction1DCauchy.pypp.h"

namespace bp = boost::python;

struct FTDecayFunction1DCauchy_wrapper : FTDecayFunction1DCauchy, bp::wrapper< FTDecayFunction1DCauchy > {

    FTDecayFunction1DCauchy_wrapper(FTDecayFunction1DCauchy const & arg )
    : FTDecayFunction1DCauchy( arg )
      , bp::wrapper< FTDecayFunction1DCauchy >(){
        // copy constructor
        m_pyobj = 0;
    }

    FTDecayFunction1DCauchy_wrapper(double omega )
    : FTDecayFunction1DCauchy( omega )
      , bp::wrapper< FTDecayFunction1DCauchy >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::FTDecayFunction1DCauchy * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->FTDecayFunction1DCauchy::clone(  );
        }
    }
    
    ::FTDecayFunction1DCauchy * default_clone(  ) const  {
        return FTDecayFunction1DCauchy::clone( );
    }

    virtual double evaluate( double q ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( q );
        else{
            return this->FTDecayFunction1DCauchy::evaluate( q );
        }
    }
    
    double default_evaluate( double q ) const  {
        return FTDecayFunction1DCauchy::evaluate( q );
    }

    PyObject* m_pyobj;

};

void register_FTDecayFunction1DCauchy_class(){

    { //::FTDecayFunction1DCauchy
        typedef bp::class_< FTDecayFunction1DCauchy_wrapper, bp::bases< IFTDecayFunction1D >, std::auto_ptr< FTDecayFunction1DCauchy_wrapper > > FTDecayFunction1DCauchy_exposer_t;
        FTDecayFunction1DCauchy_exposer_t FTDecayFunction1DCauchy_exposer = FTDecayFunction1DCauchy_exposer_t( "FTDecayFunction1DCauchy", "1 dimensional Cauchy decay function in reciprocal space.", bp::init< double >(( bp::arg("omega") )) );
        bp::scope FTDecayFunction1DCauchy_scope( FTDecayFunction1DCauchy_exposer );
        { //::FTDecayFunction1DCauchy::clone
        
            typedef ::FTDecayFunction1DCauchy * ( ::FTDecayFunction1DCauchy::*clone_function_type)(  ) const;
            typedef ::FTDecayFunction1DCauchy * ( FTDecayFunction1DCauchy_wrapper::*default_clone_function_type)(  ) const;
            
            FTDecayFunction1DCauchy_exposer.def( 
                "clone"
                , clone_function_type(&::FTDecayFunction1DCauchy::clone)
                , default_clone_function_type(&FTDecayFunction1DCauchy_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::FTDecayFunction1DCauchy::evaluate
        
            typedef double ( ::FTDecayFunction1DCauchy::*evaluate_function_type)( double ) const;
            typedef double ( FTDecayFunction1DCauchy_wrapper::*default_evaluate_function_type)( double ) const;
            
            FTDecayFunction1DCauchy_exposer.def( 
                "evaluate"
                , evaluate_function_type(&::FTDecayFunction1DCauchy::evaluate)
                , default_evaluate_function_type(&FTDecayFunction1DCauchy_wrapper::default_evaluate)
                , ( bp::arg("q") ) );
        
        }
    }

}
