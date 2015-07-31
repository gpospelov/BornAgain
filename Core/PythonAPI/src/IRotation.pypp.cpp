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
#include "IRotation.pypp.h"

namespace bp = boost::python;

struct IRotation_wrapper : IRotation, bp::wrapper< IRotation > {

    IRotation_wrapper()
    : IRotation()
      , bp::wrapper< IRotation >(){
        // null constructor
        m_pyobj = 0;
    }

    virtual ::IRotation * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual ::IRotation * cloneInvertB(  ) const {
        bp::override func_cloneInvertB = this->get_override( "cloneInvertB" );
        return func_cloneInvertB(  );
    }

    virtual ::IRotation * createInverse(  ) const {
        bp::override func_createInverse = this->get_override( "createInverse" );
        return func_createInverse(  );
    }

    virtual ::Geometry::Transform3D getTransform3D(  ) const {
        bp::override func_getTransform3D = this->get_override( "getTransform3D" );
        return func_getTransform3D(  );
    }

    virtual bool isIdentity(  ) const  {
        if( bp::override func_isIdentity = this->get_override( "isIdentity" ) )
            return func_isIdentity(  );
        else{
            return this->IRotation::isIdentity(  );
        }
    }
    
    bool default_isIdentity(  ) const  {
        return IRotation::isIdentity( );
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
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ISample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ISample::getCompositeSample( );
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
        if( dynamic_cast< IRotation_wrapper * >( boost::addressof( inst ) ) ){
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

void register_IRotation_class(){

    { //::IRotation
        typedef bp::class_< IRotation_wrapper, bp::bases< ISample >, std::auto_ptr< IRotation_wrapper >, boost::noncopyable > IRotation_exposer_t;
        IRotation_exposer_t IRotation_exposer = IRotation_exposer_t( "IRotation", "An interface for classes representing a rotatio." );
        bp::scope IRotation_scope( IRotation_exposer );
        { //::IRotation::clone
        
            typedef ::IRotation * ( ::IRotation::*clone_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "clone"
                , bp::pure_virtual( clone_function_type(&::IRotation::clone) )
                , bp::return_value_policy< bp::manage_new_object >()
                , "Returns a clone." );
        
        }
        { //::IRotation::cloneInvertB
        
            typedef ::IRotation * ( ::IRotation::*cloneInvertB_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "cloneInvertB"
                , bp::pure_virtual( cloneInvertB_function_type(&::IRotation::cloneInvertB) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "Returns a clone with inverted magnetic fields." );
        
        }
        { //::IRotation::createInverse
        
            typedef ::IRotation * ( ::IRotation::*createInverse_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "createInverse"
                , bp::pure_virtual( createInverse_function_type(&::IRotation::createInverse) )
                , bp::return_value_policy< bp::manage_new_object >()
                , "Returns a new IRotation object that is the current object's inverse." );
        
        }
        { //::IRotation::createRotation
        
            typedef ::IRotation * ( *createRotation_function_type )( ::Geometry::Transform3D const & );
            
            IRotation_exposer.def( 
                "createRotation"
                , createRotation_function_type( &::IRotation::createRotation )
                , ( bp::arg("transform") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IRotation::getTransform3D
        
            typedef ::Geometry::Transform3D ( ::IRotation::*getTransform3D_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "getTransform3D"
                , bp::pure_virtual( getTransform3D_function_type(&::IRotation::getTransform3D) )
                , "Returns transformation." );
        
        }
        { //::IRotation::isIdentity
        
            typedef bool ( ::IRotation::*isIdentity_function_type)(  ) const;
            typedef bool ( IRotation_wrapper::*default_isIdentity_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "isIdentity"
                , isIdentity_function_type(&::IRotation::isIdentity)
                , default_isIdentity_function_type(&IRotation_wrapper::default_isIdentity) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( IRotation_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            IRotation_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&IRotation_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( IRotation_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            IRotation_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&IRotation_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type)(  ) const;
            typedef bool ( IRotation_wrapper::*default_containsMagneticMaterial_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&IRotation_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( IRotation_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&IRotation_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ISample::*getCompositeSample_function_type)(  ) ;
            typedef ::ICompositeSample * ( IRotation_wrapper::*default_getCompositeSample_function_type)(  ) ;
            
            IRotation_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&IRotation_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ISample::*getCompositeSample_function_type)(  ) const;
            typedef ::ICompositeSample const * ( IRotation_wrapper::*default_getCompositeSample_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&IRotation_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( IRotation_wrapper::*default_printParameters_function_type)(  ) const;
            
            IRotation_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&IRotation_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type)(  ) ;
            typedef void ( IRotation_wrapper::*default_printSampleTree_function_type)(  ) ;
            
            IRotation_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&IRotation_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int,::AttLimits const & );
            
            IRotation_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &IRotation_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer"), bp::arg("limits")=AttLimits::limitless( ) )
                , "main method to register data address in the pool." );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( IRotation_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            IRotation_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&IRotation_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( IRotation_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            IRotation_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&IRotation_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICloneable::transferToCPP
        
            typedef void ( ::ICloneable::*transferToCPP_function_type)(  ) ;
            typedef void ( IRotation_wrapper::*default_transferToCPP_function_type)(  ) ;
            
            IRotation_exposer.def( 
                "transferToCPP"
                , transferToCPP_function_type(&::ICloneable::transferToCPP)
                , default_transferToCPP_function_type(&IRotation_wrapper::default_transferToCPP) );
        
        }
        IRotation_exposer.staticmethod( "createRotation" );
    }

}
