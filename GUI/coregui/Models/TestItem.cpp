// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TestItem.cpp
//! @brief     Implements class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestItem.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include "Units.h"
#include <QDebug>

const QString TestItem::P_DISTRIBUTION = "Distribution";
const QString TestItem::P_VALUE = "Value";
const QString TestItem::P_COMBO = "Combo";
const QString TestItem::P_VECTOR = "Vector";
TestItem::TestItem()
    : SessionItem(QString("TestItem"))
{
    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    registerProperty(P_VALUE, 99.0);
    ComboProperty types;
    types << "property 1" << "property 2" << "property 3";
    registerProperty(P_COMBO, types.getVariant());
    registerGroupProperty(P_VECTOR, Constants::VectorType);
}
