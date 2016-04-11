// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DocumentModel.cpp
//! @brief     Implements class DocumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DocumentModel.h"
#include "SimulationOptionsItem.h"

DocumentModel::DocumentModel(QObject *parent)
    : SessionModel(SessionXML::DocumentModelTag, parent)
{
    setObjectName(SessionXML::DocumentModelTag);
}

SimulationOptionsItem *DocumentModel::getSimulationOptionsItem()
{
    return dynamic_cast<SimulationOptionsItem *>(getTopItem(Constants::SimulationOptionsType));

}
