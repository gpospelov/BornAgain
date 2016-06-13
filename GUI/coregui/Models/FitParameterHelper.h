// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterHelper.h
//! @brief     Declares class FitParameterHelper
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
#include <QMap>

class ParameterItem;
class FitParameterItem;
class FitParameterContainerItem;
class JobItem;

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
    static QString getParameterItemPath(ParameterItem *parameterItem);
    static ParameterItem *getParameterItem(FitParameterContainerItem *container,
                                           const QString &link);
};

#endif
