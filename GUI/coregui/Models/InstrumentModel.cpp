// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/InstrumentModel.cpp
//! @brief     Implements class InstrumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InstrumentModel.h"
#include "InstrumentItem.h"

InstrumentModel::InstrumentModel(QObject *parent)
    : SessionModel(SessionXML::InstrumentModelTag, parent)
{
    setObjectName(SessionXML::InstrumentModelTag);
}


InstrumentModel *InstrumentModel::createCopy(SessionItem *parent)
{
    InstrumentModel *result = new InstrumentModel();
    result->initFrom(this, parent);
    return result;
}


//! returns list of Instruments defined in the model
QMap<QString, SessionItem *> InstrumentModel::getInstrumentMap() const
{
    return getTopItemMap(Constants::InstrumentType);
}


InstrumentItem *InstrumentModel::getInstrumentItem(const QString &instrument_name)
{
    return dynamic_cast<InstrumentItem *>(getTopItem(Constants::InstrumentType, instrument_name));
}

