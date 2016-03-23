// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RefractiveIndexItem.cpp
//! @brief     Implements class RefractiveIndexItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RefractiveIndexItem.h"
#include "ScientificDoubleProperty.h"


const QString RefractiveIndexItem::P_DELTA = "delta";
const QString RefractiveIndexItem::P_BETA = "beta";


RefractiveIndexItem::RefractiveIndexItem()
    : SessionItem(Constants::RefractiveIndexType)
{
    ScientificDoubleProperty delta(0.0);
    addProperty(P_DELTA, delta.getVariant());

    ScientificDoubleProperty beta(0.0);
    addProperty(P_BETA, beta.getVariant());
}

QString RefractiveIndexItem::itemLabel() const
{
    return QString("(1 - %1, %2)").arg(getDelta()).arg(getBeta());
}

double RefractiveIndexItem::getDelta() const
{
    return getItemValue(P_DELTA).value<ScientificDoubleProperty>().getValue();
}

void RefractiveIndexItem::setDelta(double delta)
{
    ScientificDoubleProperty scd_property = getItemValue(P_DELTA).value<ScientificDoubleProperty>();
    scd_property.setValue(delta);
    setItemValue(P_DELTA, scd_property.getVariant());
}

double RefractiveIndexItem::getBeta() const
{
    return getItemValue(P_BETA).value<ScientificDoubleProperty>().getValue();
}

void RefractiveIndexItem::setBeta(double beta)
{
    ScientificDoubleProperty scd_property = getItemValue(P_BETA).value<ScientificDoubleProperty>();
    scd_property.setValue(beta);
    setItemValue(P_BETA, scd_property.getVariant());
}
