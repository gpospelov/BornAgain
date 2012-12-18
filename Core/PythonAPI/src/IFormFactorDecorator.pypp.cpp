// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "BasicVector3D.h"
#include "Experiment.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "GISASExperiment.h"
#include "HomogeneousMaterial.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "Crystal.h"
#include "ParticleDecoration.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "ParticleInfo.h"
#include "DiffuseParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Transform3D.h"
#include "Units.h"
#include "Types.h"
#include "IFormFactorDecorator.pypp.h"

namespace bp = boost::python;

struct IFormFactorDecorator_wrapper : IFormFactorDecorator, bp::wrapper< IFormFactorDecorator > {

    virtual ::IFormFactorDecorator * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual double getHeight(  ) const  {
        if( bp::override func_getHeight = this->get_override( "getHeight" ) )
            return func_getHeight(  );
        else{
            return this->IFormFactorDecorator::getHeight(  );
        }
    }
    
    double default_getHeight(  ) const  {
        return IFormFactorDecorator::getHeight( );
    }

    virtual double getRadius(  ) const  {
        if( bp::override func_getRadius = this->get_override( "getRadius" ) )
            return func_getRadius(  );
        else{
            return this->IFormFactorDecorator::getRadius(  );
        }
    }
    
    double default_getRadius(  ) const  {
        return IFormFactorDecorator::getRadius( );
    }

    virtual double getVolume(  ) const  {
        if( bp::override func_getVolume = this->get_override( "getVolume" ) )
            return func_getVolume(  );
        else{
            return this->IFormFactorDecorator::getVolume(  );
        }
    }
    
    double default_getVolume(  ) const  {
        return IFormFactorDecorator::getVolume( );
    }

    virtual void setAmbientRefractiveIndex( ::complex_t refractive_index ) {
        if( bp::override func_setAmbientRefractiveIndex = this->get_override( "setAmbientRefractiveIndex" ) )
            func_setAmbientRefractiveIndex( refractive_index );
        else{
            this->IFormFactorDecorator::setAmbientRefractiveIndex( refractive_index );
        }
    }
    
    void default_setAmbientRefractiveIndex( ::complex_t refractive_index ) {
        IFormFactorDecorator::setAmbientRefractiveIndex( refractive_index );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void createDistributedFormFactors( ::std::vector< IFormFactor* > & form_factors, ::std::vector< double > & probabilities, ::size_t nbr_samples ) const  {
        if( bp::override func_createDistributedFormFactors = this->get_override( "createDistributedFormFactors" ) )
            func_createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
        else{
            this->IFormFactor::createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
        }
    }
    
    void default_createDistributedFormFactors( ::std::vector< IFormFactor* > & form_factors, ::std::vector< double > & probabilities, ::size_t nbr_samples ) const  {
        IFormFactor::createDistributedFormFactors( boost::ref(form_factors), boost::ref(probabilities), nbr_samples );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::complex_t evaluate( ::cvector_t const & k_i, ::Bin1DCVector const & k_f_bin, double alpha_i, double alpha_f ) const {
        bp::override func_evaluate = this->get_override( "evaluate" );
        return func_evaluate( boost::ref(k_i), boost::ref(k_f_bin), alpha_i, alpha_f );
    }

    virtual int getNumberOfStochasticParameters(  ) const  {
        if( bp::override func_getNumberOfStochasticParameters = this->get_override( "getNumberOfStochasticParameters" ) )
            return func_getNumberOfStochasticParameters(  );
        else{
            return this->IFormFactor::getNumberOfStochasticParameters(  );
        }
    }
    
    int default_getNumberOfStochasticParameters(  ) const  {
        return IFormFactor::getNumberOfStochasticParameters( );
    }

    virtual bool isDistributedFormFactor(  ) const  {
        if( bp::override func_isDistributedFormFactor = this->get_override( "isDistributedFormFactor" ) )
            return func_isDistributedFormFactor(  );
        else{
            return this->IFormFactor::isDistributedFormFactor(  );
        }
    }
    
    bool default_isDistributedFormFactor(  ) const  {
        return IFormFactor::isDistributedFormFactor( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void print_structure(  ) {
        if( bp::override func_print_structure = this->get_override( "print_structure" ) )
            func_print_structure(  );
        else{
            this->ISample::print_structure(  );
        }
    }
    
    void default_print_structure(  ) {
        ISample::print_structure( );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_IFormFactorDecorator_class(){

    bp::class_< IFormFactorDecorator_wrapper, bp::bases< IFormFactor >, boost::noncopyable >( "IFormFactorDecorator", bp::no_init )    
        .def( 
            "clone"
            , bp::pure_virtual( (::IFormFactorDecorator * ( ::IFormFactorDecorator::* )(  ) const)(&::IFormFactorDecorator::clone) )
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "getHeight"
            , (double ( ::IFormFactorDecorator::* )(  ) const)(&::IFormFactorDecorator::getHeight)
            , (double ( IFormFactorDecorator_wrapper::* )(  ) const)(&IFormFactorDecorator_wrapper::default_getHeight) )    
        .def( 
            "getRadius"
            , (double ( ::IFormFactorDecorator::* )(  ) const)(&::IFormFactorDecorator::getRadius)
            , (double ( IFormFactorDecorator_wrapper::* )(  ) const)(&IFormFactorDecorator_wrapper::default_getRadius) )    
        .def( 
            "getVolume"
            , (double ( ::IFormFactorDecorator::* )(  ) const)(&::IFormFactorDecorator::getVolume)
            , (double ( IFormFactorDecorator_wrapper::* )(  ) const)(&IFormFactorDecorator_wrapper::default_getVolume) )    
        .def( 
            "setAmbientRefractiveIndex"
            , (void ( ::IFormFactorDecorator::* )( ::complex_t ) )(&::IFormFactorDecorator::setAmbientRefractiveIndex)
            , (void ( IFormFactorDecorator_wrapper::* )( ::complex_t ) )(&IFormFactorDecorator_wrapper::default_setAmbientRefractiveIndex)
            , ( bp::arg("refractive_index") ) )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( IFormFactorDecorator_wrapper::* )(  ) )(&IFormFactorDecorator_wrapper::default_areParametersChanged) )    
        .def( 
            "createDistributedFormFactors"
            , (void ( ::IFormFactor::* )( ::std::vector< IFormFactor* > &,::std::vector< double > &,::size_t ) const)(&::IFormFactor::createDistributedFormFactors)
            , (void ( IFormFactorDecorator_wrapper::* )( ::std::vector< IFormFactor* > &,::std::vector< double > &,::size_t ) const)(&IFormFactorDecorator_wrapper::default_createDistributedFormFactors)
            , ( bp::arg("form_factors"), bp::arg("probabilities"), bp::arg("nbr_samples") )
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( IFormFactorDecorator_wrapper::* )(  ) const)(&IFormFactorDecorator_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "evaluate"
            , bp::pure_virtual( (::complex_t ( ::IFormFactor::* )( ::cvector_t const &,::Bin1DCVector const &,double,double ) const)(&::IFormFactor::evaluate) )
            , ( bp::arg("k_i"), bp::arg("k_f_bin"), bp::arg("alpha_i"), bp::arg("alpha_f") ) )    
        .def( 
            "getNumberOfStochasticParameters"
            , (int ( ::IFormFactor::* )(  ) const)(&::IFormFactor::getNumberOfStochasticParameters)
            , (int ( IFormFactorDecorator_wrapper::* )(  ) const)(&IFormFactorDecorator_wrapper::default_getNumberOfStochasticParameters) )    
        .def( 
            "isDistributedFormFactor"
            , (bool ( ::IFormFactor::* )(  ) const)(&::IFormFactor::isDistributedFormFactor)
            , (bool ( IFormFactorDecorator_wrapper::* )(  ) const)(&IFormFactorDecorator_wrapper::default_isDistributedFormFactor) )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( IFormFactorDecorator_wrapper::* )(  ) const)(&IFormFactorDecorator_wrapper::default_printParameters) )    
        .def( 
            "print_structure"
            , (void ( ::ISample::* )(  ) )(&::ISample::print_structure)
            , (void ( IFormFactorDecorator_wrapper::* )(  ) )(&IFormFactorDecorator_wrapper::default_print_structure) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( IFormFactorDecorator_wrapper::* )(  ) )(&IFormFactorDecorator_wrapper::default_setParametersAreChanged) );

}
