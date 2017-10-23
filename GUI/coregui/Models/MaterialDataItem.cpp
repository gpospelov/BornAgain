// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RefractiveIndexItem.cpp
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

#include "MaterialDataItem.h"

#include "ScientificDoubleProperty.h"


const QString MaterialDataItem::P_REAL = "real";
const QString MaterialDataItem::P_IMAG = "imag";


MaterialDataItem::MaterialDataItem()
    : SessionItem(Constants::MaterialDataType)
{
    ScientificDoubleProperty real(0.0);
    addProperty(P_REAL, real.getVariant());

    ScientificDoubleProperty imag(0.0);
    addProperty(P_IMAG, imag.getVariant());

    mapper()->setOnPropertyChange(
        [this](const QString &){
            setValue(itemLabel());
        }
    );

    setValue(itemLabel());
    setEditable(false);
}

QString MaterialDataItem::itemLabel() const
{
    return QString("(1 - %1, %2)").arg(getReal()).arg(getImag());
}

double MaterialDataItem::getReal() const
{
    return getItemValue(P_REAL).value<ScientificDoubleProperty>().getValue();
}

void MaterialDataItem::setReal(double real)
{
    ScientificDoubleProperty property = getItemValue(P_REAL).value<ScientificDoubleProperty>();
    property.setValue(real);
    setItemValue(P_REAL, property.getVariant());
}

double MaterialDataItem::getImag() const
{
    return getItemValue(P_IMAG).value<ScientificDoubleProperty>().getValue();
}

void MaterialDataItem::setImag(double imag)
{
    ScientificDoubleProperty property = getItemValue(P_IMAG).value<ScientificDoubleProperty>();
    property.setValue(imag);
    setItemValue(P_IMAG, property.getVariant());
}
