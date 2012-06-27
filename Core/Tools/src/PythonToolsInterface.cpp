#include "PythonToolsInterface.h"
#include "Units.h"
#include "Types.h"

#include <boost/python.hpp>
namespace bp = boost::python;


void PythonInterface::export_tools()
{
    { //::KVector< double >
        typedef bp::class_< KVector< double > > kvector_t_exposer_t;
        kvector_t_exposer_t kvector_t_exposer = kvector_t_exposer_t( "kvector_t", bp::init< >() );
        bp::scope kvector_t_scope( kvector_t_exposer );
        kvector_t_exposer.def( bp::init< double, double, double >(( bp::arg("x"), bp::arg("y"), bp::arg("z") )) );
        { //::KVector< double >::LambdaAlphaPhi

            typedef KVector< double > exported_class_t;
            typedef ::KVector< double > ( *LambdaAlphaPhi_function_type )( double,double,double );

            kvector_t_exposer.def(
                "LambdaAlphaPhi"
                , LambdaAlphaPhi_function_type( &::KVector< double >::LambdaAlphaPhi )
                , ( bp::arg("lambda"), bp::arg("alpha"), bp::arg("phi") ) );

        }
        { //::KVector< double >::mag

            typedef KVector< double > exported_class_t;
            typedef double ( exported_class_t::*mag_function_type )(  ) const;

            kvector_t_exposer.def(
                "mag"
                , mag_function_type( &::KVector< double >::mag ) );

        }
        { //::KVector< double >::mag2

            typedef KVector< double > exported_class_t;
            typedef double ( exported_class_t::*mag2_function_type )(  ) const;

            kvector_t_exposer.def(
                "mag2"
                , mag2_function_type( &::KVector< double >::mag2 ) );

        }
        { //::KVector< double >::magxy

            typedef KVector< double > exported_class_t;
            typedef double ( exported_class_t::*magxy_function_type )(  ) const;

            kvector_t_exposer.def(
                "magxy"
                , magxy_function_type( &::KVector< double >::magxy ) );

        }
        kvector_t_exposer.def( bp::self += bp::self );
        kvector_t_exposer.def( bp::self -= bp::self );
        { //::KVector< double >::operator=

            typedef KVector< double > exported_class_t;
            typedef ::KVector< double > & ( exported_class_t::*assign_function_type )( ::KVector< double > const & ) ;

            kvector_t_exposer.def(
                "assign"
                , assign_function_type( &::KVector< double >::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );

        }
        { //::KVector< double >::setLambdaAlphaPhi

            typedef KVector< double > exported_class_t;
            typedef void ( exported_class_t::*setLambdaAlphaPhi_function_type )( double,double,double ) ;

            kvector_t_exposer.def(
                "setLambdaAlphaPhi"
                , setLambdaAlphaPhi_function_type( &::KVector< double >::setLambdaAlphaPhi )
                , ( bp::arg("lambda"), bp::arg("alpha"), bp::arg("phi") ) );

        }
        { //::KVector< double >::setMagThetaPhi

            typedef KVector< double > exported_class_t;
            typedef void ( exported_class_t::*setMagThetaPhi_function_type )( double,double,double ) ;

            kvector_t_exposer.def(
                "setMagThetaPhi"
                , setMagThetaPhi_function_type( &::KVector< double >::setMagThetaPhi )
                , ( bp::arg("mag"), bp::arg("theta"), bp::arg("phi") ) );

        }
        { //::KVector< double >::x

            typedef KVector< double > exported_class_t;
            typedef double ( exported_class_t::*x_function_type )(  ) const;

            kvector_t_exposer.def(
                "x"
                , x_function_type( &::KVector< double >::x ) );

        }
        { //::KVector< double >::y

            typedef KVector< double > exported_class_t;
            typedef double ( exported_class_t::*y_function_type )(  ) const;

            kvector_t_exposer.def(
                "y"
                , y_function_type( &::KVector< double >::y ) );

        }
        { //::KVector< double >::z

            typedef KVector< double > exported_class_t;
            typedef double ( exported_class_t::*z_function_type )(  ) const;

            kvector_t_exposer.def(
                "z"
                , z_function_type( &::KVector< double >::z ) );

        }
        kvector_t_exposer.staticmethod( "LambdaAlphaPhi" );
        kvector_t_exposer.def( bp::self_ns::str( bp::self ) );
    }

    { //::Units::deg2rad

        typedef double ( *deg2rad_function_type )( double );

        bp::def(
            "deg2rad"
            , deg2rad_function_type( &::Units::deg2rad )
            , ( bp::arg("angle") ) );

    }

    { //::Units::rad2deg

        typedef double ( *rad2deg_function_type )( double );

        bp::def(
            "rad2deg"
            , rad2deg_function_type( &::Units::rad2deg )
            , ( bp::arg("angle") ) );

    }

    bp::scope().attr("angstrom") = Units::angstrom;

    bp::scope().attr("deg") = Units::deg;

    bp::scope().attr("degree") = Units::degree;

    bp::scope().attr("meter") = Units::meter;

    bp::scope().attr("micrometer") = Units::micrometer;

    bp::scope().attr("millimeter") = Units::millimeter;

    bp::scope().attr("milliradian") = Units::milliradian;

    bp::scope().attr("mrad") = Units::mrad;

    bp::scope().attr("nanometer") = Units::nanometer;

    bp::scope().attr("nm") = Units::nm;

    bp::scope().attr("rad") = Units::rad;

    bp::scope().attr("radian") = Units::radian;

    bp::scope().attr("sr") = Units::sr;

    bp::scope().attr("steradian") = Units::steradian;
}

