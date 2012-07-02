#include "PythonPlusplusHelper.h"
#include "OpticalFresnel.h"



//! operator is necessary to make pyplusplus/boost happy during exposing of FresnelCoeff to python using boost::vector_indexing_suite
bool OpticalFresnel::FresnelCoeff::operator==(OpticalFresnel::FresnelCoeff const &other) const
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

