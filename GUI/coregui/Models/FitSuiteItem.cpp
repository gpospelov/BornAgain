// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitSuiteItem.cpp
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
#include "FitParameterItems.h"
#include "MinimizerItem.h"

const QString FitSuiteItem::P_UPDATE_INTERVAL = "Update interval";
const QString FitSuiteItem::P_ITERATION_COUNT = "Number of iterations";
const QString FitSuiteItem::P_CHI2 = "Chi2";
const QString FitSuiteItem::T_FIT_PARAMETERS = "Fit parameters container";
const QString FitSuiteItem::T_MINIMIZER = "Minimizer settings";


FitSuiteItem::FitSuiteItem()
    : SessionItem(Constants::FitSuiteType)
{
    addProperty(P_UPDATE_INTERVAL, 10);
    addProperty(P_ITERATION_COUNT, 0);
    addProperty(P_CHI2, 0.0);

    registerTag(T_FIT_PARAMETERS, 1, 1, QStringList() << Constants::FitParameterContainerType);
    registerTag(T_MINIMIZER, 1, 1, QStringList() << Constants::MinimizerContainerType);
}

FitParameterContainerItem *FitSuiteItem::fitParameterContainerItem()
{
    return dynamic_cast<FitParameterContainerItem *>(getItem(FitSuiteItem::T_FIT_PARAMETERS));
}

MinimizerContainerItem *FitSuiteItem::minimizerContainerItem()
{
    return dynamic_cast<MinimizerContainerItem *>(getItem(FitSuiteItem::T_MINIMIZER));
}

//std::unique_ptr<FitSuite> FitSuiteItem::createFitSuite()
//{
//    std::unique_ptr<FitSuite> result(new FitSuite);

////    SessionItem *container = getItem(T_FIT_PARAMETERS);
////    Q_ASSERT(container);

////    foreach(SessionItem *parItem, container->getItems(T_FIT_PARAMETERS)) {

////    }

//    return std::move(result);
//}
