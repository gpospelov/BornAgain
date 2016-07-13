// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitSuiteItem.h
//! @brief     Declares class FitSuiteItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEITEM_H
#define FITSUITEITEM_H

#include "SessionItem.h"

class FitSuite;
class FitParameterContainerItem;
class MinimizerContainerItem;

class BA_CORE_API_ FitSuiteItem : public SessionItem
{

public:
    static const QString P_UPDATE_INTERVAL;
    static const QString P_ITERATION_COUNT;
    static const QString P_CHI2;
    static const QString T_FIT_PARAMETERS;
    static const QString T_MINIMIZER;
    explicit FitSuiteItem();

    FitParameterContainerItem *fitParameterContainerItem();
    MinimizerContainerItem *minimizerContainerItem();
//    std::unique_ptr<FitSuite> createFitSuite();
};

#endif // FITSUITEITEM_H
