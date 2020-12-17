//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/comparators.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/model/comparators.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/customvariants.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/utils/reallimits.h"
#include <QMetaType>

using namespace ModelView;

bool Comparators::m_is_registered = false;

void Comparators::registerComparators() {
    if (!m_is_registered) {
        QMetaType::registerComparators<std::string>();
        QMetaType::registerComparators<std::vector<double>>();
        QMetaType::registerComparators<ComboProperty>();
        QMetaType::registerComparators<ExternalProperty>();
        QMetaType::registerComparators<RealLimits>();
        m_is_registered = true;
    }
}

bool Comparators::registered() {
    return m_is_registered;
}
