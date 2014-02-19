// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/SessionModel.cpp
//! @brief     Implements class SessionModel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SessionModel.h"
#include "ItemFactory.h"


SessionModel::SessionModel(QObject *parent)
    : QStandardItemModel(parent)
{
    initialize();
}

SessionModel::~SessionModel()
{
}

QStandardItem *SessionModel::insertNewItem(QString model_type, const QModelIndex &index)
{
    QStandardItem *parent;
    if (index.isValid()) {
        parent = itemFromIndex(index);
        if (!parent) {
            return 0;
        }
    }
    else {
        parent = invisibleRootItem();
    }
    return createNewItem(parent, model_type);
}

void SessionModel::initialize()
{
}

QStandardItem *SessionModel::createNewItem(QStandardItem *parent, QString model_type)
{
    ParameterizedItem *new_item = ItemFactory::createItem(model_type);
    if (!new_item) {
        return 0;
    }

    // Check if child is allowed to be added to parent
    if (parent!=invisibleRootItem())
    {
        ParameterizedItem *p_par_parent = dynamic_cast<ParameterizedItem *>(parent);
        if (!p_par_parent || !p_par_parent->acceptsAsChild(new_item)) {
            delete new_item;
            return 0;
        }
    }

    parent->appendRow(new_item);
    return new_item;
}
