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
#include "IParticle.pypp.h"

namespace bp = boost::python;

struct IParticle_wrapper : IParticle, bp::wrapper< IParticle > {

    virtual ::IParticle * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual ::IParticle * cloneInvertB(  ) const {
        bp::override func_cloneInvertB = this->get_override( "cloneInvertB" );
        return func_cloneInvertB(  );
    }

    virtual ::IFormFactor * createTransformedFormFactor( ::complex_t wavevector_scattering_factor, ::IRotation const * p_rotation, ::kvector_t translation ) const {
        bp::override func_createTransformedFormFactor = this->get_override( "createTransformedFormFactor" );
        return func_createTransformedFormFactor( wavevector_scattering_factor, boost::python::ptr(p_rotation), translation );
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

    virtual ::IMaterial const * getAmbientMaterial(  ) const {
        bp::override func_getAmbientMaterial = this->get_override( "getAmbientMaterial" );
        return func_getAmbientMaterial(  );
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
        if( dynamic_cast< IParticle_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
        }
    }

    virtual void setAmbientMaterial( ::IMaterial const & material ) {
        if( bp::override func_setAmbientMaterial = this->get_override( "setAmbientMaterial" ) )
            func_setAmbientMaterial( boost::ref(material) );
        else{
            this->IAbstractParticle::setAmbientMaterial( boost::ref(material) );
        }
    }
    
    void default_setAmbientMaterial( ::IMaterial const & material ) {
        IAbstractParticle::setAmbientMaterial( boost::ref(material) );
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

void register_IParticle_class(){

    { //::IParticle
        typedef bp::class_< IParticle_wrapper, bp::bases< IAbstractParticle >, std::auto_ptr< IParticle_wrapper >, boost::noncopyable > IParticle_exposer_t;
        IParticle_exposer_t IParticle_exposer = IParticle_exposer_t( "IParticle", "Interface for a real particle (one that has position/rotation and form factor.", bp::no_init );
        bp::scope IParticle_scope( IParticle_exposer );
        { //::IParticle::applyRotation
        
            typedef void ( ::IParticle::*applyRotation_function_type)( ::IRotation const & ) ;
            
            IParticle_exposer.def( 
                "applyRotation"
                , applyRotation_function_type( &::IParticle::applyRotation )
                , ( bp::arg("rotation") )
                , "Applies transformation by composing it with the existing one." );
        
        }
        { //::IParticle::applyTranslation
        
            typedef void ( ::IParticle::*applyTranslation_function_type)( ::kvector_t ) ;
            
            IParticle_exposer.def( 
                "applyTranslation"
                , applyTranslation_function_type( &::IParticle::applyTranslation )
                , ( bp::arg("displacement") )
                , "Applies extra translation by adding it to the current one." );
        
        }
        { //::IParticle::clone
        
            typedef ::IParticle * ( ::IParticle::*clone_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "clone"
                , bp::pure_virtual( clone_function_type(&::IParticle::clone) )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParticle::cloneInvertB
        
            typedef ::IParticle * ( ::IParticle::*cloneInvertB_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "cloneInvertB"
                , bp::pure_virtual( cloneInvertB_function_type(&::IParticle::cloneInvertB) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "Returns a clone with inverted magnetic fields." );
        
        }
        { //::IParticle::createFormFactor
        
            typedef ::IFormFactor * ( ::IParticle::*createFormFactor_function_type)( ::complex_t ) const;
            
            IParticle_exposer.def( 
                "createFormFactor"
                , createFormFactor_function_type( &::IParticle::createFormFactor )
                , ( bp::arg("wavevector_scattering_factor") )
                , bp::return_value_policy< bp::manage_new_object >()
                , "Create a form factor for this particle with an extra scattering factor." );
        
        }
        { //::IParticle::createTransformedFormFactor
        
            typedef ::IFormFactor * ( ::IParticle::*createTransformedFormFactor_function_type)( ::complex_t,::IRotation const *,::kvector_t ) const;
            
            IParticle_exposer.def( 
                "createTransformedFormFactor"
                , bp::pure_virtual( createTransformedFormFactor_function_type(&::IParticle::createTransformedFormFactor) )
                , ( bp::arg("wavevector_scattering_factor"), bp::arg("p_rotation"), bp::arg("translation") )
                , bp::return_value_policy< bp::manage_new_object >()
                , "Create a form factor for this particle with an extra scattering factor." );
        
        }
        { //::IParticle::getPosition
        
            typedef ::kvector_t ( ::IParticle::*getPosition_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "getPosition"
                , getPosition_function_type( &::IParticle::getPosition )
                , "Returns particle position." );
        
        }
        { //::IParticle::getRotation
        
            typedef ::IRotation const * ( ::IParticle::*getRotation_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "getRotation"
                , getRotation_function_type( &::IParticle::getRotation )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "Returns rotation object." );
        
        }
        { //::IParticle::setPosition
        
            typedef void ( ::IParticle::*setPosition_function_type)( ::kvector_t ) ;
            
            IParticle_exposer.def( 
                "setPosition"
                , setPosition_function_type( &::IParticle::setPosition )
                , ( bp::arg("position") )
                , "Sets particle position." );
        
        }
        { //::IParticle::setPosition
        
            typedef void ( ::IParticle::*setPosition_function_type)( double,double,double ) ;
            
            IParticle_exposer.def( 
                "setPosition"
                , setPosition_function_type( &::IParticle::setPosition )
                , ( bp::arg("x"), bp::arg("y"), bp::arg("z") )
                , "Sets particle position." );
        
        }
        { //::IParticle::setRotation
        
            typedef void ( ::IParticle::*setRotation_function_type)( ::IRotation const & ) ;
            
            IParticle_exposer.def( 
                "setRotation"
                , setRotation_function_type( &::IParticle::setRotation )
                , ( bp::arg("rotation") )
                , "Sets transformation." );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( IParticle_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            IParticle_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&IParticle_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( IParticle_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            IParticle_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&IParticle_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type)(  ) const;
            typedef bool ( IParticle_wrapper::*default_containsMagneticMaterial_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&IParticle_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( IParticle_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&IParticle_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IAbstractParticle::getAmbientMaterial
        
            typedef ::IMaterial const * ( ::IAbstractParticle::*getAmbientMaterial_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "getAmbientMaterial"
                , bp::pure_virtual( getAmbientMaterial_function_type(&::IAbstractParticle::getAmbientMaterial) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "Returns particle's material." );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ICompositeSample::*getCompositeSample_function_type)(  ) ;
            typedef ::ICompositeSample * ( IParticle_wrapper::*default_getCompositeSample_function_type)(  ) ;
            
            IParticle_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&IParticle_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ICompositeSample::*getCompositeSample_function_type)(  ) const;
            typedef ::ICompositeSample const * ( IParticle_wrapper::*default_getCompositeSample_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&IParticle_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( IParticle_wrapper::*default_printParameters_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&IParticle_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type)(  ) ;
            typedef void ( IParticle_wrapper::*default_printSampleTree_function_type)(  ) ;
            
            IParticle_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&IParticle_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int,::AttLimits const & );
            
            IParticle_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &IParticle_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer"), bp::arg("limits")=AttLimits::limitless( ) )
                , "main method to register data address in the pool." );
        
        }
        { //::IAbstractParticle::setAmbientMaterial
        
            typedef void ( ::IAbstractParticle::*setAmbientMaterial_function_type)( ::IMaterial const & ) ;
            typedef void ( IParticle_wrapper::*default_setAmbientMaterial_function_type)( ::IMaterial const & ) ;
            
            IParticle_exposer.def( 
                "setAmbientMaterial"
                , setAmbientMaterial_function_type(&::IAbstractParticle::setAmbientMaterial)
                , default_setAmbientMaterial_function_type(&IParticle_wrapper::default_setAmbientMaterial)
                , ( bp::arg("material") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( IParticle_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            IParticle_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&IParticle_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( IParticle_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            IParticle_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&IParticle_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICompositeSample::size
        
            typedef ::std::size_t ( ::ICompositeSample::*size_function_type)(  ) const;
            typedef ::std::size_t ( IParticle_wrapper::*default_size_function_type)(  ) const;
            
            IParticle_exposer.def( 
                "size"
                , size_function_type(&::ICompositeSample::size)
                , default_size_function_type(&IParticle_wrapper::default_size) );
        
        }
        { //::ICloneable::transferToCPP
        
            typedef void ( ::ICloneable::*transferToCPP_function_type)(  ) ;
            typedef void ( IParticle_wrapper::*default_transferToCPP_function_type)(  ) ;
            
            IParticle_exposer.def( 
                "transferToCPP"
                , transferToCPP_function_type(&::ICloneable::transferToCPP)
                , default_transferToCPP_function_type(&IParticle_wrapper::default_transferToCPP) );
        
        }
    }

}
