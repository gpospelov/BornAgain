// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitSuiteItem.cpp
//! @brief     Implements class FitSuiteItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitSuiteItem.h"

const QString FitSuiteItem::T_FIT_PARAMETERS = "Fit parameters container";

FitSuiteItem::FitSuiteItem()
    : SessionItem(Constants::FitSuiteType)
{
    registerTag(T_FIT_PARAMETERS, 1, 1, QStringList() << Constants::FitParameterContainerType);
}
