// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DocumentModel.h
//! @brief     Defines class DocumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include "SessionModel.h"

class SimulationOptionsItem;

class BA_CORE_API_ DocumentModel : public SessionModel
{
    Q_OBJECT

public:
    explicit DocumentModel(QObject *parent = 0);

    SimulationOptionsItem *getSimulationOptionsItem();

};

#endif
