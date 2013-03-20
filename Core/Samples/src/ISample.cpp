// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ISample.cpp
//! @brief     Implements class ISample.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "ISample.h"
#include "ICompositeSample.h"
#include "ICompositeIterator.h"
#include "Utils.h"

ISample *ISample::clone() const
{
    throw NotImplementedException("ISample::clone() -> Error! Method is not implemented");
}

void ISample::print_structure()
{
    std::cout << getName() << " " << this << std::endl;
    if(getCompositeSample()) {
        ICompositeIterator it = getCompositeSample()->createIterator();
        it.first();
        while(!it.is_done())
        {
            ISample *smp = it.get_current();
            if(smp) {
                int nlevel = (int)it.get_level();
                for(int i=0; i<nlevel; i++) std::cout << "... ";
                std::cout << (*smp) << std::endl;
            } else {
                std::cout << "NULL" << std::endl;
            }
            it.next();
        }
    }
}

//! add parameters from local pool to external pool and call recursion over direct children

std::string ISample::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number) const
{
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // going through direct children of given sample and copy they parameters recursively
    const ICompositeSample *sample = getCompositeSample();
    if( sample ) {

        // Here we need some default mechanism to handle cases with many children with same name.
        // Lets run through all direct children and save their names
        Utils::StringUsageMap strUsageMap;
        for(ICompositeSample::const_iterator_t it=sample->begin_shallow(); it!=sample->end_shallow(); ++it) {
            strUsageMap.add( new_path +(*it)->getName() ); // saving children name
        }

        // Now we run through direct children again, and assign copy number for all children with same name
        Utils::StringUsageMap strUsageMap2;
        for(ICompositeSample::const_iterator_t it=sample->begin_shallow(); it!=sample->end_shallow(); ++it) {
            std::string children_name = new_path +(*it)->getName();
            strUsageMap2.add(children_name);
            int ncopy = strUsageMap2[children_name]-1; // staring from 0

            // if object is in single exemplar, we do not want any copy number
            if(strUsageMap[children_name] == 1) ncopy = -1;

            (*it)->addParametersToExternalPool(new_path, external_pool, ncopy);
        }
    }
    return new_path;
}
