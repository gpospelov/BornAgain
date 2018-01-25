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

const QString MaterialRefractiveDataItem::P_REAL = "real";
const QString MaterialRefractiveDataItem::P_IMAG = "imag";

MaterialRefractiveDataItem::MaterialRefractiveDataItem()
    : MaterialDataItem(Constants::MaterialRefractiveDataType)
{
    addProperty(P_REAL, 0.0)->setEditorType(Constants::ScientificEditorType)
        .setLimits(RealLimits::limitless());
    addProperty(P_IMAG, 0.0)->setEditorType(Constants::ScientificEditorType)
        .setLimits(RealLimits::limitless());

    mapper()->setOnPropertyChange([this](const QString&) { updateLabel(); });

    updateLabel();
    setEditable(false); // for label
}

double MaterialRefractiveDataItem::real() const
{
    return getItemValue(P_REAL).toDouble();
}

void MaterialRefractiveDataItem::setReal(double real)
{
    setItemValue(P_REAL, real);
}

double MaterialRefractiveDataItem::imag() const
{
    return getItemValue(P_IMAG).toDouble();
}

void MaterialRefractiveDataItem::setImag(double imag)
{
    setItemValue(P_IMAG, imag);
}

void MaterialRefractiveDataItem::updateLabel()
{
    setValue(QString("(1 - %1, %2)").arg(real()).arg(imag()));
}

// ------------------------------------------------------------------------------------------------

MaterialSLDDataItem::MaterialSLDDataItem()
    : MaterialDataItem(Constants::MaterialSLDDataType)
{

}
