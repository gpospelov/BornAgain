// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/IFunctionAdapter.cpp
//! @brief     Implements class IFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IFunctionAdapter.h"

using namespace Fit;

IFunctionAdapter::IFunctionAdapter()
    : m_number_of_calls(0)
{

}

int IFunctionAdapter::numberOfCalls() const
{
    return m_number_of_calls;
}

IFunctionAdapter::~IFunctionAdapter() = default;

