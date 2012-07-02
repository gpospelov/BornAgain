#include "PythonModule.h"
#include <boost/python.hpp>
#include "PythonInterface_classes_1.h"
#include "PythonInterface_classes_2.h"
#include "PythonInterface_classes_3.h"
#include "PythonInterface_free_functions.h"
#include "PythonInterface_global_variables.h"


BOOST_PYTHON_MODULE(libScattCore){
    register_classes_1();

    register_classes_2();

    register_classes_3();

    register_global_variables();

    register_free_functions();
}

