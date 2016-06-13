// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TestItem.cpp
//! @brief     Implements class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
    addGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    addProperty(P_VALUE, 99.0);
    ComboProperty types;
    types << "property 1" << "property 2" << "property 3";
    addProperty(P_COMBO, types.getVariant());
    addGroupProperty(P_VECTOR, Constants::VectorType);
}
