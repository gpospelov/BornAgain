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


SessionModel::SessionModel(QObject *parent)
    : QStandardItemModel(parent)
{
    initialize();
}

SessionModel::~SessionModel()
{

}

QStandardItem *SessionModel::insertNewItem(BA_MODEL_ID::Model_ID model_type, const QModelIndex &index)
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
    m_default_names[BA_MODEL_ID::MultiLayer] = QString("MultiLayer");
    m_default_names[BA_MODEL_ID::Layer] = QString("Layer");
}

QStandardItem *SessionModel::createNewItem(QStandardItem *parent, BA_MODEL_ID::Model_ID model_type)
{
    QString name = m_default_names[model_type];
    ParameterizedItem *new_item = new ParameterizedItem(model_type, name);
    parent->appendRow(new_item);
    return new_item;
}
