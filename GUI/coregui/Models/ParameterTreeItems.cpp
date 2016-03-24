// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterTreeItem.h
//! @brief     Implements classes for ParameterTreeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterTreeItems.h"

ParameterLabelItem::ParameterLabelItem()
    : SessionItem(Constants::ParameterLabelType)
{
    const QString T_CHILDREN = "children tag";
    registerTag(T_CHILDREN, 0, -1, QStringList() << Constants::ParameterLabelType << Constants::ParameterType);
    setDefaultTag(T_CHILDREN);
}

ParameterItem::ParameterItem()
    : SessionItem(Constants::ParameterType)
{

}
