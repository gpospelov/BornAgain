// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      PythonAPI/src/PythonListConverter.cpp 
//! @brief     Implements Vector_from_python_list.
//
// ************************************************************************** //

#include "PythonListConverter.h"
#include "Types.h"

void register_python2cpp_converters()
{
    Vector_from_python_list<double>();
    Vector_from_python_list<kvector_t>();
}
