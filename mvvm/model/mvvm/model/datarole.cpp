//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/datarole.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/model/datarole.h"
#include "mvvm/model/customvariants.h"

using namespace ModelView;

DataRole::DataRole(Variant data, int role) : m_data(std::move(data)), m_role(role) {}

bool DataRole::operator==(const DataRole& other) const {
    return m_role == other.m_role && Utils::IsTheSame(m_data, other.m_data);
}
