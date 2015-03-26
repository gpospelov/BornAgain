// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ICompositeSample.cpp
//! @brief     Implements class ICompositeSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ICompositeSample.h"
#include "ICompositeIterator.h"
#include "MessageService.h"
#include <sstream>
#include "Exceptions.h"


//! Registers child in the container

void ICompositeSample::registerChild(ISample *sample)
{
    if(sample) {
        m_samples.push_back(sample);
    }else {
        throw NullPointerException("ICompositeSample::registerChild -> Error. Null pointer.");
    }
}

//! remove registered child from the container

void ICompositeSample::deregisterChild(ISample *sample)
{
    m_samples.remove(sample);
}

//! Creates general iterator to walk through the tree of registered composite children

ICompositeIterator ICompositeSample::createIterator() const
{
    return ICompositeIterator(this);
}


