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
#include "SampleTreeIterator.h"
#include "MessageService.h"
#include "Exceptions.h"
#include <algorithm>
#include <sstream>


//! Registers child in the container

void ICompositeSample::registerChild(ISample *sample)
{
    if(sample) {
        m_samples.push_back(sample);
    } else {
        throw NullPointerException("ICompositeSample::registerChild -> Error. Null pointer.");
    }
}

//! remove registered child from the container

void ICompositeSample::deregisterChild(ISample *sample)
{
    std::vector<ISample*>::iterator it = std::find(m_samples.begin(), m_samples.end(), sample);
    if (it != m_samples.end()) {
        m_samples.erase(it);
    }
}

ISample *ICompositeSample::operator[](size_t index)
{
    if (childIndexInRange(index)) {
        return m_samples[index];
    }
    return 0;
}

const ISample *ICompositeSample::operator[](size_t index) const
{
    if (childIndexInRange(index)) {
        return m_samples[index];
    }
    return 0;
}

std::vector<const ISample *> ICompositeSample::getChildren() const
{
    std::vector<const ISample *> result;
    for (size_t i=0; i<m_samples.size(); ++i) {
        result.push_back(m_samples[i]);
    }
    return result;
}

bool ICompositeSample::childIndexInRange(size_t index) const
{
    return index<m_samples.size();
}

