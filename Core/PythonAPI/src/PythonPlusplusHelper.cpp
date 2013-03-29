// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/src/PythonPlusplusHelper.cpp
//! @brief     Implements OpticalFresnel::FresnelCoeff::operator== (why ?)
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "PythonPlusplusHelper.h"
#include "OpticalFresnel.h"

//! operator== is necessary to make pyplusplus/boost happy during exposing of FresnelCoeff to python using boost::vector_indexing_suite
bool OpticalFresnel::FresnelCoeff::operator==(OpticalFresnel::FresnelCoeff const& other) const
{
    if(kz != other.kz ||
       r  != other.r  ||
       t  != other.t  ||
       rb != other.rb ||
       tb != other.tb ||
       X  != other.X  ||
       R  != other.R  ||
       T  != other.T )
    {
        return false;
    } else {
        return true;
    }
}


//template BasicVector3D<double> operator/ <double, double> (const BasicVector3D<double>& v, double a);

