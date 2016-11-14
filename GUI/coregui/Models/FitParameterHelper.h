// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterHelper.h
//! @brief     Defines class FitParameterHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERHELPER_H
#define FITPARAMETERHELPER_H

#include "WinDllMacros.h"
#include <QStringList>

class ParameterItem;
class FitParameterItem;
class FitParameterContainerItem;

//! The FitParameterHelper class contains set of convenience static methods to handle
//! various fitting items in given JobItem.

class BA_CORE_API_ FitParameterHelper
{
public:
    static void createFitParameter(FitParameterContainerItem *container,
                                   ParameterItem *parameterItem);

    static void removeFromFitParameters(FitParameterContainerItem *container,
                                        ParameterItem *parameterItem);
    static void addToFitParameter(FitParameterContainerItem *container,
                                  ParameterItem *parameterItem, const QString &fitParName);

    static FitParameterItem *getFitParameterItem(FitParameterContainerItem *container,
                                                 ParameterItem *parameterItem);

    static QStringList getFitParameterNames(FitParameterContainerItem *container);
    static QString getParameterItemPath(const ParameterItem *parameterItem);
    static ParameterItem *getParameterItem(FitParameterContainerItem *container,
                                           const QString &link);
};

#endif // FITPARAMETERHELPER_H
