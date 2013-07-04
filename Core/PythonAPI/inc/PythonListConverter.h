// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/inc/PythonListConverter.h
//! @brief     Defines and implements template struct Vector_from_python_list.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYTHONLISTCONVERTER_H
#define PYTHONLISTCONVERTER_H


#include "boost/python/detail/wrap_python.hpp"

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include <boost/python.hpp>
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);

#include <vector>

namespace bp = boost::python;

//! Converter of Python list to std containers

//! from http://code.activestate.com/lists/python-cplusplus-sig/16463/
//!
template<typename T>
struct Vector_from_python_list
{
    //! convert Python list to std::vector
    Vector_from_python_list()
    {
        bp::converter::registry::push_back(&Vector_from_python_list<T>::convertible
                                           , &Vector_from_python_list<T>::construct
                                           , bp::type_id<std::vector<T> >() );
    }

    //! Determine if obj_ptr can be converted in a std::vector<T>
    static void* convertible(PyObject* obj_ptr)
    {
        if (!PyList_Check(obj_ptr)) return 0;
        return obj_ptr;
    }

    //! Convert obj_ptr into a std::vector<T>
    static void construct(PyObject* obj_ptr, bp::converter::rvalue_from_python_stage1_data* data)
    {
        // Extract the character data from the python string
        //      const char* value = PyString_AsString(obj_ptr);
        bp::list l(bp::handle<>(bp::borrowed(obj_ptr)));

        // Grab pointer to memory into which to construct the new std::vector<T>
        void* storage = ( (bp::converter::rvalue_from_python_storage<std::vector<T> >*) data)->storage.bytes;

        // in-place construct the new std::vector<T> using the character data
        // extraced from the python object
        std::vector<T>& v = *(new (storage) std::vector<T>());

        // populate the vector from list contains
        int le = len(l);
        v.resize(le);
        for(int i = 0;i!=le;++i) v[i] = bp::extract<T>(l[i]);

        // Stash the memory chunk pointer for later use by boost.python
        data->convertible = storage;
    }

};

void register_python2cpp_converters();

#endif // PYTHONLISTCONVERTER_H


