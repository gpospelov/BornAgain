// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.cpp
//! @brief     Implements class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PropertyItem.h"

PropertyItem::PropertyItem()
    :ParameterizedItem(Constants::PropertyType)
{

}

/*bool PropertyItem::setData(int column, const QVariant &data)
{
    if (displayName() == ParameterizedItem::P_NAME) {
        if (data.toString().isEmpty())
            return false;
        if (ParameterizedItem *item = parent()) {
            if (ParameterizedItem *item_parent = item->parent()) {
                // forbid setting duplicate name
                if (item_parent->getChildByName(data.toString())) {
                    return false;
                }
            }
        }
    }
    return ParameterizedItem::setData(column, data);
}*/
