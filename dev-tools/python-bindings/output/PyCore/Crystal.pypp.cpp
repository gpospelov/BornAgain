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
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "Crystal.pypp.h"

namespace bp = boost::python;

struct Crystal_wrapper : Crystal, bp::wrapper< Crystal > {

    Crystal_wrapper(::ParticleComposition const & lattice_basis, ::Lattice const & lattice )
    : Crystal( boost::ref(lattice_basis), boost::ref(lattice) )
      , bp::wrapper< Crystal >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::Crystal * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->Crystal::clone(  );
        }
    }
    
    ::Crystal * default_clone(  ) const  {
        return Crystal::clone( );
    }

    virtual ::Crystal * cloneInvertB(  ) const  {
        if( bp::override func_cloneInvertB = this->get_override( "cloneInvertB" ) )
            return func_cloneInvertB(  );
        else{
            return this->Crystal::cloneInvertB(  );
        }
    }
    
    ::Crystal * default_cloneInvertB(  ) const  {
        return Crystal::cloneInvertB( );
    }

    virtual ::IMaterial const * getAmbientMaterial(  ) const  {
        if( bp::override func_getAmbientMaterial = this->get_override( "getAmbientMaterial" ) )
            return func_getAmbientMaterial(  );
        else{
            return this->Crystal::getAmbientMaterial(  );
        }
    }
    
    ::IMaterial const * default_getAmbientMaterial(  ) const  {
        return Crystal::getAmbientMaterial( );
    }

    virtual void setAmbientMaterial( ::IMaterial const & material ) {
        if( bp::override func_setAmbientMaterial = this->get_override( "setAmbientMaterial" ) )
            func_setAmbientMaterial( boost::ref(material) );
        else{
            this->Crystal::setAmbientMaterial( boost::ref(material) );
        }
    }
    
    void default_setAmbientMaterial( ::IMaterial const & material ) {
        Crystal::setAmbientMaterial( boost::ref(material) );
    }

    virtual void applyRotation( ::IRotation const & rotation ) {
        if( bp::override func_applyRotation = this->get_override( "applyRotation" ) )
            func_applyRotation( boost::ref(rotation) );
        else{
            this->IClusteredParticles::applyRotation( boost::ref(rotation) );
        }
    }
    
    void default_applyRotation( ::IRotation const & rotation ) {
        IClusteredParticles::applyRotation( boost::ref(rotation) );
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

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual bool containsMagneticMaterial(  ) const  {
        if( bp::override func_containsMagneticMaterial = this->get_override( "containsMagneticMaterial" ) )
            return func_containsMagneticMaterial(  );
        else{
            return this->ISample::containsMagneticMaterial(  );
        }
    }
    
    bool default_containsMagneticMaterial(  ) const  {
        return ISample::containsMagneticMaterial( );
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

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
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

    virtual void printSampleTree(  ) {
        if( bp::override func_printSampleTree = this->get_override( "printSampleTree" ) )
            func_printSampleTree(  );
        else{
            this->ISample::printSampleTree(  );
        }
    }
    
    void default_printSampleTree(  ) {
        ISample::printSampleTree( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer, ::AttLimits const & limits=AttLimits::limitless( ) ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer, limits );
        }
        else{
            IParameterized::registerParameter( name, parpointer, boost::ref(limits) );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer, ::AttLimits const & limits=AttLimits::limitless( ) ){
        if( dynamic_cast< Crystal_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
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

    virtual ::std::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::std::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

    virtual void transferToCPP(  ) {
        
        if( !this->m_pyobj) {
            this->m_pyobj = boost::python::detail::wrapper_base_::get_owner(*this);
            Py_INCREF(this->m_pyobj);
        }
        
        if( bp::override func_transferToCPP = this->get_override( "transferToCPP" ) )
            func_transferToCPP(  );
        else{
            this->ICloneable::transferToCPP(  );
        }
    }
    
    void default_transferToCPP(  ) {
        
        if( !this->m_pyobj) {
            this->m_pyobj = boost::python::detail::wrapper_base_::get_owner(*this);
            Py_INCREF(this->m_pyobj);
        }
        
        ICloneable::transferToCPP( );
    }

    PyObject* m_pyobj;

};

void register_Crystal_class(){

    { //::Crystal
        typedef bp::class_< Crystal_wrapper, bp::bases< IClusteredParticles >, std::auto_ptr< Crystal_wrapper >, boost::noncopyable > Crystal_exposer_t;
        Crystal_exposer_t Crystal_exposer = Crystal_exposer_t( "Crystal", "A crystal structure with a form factor as a basis.", bp::init< ParticleComposition const &, Lattice const & >(( bp::arg("lattice_basis"), bp::arg("lattice") )) );
        bp::scope Crystal_scope( Crystal_exposer );
        { //::Crystal::clone
        
            typedef ::Crystal * ( ::Crystal::*clone_function_type)(  ) const;
            typedef ::Crystal * ( Crystal_wrapper::*default_clone_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "clone"
                , clone_function_type(&::Crystal::clone)
                , default_clone_function_type(&Crystal_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::Crystal::cloneInvertB
        
            typedef ::Crystal * ( ::Crystal::*cloneInvertB_function_type)(  ) const;
            typedef ::Crystal * ( Crystal_wrapper::*default_cloneInvertB_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "cloneInvertB"
                , cloneInvertB_function_type(&::Crystal::cloneInvertB)
                , default_cloneInvertB_function_type(&Crystal_wrapper::default_cloneInvertB)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Crystal::getAmbientMaterial
        
            typedef ::IMaterial const * ( ::Crystal::*getAmbientMaterial_function_type)(  ) const;
            typedef ::IMaterial const * ( Crystal_wrapper::*default_getAmbientMaterial_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "getAmbientMaterial"
                , getAmbientMaterial_function_type(&::Crystal::getAmbientMaterial)
                , default_getAmbientMaterial_function_type(&Crystal_wrapper::default_getAmbientMaterial)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Crystal::getLatticeBasis
        
            typedef ::ParticleComposition const * ( ::Crystal::*getLatticeBasis_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "getLatticeBasis"
                , getLatticeBasis_function_type( &::Crystal::getLatticeBasis )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Crystal::setAmbientMaterial
        
            typedef void ( ::Crystal::*setAmbientMaterial_function_type)( ::IMaterial const & ) ;
            typedef void ( Crystal_wrapper::*default_setAmbientMaterial_function_type)( ::IMaterial const & ) ;
            
            Crystal_exposer.def( 
                "setAmbientMaterial"
                , setAmbientMaterial_function_type(&::Crystal::setAmbientMaterial)
                , default_setAmbientMaterial_function_type(&Crystal_wrapper::default_setAmbientMaterial)
                , ( bp::arg("material") ) );
        
        }
        { //::Crystal::setDWFactor
        
            typedef void ( ::Crystal::*setDWFactor_function_type)( double ) ;
            
            Crystal_exposer.def( 
                "setDWFactor"
                , setDWFactor_function_type( &::Crystal::setDWFactor )
                , ( bp::arg("dw_factor") ) );
        
        }
        { //::IClusteredParticles::applyRotation
        
            typedef void ( ::IClusteredParticles::*applyRotation_function_type)( ::IRotation const & ) ;
            typedef void ( Crystal_wrapper::*default_applyRotation_function_type)( ::IRotation const & ) ;
            
            Crystal_exposer.def( 
                "applyRotation"
                , applyRotation_function_type(&::IClusteredParticles::applyRotation)
                , default_applyRotation_function_type(&Crystal_wrapper::default_applyRotation)
                , ( bp::arg("rotation") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( Crystal_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            Crystal_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&Crystal_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( Crystal_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            Crystal_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&Crystal_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type)(  ) const;
            typedef bool ( Crystal_wrapper::*default_containsMagneticMaterial_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&Crystal_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( Crystal_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&Crystal_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ICompositeSample::*getCompositeSample_function_type)(  ) ;
            typedef ::ICompositeSample * ( Crystal_wrapper::*default_getCompositeSample_function_type)(  ) ;
            
            Crystal_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&Crystal_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ICompositeSample::*getCompositeSample_function_type)(  ) const;
            typedef ::ICompositeSample const * ( Crystal_wrapper::*default_getCompositeSample_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&Crystal_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( Crystal_wrapper::*default_printParameters_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&Crystal_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type)(  ) ;
            typedef void ( Crystal_wrapper::*default_printSampleTree_function_type)(  ) ;
            
            Crystal_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&Crystal_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int,::AttLimits const & );
            
            Crystal_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &Crystal_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer"), bp::arg("limits")=AttLimits::limitless( ) )
                , "main method to register data address in the pool." );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( Crystal_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            Crystal_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&Crystal_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( Crystal_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            Crystal_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&Crystal_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICompositeSample::size
        
            typedef ::std::size_t ( ::ICompositeSample::*size_function_type)(  ) const;
            typedef ::std::size_t ( Crystal_wrapper::*default_size_function_type)(  ) const;
            
            Crystal_exposer.def( 
                "size"
                , size_function_type(&::ICompositeSample::size)
                , default_size_function_type(&Crystal_wrapper::default_size) );
        
        }
        { //::ICloneable::transferToCPP
        
            typedef void ( ::ICloneable::*transferToCPP_function_type)(  ) ;
            typedef void ( Crystal_wrapper::*default_transferToCPP_function_type)(  ) ;
            
            Crystal_exposer.def( 
                "transferToCPP"
                , transferToCPP_function_type(&::ICloneable::transferToCPP)
                , default_transferToCPP_function_type(&Crystal_wrapper::default_transferToCPP) );
        
        }
    }

}
