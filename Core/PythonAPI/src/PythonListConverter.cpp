// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/src/PythonListConverter.cpp
//! @brief     Implements Vector_from_python_list.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PythonListConverter.h"
#include "Vectors3D.h"

void register_python2cpp_converters()
{
    Vector_from_python_list<double>();
    Vector_from_python_list<kvector_t>();
    Vector_from_python_list<std::string>();
    Vector_from_python_list<int>();
    Vector_from_python_list<std::vector<double> >();
}


