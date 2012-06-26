#include "PythonToolsInterface.h"
#include "Units.h"

#include <boost/python.hpp>
namespace bp = boost::python;


void PythonInterface::export_tools()
{
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

