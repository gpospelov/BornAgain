// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/SampleTreeIterator.cpp
//! @brief     Implements class SampleTreeIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleTreeIterator.h"
#include "ICompositeIteratorStrategy.h"
#include "Exceptions.h"



IteratorState::IteratorState(const ISample *single_element)
    : m_position(0)
{
    m_samples.push_back(single_element);
}

IteratorState::IteratorState(std::vector<const ISample *> samples)
    : m_samples(samples)
    , m_position(0)
{
}


SampleTreeIterator::SampleTreeIterator(const ISample *root)
    : mp_root(root)
{
    mP_strategy.reset(new CompositeIteratorPreorderStrategy());
}

SampleTreeIterator &SampleTreeIterator::operator=(const SampleTreeIterator &other)
{
    mp_root = other.mp_root;
    mP_strategy.reset(other.mP_strategy->clone());
    return *this;
}

SampleTreeIterator::~SampleTreeIterator()
{
}

void SampleTreeIterator::first()
{
    m_memento_itor = mP_strategy->first(mp_root);
}

void SampleTreeIterator::next()
{
    mP_strategy->next(m_memento_itor);
}

const ISample *SampleTreeIterator::getCurrent()
{
    return m_memento_itor.getCurrent();
}

bool SampleTreeIterator::isDone() const
{
    return m_memento_itor.size()==0;
}

size_t SampleTreeIterator::getLevel() const
{
    return m_memento_itor.size();
}


