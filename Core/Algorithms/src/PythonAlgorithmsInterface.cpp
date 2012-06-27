#include "PythonAlgorithmsInterface.h"
#include "OpticalFresnel.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
namespace bp = boost::python;


void PythonInterface::export_algorithms()
{

    { //::std::vector< OpticalFresnel::FresnelCoeff >
        typedef bp::class_< std::vector< OpticalFresnel::FresnelCoeff > > MultiLayerCoeff_t_exposer_t;
        MultiLayerCoeff_t_exposer_t MultiLayerCoeff_t_exposer = MultiLayerCoeff_t_exposer_t( "MultiLayerCoeff_t" );
        bp::scope MultiLayerCoeff_t_scope( MultiLayerCoeff_t_exposer );
        //WARNING: the next line of code will not compile, because "::OpticalFresnel::FresnelCoeff" does not have operator== !
        //MultiLayerCoeff_t_exposer.def( bp::vector_indexing_suite< ::std::vector< OpticalFresnel::FresnelCoeff > >() );
    }

    { //::OpticalFresnel
        typedef bp::class_< OpticalFresnel > OpticalFresnel_exposer_t;
        OpticalFresnel_exposer_t OpticalFresnel_exposer = OpticalFresnel_exposer_t( "OpticalFresnel", bp::init< >() );
        bp::scope OpticalFresnel_scope( OpticalFresnel_exposer );
        bp::class_< OpticalFresnel::FresnelCoeff >( "FresnelCoeff", bp::init< >() )
            .def_readwrite( "R", &OpticalFresnel::FresnelCoeff::R )
            .def_readwrite( "T", &OpticalFresnel::FresnelCoeff::T )
            .def_readwrite( "X", &OpticalFresnel::FresnelCoeff::X )
            .def_readwrite( "kz", &OpticalFresnel::FresnelCoeff::kz )
            .def_readwrite( "r", &OpticalFresnel::FresnelCoeff::r )
            .def_readwrite( "rb", &OpticalFresnel::FresnelCoeff::rb )
            .def_readwrite( "t", &OpticalFresnel::FresnelCoeff::t )
            .def_readwrite( "tb", &OpticalFresnel::FresnelCoeff::tb );
        bp::class_< OpticalFresnel::MultiLayerCoeff >( "MultiLayerCoeff" )
            .def(
                "__getitem__"
                , (::OpticalFresnel::FresnelCoeff & ( ::OpticalFresnel::MultiLayerCoeff::* )( ::size_t ) )( &::OpticalFresnel::MultiLayerCoeff::operator[] )
                , ( bp::arg("i") )
                , bp::return_internal_reference< >() )
            .def(
                "size"
                , (::size_t ( ::OpticalFresnel::MultiLayerCoeff::* )(  ) const)( &::OpticalFresnel::MultiLayerCoeff::size ) )
            .def_readwrite( "m_data", &OpticalFresnel::MultiLayerCoeff::m_data );
        { //::OpticalFresnel::execute

            typedef int ( *execute_function_type )( ::MultiLayer const &,::kvector_t const &,::std::vector< OpticalFresnel::FresnelCoeff > & );

            OpticalFresnel_exposer.def(
                "execute"
                , execute_function_type( &::OpticalFresnel::execute )
                , ( bp::arg("sample"), bp::arg("k"), bp::arg("coeff") ) );

        }
        { //::OpticalFresnel::execute

            typedef int ( *execute_function_type )( ::MultiLayer const &,::kvector_t const &,::OpticalFresnel::MultiLayerCoeff & );

            OpticalFresnel_exposer.def(
                "execute"
                , execute_function_type( &::OpticalFresnel::execute )
                , ( bp::arg("sample"), bp::arg("k"), bp::arg("coeff") ) );

        }
        OpticalFresnel_exposer.staticmethod( "execute" );
    }
}
