// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/src/PythonListConverter.cpp
//! @brief     Implements Vector_from_python_list.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PythonListConverter.h"
#include "Types.h"

void register_python2cpp_converters()
{
    Vector_from_python_list<double>();
    Vector_from_python_list<kvector_t>();
    Vector_from_python_list<std::string>();
}


