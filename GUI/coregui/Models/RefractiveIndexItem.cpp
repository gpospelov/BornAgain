// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RefractiveIndexItem.cpp
//! @brief     Implements class RefractiveIndexItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RefractiveIndexItem.h"
#include "ScientificDoubleProperty.h"


const QString RefractiveIndexItem::P_DELTA = "delta";
const QString RefractiveIndexItem::P_BETA = "beta";


RefractiveIndexItem::RefractiveIndexItem()
    : ParameterizedItem(Constants::RefractiveIndexType)
{
    ScientificDoubleProperty delta(0.0);
    registerProperty(P_DELTA, delta.getVariant());

    ScientificDoubleProperty beta(0.0);
    registerProperty(P_BETA, beta.getVariant());
}

QString RefractiveIndexItem::itemLabel() const
{
    return QString("(1 - %1, %2)").arg(getDelta()).arg(getBeta());
}

double RefractiveIndexItem::getDelta() const
{
    return getRegisteredProperty(P_DELTA).value<ScientificDoubleProperty>().getValue();
}

void RefractiveIndexItem::setDelta(double delta)
{
    ScientificDoubleProperty scd_property = getRegisteredProperty(P_DELTA).value<ScientificDoubleProperty>();
    scd_property.setValue(delta);
    setRegisteredProperty(P_DELTA, scd_property.getVariant());
}

double RefractiveIndexItem::getBeta() const
{
    return getRegisteredProperty(P_BETA).value<ScientificDoubleProperty>().getValue();
}

void RefractiveIndexItem::setBeta(double beta)
{
    ScientificDoubleProperty scd_property = getRegisteredProperty(P_BETA).value<ScientificDoubleProperty>();
    scd_property.setValue(beta);
    setRegisteredProperty(P_BETA, scd_property.getVariant());
}
