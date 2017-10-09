// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/VectorItem.cpp
//! @brief     Implements class VectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "VectorItem.h"

const QString VectorItem::P_X = "X";
const QString VectorItem::P_Y = "Y";
const QString VectorItem::P_Z = "Z";

VectorItem::VectorItem()
    : SessionItem(Constants::VectorType)
{
    addProperty(P_X, 0.0)->setLimits(RealLimits::limitless())
        .setToolTip(QStringLiteral("x-coordinate in nanometers"));
    addProperty(P_Y, 0.0)->setLimits(RealLimits::limitless())
        .setToolTip(QStringLiteral("y-coordinate in nanometers"));
    addProperty(P_Z, 0.0)->setLimits(RealLimits::limitless())
        .setToolTip(QStringLiteral("z-coordinate in nanometers"));

    mapper()->setOnPropertyChange(
        [this](const QString &){
            setValue(itemLabel());
        }
    );

    setValue(itemLabel());
    setEditable(false);
}

QString VectorItem::itemLabel() const
{
    return QString("(%1, %2, %3)").arg(getItemValue(P_X).toDouble())
                                  .arg(getItemValue(P_Y).toDouble())
            .arg(getItemValue(P_Z).toDouble());
}

kvector_t VectorItem::getVector() const
{
    return kvector_t(getItemValue(P_X).toDouble(),
                     getItemValue(P_Y).toDouble(),
                     getItemValue(P_Z).toDouble());
}

