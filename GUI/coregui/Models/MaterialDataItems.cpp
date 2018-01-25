// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialDataItems.cpp
//! @brief     Implements MaterialDataItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MaterialDataItems.h"

MaterialDataItem::MaterialDataItem(const QString& modelType)
    : SessionItem(modelType)
{
}

// ------------------------------------------------------------------------------------------------

const QString MaterialRefractiveDataItem::P_DELTA = "Delta";
const QString MaterialRefractiveDataItem::P_BETA = "Beta";

MaterialRefractiveDataItem::MaterialRefractiveDataItem()
    : MaterialDataItem(Constants::MaterialRefractiveDataType)
{
    addProperty(P_DELTA, 0.0)->setEditorType(Constants::ScientificEditorType)
        .setLimits(RealLimits::limitless())
        .setToolTip("Delta of refractive index (n = 1 - delta + i*beta)");
    addProperty(P_BETA, 0.0)->setEditorType(Constants::ScientificEditorType)
        .setLimits(RealLimits::limitless())
        .setToolTip("Beta of refractive index (n = 1 - delta + i*beta)");

    mapper()->setOnPropertyChange([this](const QString&) { updateLabel(); });

    updateLabel();
    setEditable(false); // for label
}

double MaterialRefractiveDataItem::delta() const
{
    return getItemValue(P_DELTA).toDouble();
}

void MaterialRefractiveDataItem::setDelta(double real)
{
    setItemValue(P_DELTA, real);
}

double MaterialRefractiveDataItem::beta() const
{
    return getItemValue(P_BETA).toDouble();
}

void MaterialRefractiveDataItem::setBeta(double imag)
{
    setItemValue(P_BETA, imag);
}

void MaterialRefractiveDataItem::updateLabel()
{
    setValue(QString("(1 - %1, %2)").arg(delta()).arg(beta()));
}

// ------------------------------------------------------------------------------------------------

MaterialSLDDataItem::MaterialSLDDataItem()
    : MaterialDataItem(Constants::MaterialSLDDataType)
{

}
