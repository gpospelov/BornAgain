// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeBuilder.cpp
//! @brief     Implements class ParameterTreeBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterTreeBuilder.h"
#include "FitParameterHelper.h"
#include "GroupItem.h"
#include "JobItem.h"
#include "ModelPath.h"
#include "MultiLayerItem.h"
#include "ParameterTreeItems.h"
#include "SampleModel.h"
#include "ScientificDoubleProperty.h"
#include <QStack>

namespace
{
int copyNumberOfChild(const SessionItem* parent, const SessionItem* item)
{
    if (!item)
        return -1;
    int result = -1;
    int count = 0;
    QString itemName = item->displayName();
    // check child items:
    for (auto p_child_item : parent->childItems()) {
        QString childName = p_child_item->displayName();
        if (p_child_item == item)
            result = count;
        if (childName == itemName)
            ++count;
    }
    if (count > 1)
        return result;
    return -1;
}

void fixDisplayName(SessionItem *parent) {
    QVector<int> copyNumber;
    for (SessionItem *child : parent->childItems()) {
        copyNumber.push_back(copyNumberOfChild(parent, child));
    }

    int index(0);
    for (SessionItem *child : parent->childItems()) {
        if(copyNumber[index] >= 0)
            child->setDisplayName( child->displayName() + QString::number(copyNumber[index]));
        ++index;
    }

    for (SessionItem *child : parent->childItems()) {
        fixDisplayName(child);
    }

}

}

void ParameterTreeBuilder::createParameterTree(JobItem *item, const QString &tag)
{
    SessionItem *container
        = item->model()->insertNewItem(Constants::ParameterContainerType, item->index(), -1, tag);

    SessionItem *multiLayer
        = container->model()->insertNewItem(Constants::ParameterLabelType, container->index());
    handleItem(multiLayer, item->getItem(JobItem::T_SAMPLE));

    SessionItem *instrument
        = container->model()->insertNewItem(Constants::ParameterLabelType, container->index());
    handleItem(instrument, item->getItem(JobItem::T_INSTRUMENT));

//    fixDisplayName(container);

#ifndef NDEBUG
    // Provides all items in "JobItem/Parameter Tree Container" with domain links already
    // at the stage of ParameterTree creation. It is necessary for validation, in Release mode
    // it will lead for unnecessary large project files.
    populateDomainLinks(item, tag);
#endif

}

void ParameterTreeBuilder::handleItem(SessionItem *tree, SessionItem *source)
{
    if (tree->modelType() == Constants::ParameterLabelType) {
        tree->setDisplayName(source->itemName());

    }

    else if (tree->modelType() == Constants::ParameterType) {
        tree->setDisplayName(source->itemName());

        double sourceValue = source->value().toDouble();
        if(source->value().typeName() == Constants::ScientificDoublePropertyType) {
            ScientificDoubleProperty intensity = source->value().value<ScientificDoubleProperty>();
            sourceValue=intensity.getValue();
        }

        tree->setValue(QVariant(sourceValue));
        QString path = ModelPath::getPathFromIndex(source->index());
        int firstSlash = path.indexOf('/');
        path = path.mid(firstSlash + 1);
        tree->setItemValue(ParameterItem::P_LINK, path);        
        tree->setItemValue(ParameterItem::P_BACKUP, sourceValue);
        return;
    }

    else {
        return;
    }

    for (SessionItem *child : source->childItems()) {
        if (child->isVisible() && child->isEnabled()) {
            if (child->modelType() == Constants::PropertyType) {
                if (child->value().type() == QVariant::Double) {
                    SessionItem *branch
                        = tree->model()->insertNewItem(Constants::ParameterType, tree->index());
                    handleItem(branch, child);
                }
                else if (child->value().typeName() == Constants::ScientificDoublePropertyType) {
                    SessionItem *branch
                        = tree->model()->insertNewItem(Constants::ParameterType, tree->index());
                    handleItem(branch, child);

                }

            } else if (child->modelType() == Constants::GroupItemType) {
                SessionItem *currentItem
                    = dynamic_cast<GroupItem *>(child)->currentItem();
                if (currentItem && currentItem->rowCount() > 0) {
                    SessionItem *branch = tree->model()->insertNewItem(
                        Constants::ParameterLabelType, tree->index());
                    handleItem(branch, currentItem);
                }
            } else {
                SessionItem *branch
                    = tree->model()->insertNewItem(Constants::ParameterLabelType, tree->index());
                handleItem(branch, child);
            }
        }
    }
}

//! For every ParameterItem in JobItem's ParameterTree container creates a link to domain.
void ParameterTreeBuilder::populateDomainLinks(JobItem *jobItem, const QString &tag)
{
    SessionItem *current = jobItem->getItem(tag); // this is container
    QStack<SessionItem *> stack;
    stack.push(current);
    while (!stack.empty()) {
        current = stack.pop();
        if (current->modelType() == Constants::ParameterLabelType
                || current->modelType() == Constants::ParameterContainerType) {
            for (SessionItem *child : current->getItems()) {
                stack.push(child);
            }
        } else {
            if (ParameterItem *parItem = dynamic_cast<ParameterItem *>(current)) {
//                QString parItemPath = FitParameterHelper::getParameterItemPath(parItem);
//                std::string domainPath = ModelPath::translateParameterName(
//                    jobItem, parItemPath);
//                parItem->setItemValue(ParameterItem::P_DOMAIN, QString::fromStdString(domainPath));

                // new way of translating
                QString translation = "*/" + ModelPath::itemPathTranslation(*parItem->linkedItem(), jobItem);
                parItem->setItemValue(ParameterItem::P_DOMAIN, translation);
            }
        }
    }
}
