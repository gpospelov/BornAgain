// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SelectableGroupProperty.cpp
//! @brief     Implements class SelectableGroupProperty
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SelectableGroupProperty.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"
#include <QDebug>



//void SelectableGroupProperty::setValue(const QString &value)
//{
//    qDebug() << "SelectableGroupProperty::setValue() -> " << value;
//    if(value == getValue()) return;

//    FancyGroupProperty::setValue(value);

//    if(m_parent) {
//        m_parent->addPropertyItem(getGroupName(), createCorrespondingItem());
//        emit m_parent->propertyItemChanged(getGroupName());
//    }
//}

