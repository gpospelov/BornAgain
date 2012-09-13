#include "PythonListConverter.h"
#include "Types.h"

void register_python2cpp_converters()
{

    Vector_from_python_list<double>();
    Vector_from_python_list<kvector_t>();

}
