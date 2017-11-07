// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyModel.h
//! @brief     Defines class ComponentProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTPROXYMODEL_H
#define COMPONENTPROXYMODEL_H

#include "WinDllMacros.h"
#include <QAbstractProxyModel>

class SessionModel;

//! Proxy model to adjust SessionModel for component editor (right bottom corner of SampleView
//! and similar).
//! The model hides all SessionItems which are not PropertyItems.
//! The model hides GroupPropertyItem children and shows grand-children of currently selected item
//! one level up.

class BA_CORE_API_ ComponentProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    ComponentProxyModel(QObject* parent = nullptr);

    void setSessionModel(SessionModel* model);

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    SessionModel* m_model;
};

#endif  // COMPONENTPROXYMODEL_H

