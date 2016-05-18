// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitModelHelper.h
//! @brief     Declares class FitModelHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITMODELHELPER_H
#define FITMODELHELPER_H

#include "WinDllMacros.h"
#include "SessionModel.h"
#include <QMap>

class ParameterItem;
class FitParameterItem;
class FitParameterContainerItem;
class JobItem;

//! The FitModelHelper class contains set of convenience static methods to handle various fitting
//! items in given JobItem

class BA_CORE_API_ FitModelHelper : public SessionModel
{
public:
    static void createFitParameter(FitParameterContainerItem *container, ParameterItem *parameterItem);

    static void removeFromFitParameters(FitParameterContainerItem *container, ParameterItem *parameterItem);
    static void addToFitParameter(FitParameterContainerItem *container, ParameterItem *parameterItem, const QString &fitParName);

    static FitParameterItem *getFitParameterItem(FitParameterContainerItem *container, ParameterItem *parameterItem);

    static QStringList getFitParameterNames(FitParameterContainerItem *container);
    static QString getParameterItemPath(ParameterItem *parameterItem);
    static ParameterItem *getParameterItem(FitParameterContainerItem *container, const QString &link);

};

#endif
