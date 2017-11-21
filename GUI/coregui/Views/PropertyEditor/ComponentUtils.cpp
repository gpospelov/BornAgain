// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentUtis.cpp
//! @brief     Implements ComponentUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentUtils.h"
#include "item_constants.h"
#include "SessionItem.h"

QStringList ComponentUtils::propertyRelatedTypes()
{
    QStringList result = QStringList() << Constants::PropertyType << Constants::GroupItemType
                                       << Constants::VectorType << Constants::BasicAxisType
                                       << Constants::AmplitudeAxisType
                                       << Constants::MaterialDataType;
    return result;
}

QList<const SessionItem*> ComponentUtils::componentItems(const SessionItem& item)
{
    static QStringList propertyRelated = ComponentUtils::propertyRelatedTypes();

    QList<const SessionItem*> result;

    if (item.modelType() == Constants::PropertyType)
        result.push_back(&item);

    for (auto child : item.children()) {
        if (!child->isVisible())
            continue;

        if (propertyRelated.contains(child->modelType()))
            result.append(child);

        if (child->modelType() == Constants::GroupItemType) {
            for (auto grandchild : child->children()) {
                if (grandchild->isVisible())
                    result+= ComponentUtils::componentItems(*grandchild);
            }
        }

    }

    return result;
}
