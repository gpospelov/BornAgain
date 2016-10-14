// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationAreaIterator.cpp
//! @brief     Implements class SimulationAreaIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationAreaIterator.h"
#include "SimulationArea.h"
#include "IDetector2D.h"

SimulationAreaIterator::SimulationAreaIterator(const SimulationArea *area, size_t start_at_index)
    : m_area(area)
    , m_index(start_at_index)
    , m_element_index(0)
{

}

SimulationAreaIterator &SimulationAreaIterator::operator++()
{
    while(m_area->detector()->isMasked(++m_index));
    ++m_element_index;
    return *this;
}

SimulationAreaIterator &SimulationAreaIterator::operator++(int)
{
    m_index++;
    m_element_index++;
    return *this;
}

