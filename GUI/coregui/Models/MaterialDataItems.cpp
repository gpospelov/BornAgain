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

const QString MaterialDataItem::P_REAL = "real";
const QString MaterialDataItem::P_IMAG = "imag";

MaterialDataItem::MaterialDataItem(const QString& modelType)
    : SessionItem(modelType)
{
    addProperty(P_REAL, 0.0)->setEditorType(Constants::ScientificEditorType)
        .setLimits(RealLimits::limitless());
    addProperty(P_IMAG, 0.0)->setEditorType(Constants::ScientificEditorType)
        .setLimits(RealLimits::limitless());

    mapper()->setOnPropertyChange([this](const QString&) { updateLabel(); });

    updateLabel();
    setEditable(false);
}

double MaterialDataItem::getReal() const
{
    return getItemValue(P_REAL).toDouble();
}

void MaterialDataItem::setReal(double real)
{
    setItemValue(P_REAL, real);
}

double MaterialDataItem::getImag() const
{
    return getItemValue(P_IMAG).toDouble();
}

void MaterialDataItem::setImag(double imag)
{
    setItemValue(P_IMAG, imag);
}

void MaterialDataItem::updateLabel()
{
    setValue(QString("(1 - %1, %2)").arg(getReal()).arg(getImag()));
}

MaterialRefractiveDataItem::MaterialRefractiveDataItem()
    : MaterialDataItem(Constants::MaterialDataType)
{

}
