#include "PythonSamplesInterface.h"
#include "IMaterial.h"
#include "HomogeneousMaterial.h"
#include "ISingleton.h"
#include "MaterialManager.h"
#include "LayerRoughness.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "ParameterPool.h"

#include <boost/python.hpp>
namespace bp = boost::python;

struct Layer_wrapper : Layer, bp::wrapper< Layer > {

    Layer_wrapper( )
    : Layer( )
      , bp::wrapper< Layer >(){
        // null constructor

    }

    Layer_wrapper(::Layer const & other )
    : Layer( boost::ref(other) )
      , bp::wrapper< Layer >(){
        // copy constructor

    }

    virtual ::IMaterial const * getMaterial(  ) const  {
        if( bp::override func_getMaterial = this->get_override( "getMaterial" ) )
            return func_getMaterial(  );
        else{
            return this->Layer::getMaterial(  );
        }
    }

    ::IMaterial const * default_getMaterial(  ) const  {
        return Layer::getMaterial( );
    }

    virtual void setMaterial( ::IMaterial const * p_material ) {
        if( bp::override func_setMaterial = this->get_override( "setMaterial" ) )
            func_setMaterial( boost::python::ptr(p_material) );
        else{
            this->Layer::setMaterial( boost::python::ptr(p_material) );
        }
    }

    void default_setMaterial( ::IMaterial const * p_material ) {
        Layer::setMaterial( boost::python::ptr(p_material) );
    }

    virtual void setMaterial( ::IMaterial const * p_material, double thickness ) {
        if( bp::override func_setMaterial = this->get_override( "setMaterial" ) )
            func_setMaterial( boost::python::ptr(p_material), thickness );
        else{
            this->Layer::setMaterial( boost::python::ptr(p_material), thickness );
        }
    }

    void default_setMaterial( ::IMaterial const * p_material, double thickness ) {
        Layer::setMaterial( boost::python::ptr(p_material), thickness );
    }

};


void PythonInterface::export_samples()
{
    { //::IMaterial
        typedef bp::class_< IMaterial > IMaterial_exposer_t;
        IMaterial_exposer_t IMaterial_exposer = IMaterial_exposer_t( "IMaterial", bp::init< >() );
        bp::scope IMaterial_scope( IMaterial_exposer );
        IMaterial_exposer.def( bp::init< std::string const & >(( bp::arg("name") )) );
        IMaterial_exposer.def( bp::init< IMaterial const & >(( bp::arg("other") )) );
        { //::IMaterial::operator=

            typedef ::IMaterial & ( ::IMaterial::*assign_function_type )( ::IMaterial const & ) ;

            IMaterial_exposer.def(
                "assign"
                , assign_function_type( &::IMaterial::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );

        }
        IMaterial_exposer.def( bp::self_ns::str( bp::self ) );
    }

    { //::HomogeneousMaterial
        typedef bp::class_< HomogeneousMaterial, bp::bases< IMaterial > > HomogeneousMaterial_exposer_t;
        HomogeneousMaterial_exposer_t HomogeneousMaterial_exposer = HomogeneousMaterial_exposer_t( "HomogeneousMaterial", bp::init< >() );
        bp::scope HomogeneousMaterial_scope( HomogeneousMaterial_exposer );
        HomogeneousMaterial_exposer.def( bp::init< complex_t >(( bp::arg("refractive_index") )) );
        HomogeneousMaterial_exposer.def( bp::init< std::string const &, complex_t >(( bp::arg("name"), bp::arg("refractive_index") )) );
        HomogeneousMaterial_exposer.def( bp::init< HomogeneousMaterial const & >(( bp::arg("other") )) );
        { //::HomogeneousMaterial::getRefractiveIndex

            typedef ::complex_t ( ::HomogeneousMaterial::*getRefractiveIndex_function_type )(  ) const;

            HomogeneousMaterial_exposer.def(
                "getRefractiveIndex"
                , getRefractiveIndex_function_type( &::HomogeneousMaterial::getRefractiveIndex ) );

        }
        { //::HomogeneousMaterial::operator=

            typedef ::HomogeneousMaterial & ( ::HomogeneousMaterial::*assign_function_type )( ::HomogeneousMaterial const & ) ;

            HomogeneousMaterial_exposer.def(
                "assign"
                , assign_function_type( &::HomogeneousMaterial::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );

        }
        { //::HomogeneousMaterial::setRefractiveIndex

            typedef void ( ::HomogeneousMaterial::*setRefractiveIndex_function_type )( ::complex_t ) ;

            HomogeneousMaterial_exposer.def(
                "setRefractiveIndex"
                , setRefractiveIndex_function_type( &::HomogeneousMaterial::setRefractiveIndex )
                , ( bp::arg("refractive_index") ) );

        }
    }

    bp::class_< ISingleton< MaterialManager >, boost::noncopyable >( "ISingleton_less__MaterialManager__greater_", bp::no_init )
        .def(
            "instance"
            , (::MaterialManager & (*)(  ))( &::ISingleton< MaterialManager >::instance )
            , bp::return_value_policy< bp::reference_existing_object >() )
        .staticmethod( "instance" );

    { //::Layer
        typedef bp::class_< Layer_wrapper > Layer_exposer_t;
        Layer_exposer_t Layer_exposer = Layer_exposer_t( "Layer", bp::init< >() );
        bp::scope Layer_scope( Layer_exposer );
        Layer_exposer.def( bp::init< Layer const & >(( bp::arg("other") )) );
        { //::Layer::getMaterial

            typedef ::IMaterial const * ( ::Layer::*getMaterial_function_type )(  ) const;
            typedef ::IMaterial const * ( Layer_wrapper::*default_getMaterial_function_type )(  ) const;

            Layer_exposer.def(
                "getMaterial"
                , getMaterial_function_type(&::Layer::getMaterial)
                , default_getMaterial_function_type(&Layer_wrapper::default_getMaterial)
                , bp::return_value_policy< bp::reference_existing_object >() );

        }
        { //::Layer::operator=

            typedef ::Layer & ( ::Layer::*assign_function_type )( ::Layer const & ) ;

            Layer_exposer.def(
                "assign"
                , assign_function_type( &::Layer::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );

        }
        { //::Layer::setMaterial

            typedef void ( ::Layer::*setMaterial_function_type )( ::IMaterial const * ) ;
            typedef void ( Layer_wrapper::*default_setMaterial_function_type )( ::IMaterial const * ) ;

            Layer_exposer.def(
                "setMaterial"
                , setMaterial_function_type(&::Layer::setMaterial)
                , default_setMaterial_function_type(&Layer_wrapper::default_setMaterial)
                , ( bp::arg("p_material") ) );

        }
        { //::Layer::setMaterial

            typedef void ( ::Layer::*setMaterial_function_type )( ::IMaterial const *,double ) ;
            typedef void ( Layer_wrapper::*default_setMaterial_function_type )( ::IMaterial const *,double ) ;

            Layer_exposer.def(
                "setMaterial"
                , setMaterial_function_type(&::Layer::setMaterial)
                , default_setMaterial_function_type(&Layer_wrapper::default_setMaterial)
                , ( bp::arg("p_material"), bp::arg("thickness") ) );

        }
        Layer_exposer.def( bp::self_ns::str( bp::self ) );
    }

    { //::LayerRoughness
        typedef bp::class_< LayerRoughness > LayerRoughness_exposer_t;
        LayerRoughness_exposer_t LayerRoughness_exposer = LayerRoughness_exposer_t( "LayerRoughness", bp::init< >() );
        bp::scope LayerRoughness_scope( LayerRoughness_exposer );
        LayerRoughness_exposer.def( bp::init< double, double, double >(( bp::arg("sigma"), bp::arg("hurstParameter"), bp::arg("latteralCorrLength") )) );
        LayerRoughness_exposer.def( bp::init< LayerRoughness const & >(( bp::arg("other") )) );
        { //::LayerRoughness::getHurstParameter

            typedef double ( ::LayerRoughness::*getHurstParameter_function_type )(  ) const;

            LayerRoughness_exposer.def(
                "getHurstParameter"
                , getHurstParameter_function_type( &::LayerRoughness::getHurstParameter ) );

        }
        { //::LayerRoughness::getLatteralCorrLength

            typedef double ( ::LayerRoughness::*getLatteralCorrLength_function_type )(  ) const;

            LayerRoughness_exposer.def(
                "getLatteralCorrLength"
                , getLatteralCorrLength_function_type( &::LayerRoughness::getLatteralCorrLength ) );

        }
        { //::LayerRoughness::getSigma

            typedef double ( ::LayerRoughness::*getSigma_function_type )(  ) const;

            LayerRoughness_exposer.def(
                "getSigma"
                , getSigma_function_type( &::LayerRoughness::getSigma ) );

        }
        { //::LayerRoughness::operator=

            typedef ::LayerRoughness & ( ::LayerRoughness::*assign_function_type )( ::LayerRoughness const & ) ;

            LayerRoughness_exposer.def(
                "assign"
                , assign_function_type( &::LayerRoughness::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );

        }
        { //::LayerRoughness::setHurstParameter

            typedef void ( ::LayerRoughness::*setHurstParameter_function_type )( double ) ;

            LayerRoughness_exposer.def(
                "setHurstParameter"
                , setHurstParameter_function_type( &::LayerRoughness::setHurstParameter )
                , ( bp::arg("hurstParameter") ) );

        }
        { //::LayerRoughness::setLatteralCorrLength

            typedef void ( ::LayerRoughness::*setLatteralCorrLength_function_type )( double ) ;

            LayerRoughness_exposer.def(
                "setLatteralCorrLength"
                , setLatteralCorrLength_function_type( &::LayerRoughness::setLatteralCorrLength )
                , ( bp::arg("latteralCorrLength") ) );

        }
        { //::LayerRoughness::setSigma

            typedef void ( ::LayerRoughness::*setSigma_function_type )( double ) ;

            LayerRoughness_exposer.def(
                "setSigma"
                , setSigma_function_type( &::LayerRoughness::setSigma )
                , ( bp::arg("sigma") ) );

        }
        LayerRoughness_exposer.def( bp::self_ns::str( bp::self ) );
    }

    bp::class_< MaterialManager, bp::bases< ISingleton< MaterialManager > >, boost::noncopyable >( "MaterialManager", bp::no_init )
        .def(
            "addHomogeneousMaterial"
            , (::IMaterial const * ( ::MaterialManager::* )( ::std::string const &,::complex_t ) )( &::MaterialManager::addHomogeneousMaterial )
            , ( bp::arg("name"), bp::arg("refractive_index") )
            , bp::return_internal_reference< >() )
        .def(
            "clear"
            , (void ( ::MaterialManager::* )(  ) )( &::MaterialManager::clear ) )
        .def(
            "getMaterial"
            , (::IMaterial const * ( ::MaterialManager::* )( ::std::string const & ) )( &::MaterialManager::getMaterial )
            , ( bp::arg("name") )
            , bp::return_internal_reference< >() )
        .def( bp::self_ns::str( bp::self ) );

    bp::class_< MultiLayer, boost::noncopyable >( "MultiLayer", bp::init< >() )
        .def(
            "addLayer"
            , (void ( ::MultiLayer::* )( ::Layer const & ) )( &::MultiLayer::addLayer )
            , ( bp::arg("p_child") ) )
        .def(
            "addLayerWithTopRoughness"
            , (void ( ::MultiLayer::* )( ::Layer const &,::LayerRoughness const & ) )( &::MultiLayer::addLayerWithTopRoughness )
            , ( bp::arg("layer"), bp::arg("roughness") ) )
        .def(
            "getCrossCorrLength"
            , (double ( ::MultiLayer::* )(  ) const)( &::MultiLayer::getCrossCorrLength ) )
        .def(
            "getNumberOfLayers"
            , (::size_t ( ::MultiLayer::* )(  ) const)( &::MultiLayer::getNumberOfLayers ) )
        .def(
            "setCrossCorrLength"
            , (void ( ::MultiLayer::* )( double ) )( &::MultiLayer::setCrossCorrLength )
            , ( bp::arg("crossCorrLength") ) )
        .def( bp::self_ns::str( bp::self ) );

    bp::class_< ParameterPool, boost::noncopyable >( "ParameterPool", bp::init< >() )
        .def(
            "clear"
            , (void ( ::ParameterPool::* )(  ) )( &::ParameterPool::clear ) )
        .def(
            "clone"
            , (::ParameterPool * ( ::ParameterPool::* )(  ) )( &::ParameterPool::clone )
            , bp::return_value_policy< bp::manage_new_object >() )
        .def(
            "cloneWithPrefix"
            , (::ParameterPool * ( ::ParameterPool::* )( ::std::string ) )( &::ParameterPool::cloneWithPrefix )
            , ( bp::arg("prefix") )
            , bp::return_value_policy< bp::manage_new_object >() )
        .def(
            "copyToExternalPool"
            , (void ( ::ParameterPool::* )( ::std::string,::ParameterPool * ) )( &::ParameterPool::copyToExternalPool )
            , ( bp::arg("prefix"), bp::arg("external_pool") ) )
        .def(
            "registerParameter"
            , (bool ( ::ParameterPool::* )( ::std::string,double * ) )( &::ParameterPool::registerParameter )
            , ( bp::arg("name"), bp::arg("par") ) )
        .def(
            "size"
            , (::size_t ( ::ParameterPool::* )(  ) const)( &::ParameterPool::size ) )
        .def( bp::self_ns::str( bp::self ) );

}
