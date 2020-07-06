// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DocumentModel.h
//! @brief     Defines class DocumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include "GUI/coregui/Models/SessionModel.h"

class SimulationOptionsItem;

//! The DocumentModel class is a model with GUI settings related to the opened project.
//! Can be the place to store splitter position, etc.

class BA_CORE_API_ DocumentModel : public SessionModel
{
    Q_OBJECT

public:
    explicit DocumentModel(QObject* parent = nullptr);

    SimulationOptionsItem* simulationOptionsItem();
};

#endif // DOCUMENTMODEL_H
