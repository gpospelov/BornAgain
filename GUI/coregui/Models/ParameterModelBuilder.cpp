// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterModelBuilder.cpp
//! @brief     Implements class ParameterModelBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterModelBuilder.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "InstrumentItem.h"
#include "JobItem.h"
#include "JobModel.h"
#include "BeamItem.h"
#include "BeamDistributionItem.h"
#include "BeamWavelengthItem.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include "AngleProperty.h"
#include "GUIHelpers.h"
#include "DistributionItem.h"
#include "GroupItem.h"
#include "JobItem.h"
#include "ModelPath.h"
#include "ParameterTreeItems.h"
#include "FitModelHelper.h"
#include "FitParameterModel.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStack>
#include <QDebug>


void ParameterModelBuilder::createParameterTree(JobItem *item, const QString &tag)
{
//    SessionItem *container = item->model()->insertNewItem(Constants::ParameterLabelType, item->index(), -1, tag);
//    container->setDisplayName("Parameter Tree Container");

    SessionItem *container = item->model()->insertNewItem(Constants::ParameterContainerType, item->index(), -1, tag);

    SessionItem *multiLayer = container->model()->insertNewItem(Constants::ParameterLabelType, container->index());
    handleItem(multiLayer, item->getItem(JobItem::T_SAMPLE));

    SessionItem *instrument = container->model()->insertNewItem(Constants::ParameterLabelType, container->index());
    handleItem(instrument, item->getItem(JobItem::T_INSTRUMENT));

#ifndef NDEBUG
    // Provides all items in "JobItem/Parameter Tree Container" with domain links already
    // at the stage of ParameterTree creation. It is necessary for validation, in Release mode
    // it will lead for unnecessary larde project files.
    populateDomainLinks(item, tag);
#endif
}

void ParameterModelBuilder::handleItem(SessionItem *tree, SessionItem *source)
{
    if (tree->modelType() == Constants::ParameterLabelType) {
        tree->setDisplayName(source->itemName());

    }

    else if (tree->modelType() == Constants::ParameterType) {
        tree->setDisplayName(source->itemName());
        tree->setValue(source->value());
        QString path = ModelPath::getPathFromIndex(source->index());
        int firstSlash = path.indexOf('/');
        path = path.mid(firstSlash + 1);
        tree->setItemValue(ParameterItem::P_LINK, path);
        tree->setItemValue(ParameterItem::P_BACKUP, source->value());
        return;
    }

    else {
        return;
    }

    for (SessionItem *child : source->childItems()) {
        if (child->isVisible() && child->isEnabled()) {
            if (child->modelType() == Constants::PropertyType) {
                if (child->value().type() == QVariant::Double) {
                    SessionItem *branch = tree->model()->insertNewItem(Constants::ParameterType, tree->index());
                    handleItem(branch, child);
                }
            } else if (child->modelType() == Constants::GroupItemType) {
                SessionItem *currentItem = dynamic_cast<GroupItem*>(child)->group()->getCurrentItem();
                if (currentItem && currentItem->rowCount() > 0) {
                    SessionItem *branch = tree->model()->insertNewItem(Constants::ParameterLabelType, tree->index());
                    handleItem(branch, currentItem);
                }
            } else {
                SessionItem *branch = tree->model()->insertNewItem(Constants::ParameterLabelType, tree->index());
                handleItem(branch, child);
            }
        }
    }
}

//! For every ParameterItem in JobItem's ParameterTree container creates a link to domain.
void ParameterModelBuilder::populateDomainLinks(JobItem *jobItem, const QString &tag)
{
    SessionItem *current = jobItem->getItem(tag); //this is container
    QStack<SessionItem*> stack;
    stack.push(current);
    while(!stack.empty()) {
        current = stack.pop();
        if (current->modelType() == Constants::ParameterLabelType) {
            for (SessionItem *child : current->getItems()) {
                stack.push(child);
            }
        } else {
            if(ParameterItem *parItem = dynamic_cast<ParameterItem *>(current)) {
                QString parItemPath = FitModelHelper::getParameterItemPath(parItem);
                std::string domainPath = ModelPath::translateParameterName(jobItem->getMultiLayerItem()->parent(), parItemPath);
                parItem->setItemValue(ParameterItem::P_DOMAIN, QString::fromStdString(domainPath));
            }
        }
    }

}
