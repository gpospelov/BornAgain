#include "PythonModule.h"
#include <boost/python.hpp>


BOOST_PYTHON_MODULE(libScattCore)
{
    PythonInterface::export_algorithms();
    PythonInterface::export_samples();
    PythonInterface::export_tools();
}

