#include "Python.h"
#define PY_ARRAY_UNIQUE_SYMBOL scatt_ARRAY_API
#include "numpy/arrayobject.h"
// the order of 3 guys above is important

#include "PythonModule.h"
#include <boost/python.hpp>
#include "PythonInterface_classes_1.h"
#include "PythonInterface_classes_2.h"
#include "PythonInterface_classes_3.h"
#include "PythonInterface_free_functions.h"
#include "PythonInterface_global_variables.h"
#include "PythonListConverter.h"


void display(const std::vector<double>&v)
{
  std::copy(v.begin(),v.end(), std::ostream_iterator<double>(std::cout," "));
  std::cout << std::endl;
}


BOOST_PYTHON_MODULE(libScattCore){

    register_classes_1();

    register_classes_2();

    register_classes_3();

    register_global_variables();

    register_free_functions();

    register_python2cpp_converters();

    boost::python::def("display", display);

    import_array();
    /* IMPORTANT
    this is initialisation function from C-API of python-numpy package. It has to be called once in the
    initialisation section of the module (i.e. here), when module is going to use any of python numpy C-API.
    Additional rule: when initialisation of the module, and functions that use python-numpy C-API are located in
    different files (different compilation units) - and this is exactly our case - additional defines has
    to be inserted before #include "numpy/arrayobject.h". See explanations
    http://docs.scipy.org/doc/numpy/reference/c-api.array.html#import_array
    */


}

