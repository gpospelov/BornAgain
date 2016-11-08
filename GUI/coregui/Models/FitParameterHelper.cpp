// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterHelper.cpp
//! @brief     Implements class FitModelHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterHelper.h"
#include "FitParameterItems.h"
#include "JobItem.h"
#include "JobModel.h"
#include "ModelPath.h"
#include "ParameterTreeItems.h"

//! Creates fit parameter from given ParameterItem, sets starting value to the value
//! of ParameterItem, copies link.

void FitParameterHelper::createFitParameter(FitParameterContainerItem *container,
                                        ParameterItem *parameterItem)
{
    Q_ASSERT(container);
    Q_ASSERT(parameterItem);

    removeFromFitParameters(container, parameterItem);

    FitParameterItem *fitPar = dynamic_cast<FitParameterItem *>(
        container->model()->insertNewItem(Constants::FitParameterType, container->index()));
    Q_ASSERT(fitPar);
    fitPar->setDisplayName(QStringLiteral("par"));
    SessionItem *link
        = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
    fitPar->setItemValue(FitParameterItem::P_START_VALUE, parameterItem->value());
    link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));

    fitPar->initMinMaxValues(parameterItem->getLinkedItem()->limits());
}

//! Removes link to given parameterItem from fit parameters

void FitParameterHelper::removeFromFitParameters(FitParameterContainerItem *container,
                                             ParameterItem *parameterItem)
{
    FitParameterItem *fitParItem = getFitParameterItem(container, parameterItem);

    if (fitParItem) {
        foreach (SessionItem *linkItem, fitParItem->getItems(FitParameterItem::T_LINK)) {
            if (getParameterItemPath(parameterItem)
                == linkItem->getItemValue(FitParameterLinkItem::P_LINK)) {
                fitParItem->model()->removeRow(linkItem->index().row(), linkItem->index().parent());
                break;
            }
        }
    }
}

//! Adds given parameterItem to the existing fit parameter with display name fitParName.
//! If parameterItem is already linked with another fitParameter, it will be relinked

void FitParameterHelper::addToFitParameter(FitParameterContainerItem *container,
                                       ParameterItem *parameterItem, const QString &fitParName)
{
    Q_ASSERT(container);

    removeFromFitParameters(container, parameterItem);
    foreach (SessionItem *fitPar,
             container->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        if (fitPar->displayName() == fitParName) {
            SessionItem *link
                = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
            link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));
            break;
        }
    }
}

//! Returns fFitParameterItem corresponding to given ParameterItem

FitParameterItem *FitParameterHelper::getFitParameterItem(FitParameterContainerItem *container,
                                                      ParameterItem *parameterItem)
{
    Q_ASSERT(container);
    return container->getFitParameterItem(getParameterItemPath(parameterItem));
}

//! Returns list of fit parameter display names

QStringList FitParameterHelper::getFitParameterNames(FitParameterContainerItem *container)
{
    Q_ASSERT(container);
    QStringList result;
    foreach (SessionItem *item, container->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        result.append(item->displayName());
    }
    return result;
}

//! return path to given item in the ParameterTreeContainer

QString FitParameterHelper::getParameterItemPath(const ParameterItem *parameterItem)
{
    QString result = ModelPath::getPathFromIndex(parameterItem->index());
    QString containerPrefix = Constants::ParameterContainerType + "/";
    int containerEnd = result.indexOf(containerPrefix) + containerPrefix.size();
    result = result.mid(containerEnd);
    return result;
}

//! Returns ParameterItem corresponding to given link.
//! Link is relative to ParameterContainerItem, so first we have to find it

ParameterItem *FitParameterHelper::getParameterItem(FitParameterContainerItem *container,
                                                const QString &link)
{
    SessionItem *cur = container;
    while (cur && cur->modelType() != Constants::JobItemType) {
        cur = cur->parent();
    }
    Q_ASSERT(cur->modelType() == Constants::JobItemType);
    JobItem *jobItem = dynamic_cast<JobItem *>(cur);
    Q_ASSERT(jobItem);
    return dynamic_cast<ParameterItem *>(
        ModelPath::getItemFromPath(link, jobItem->parameterContainerItem()));
}
