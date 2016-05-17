// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FilterPropertyProxy.h
//! @brief     Declares class FilterPropertyProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#ifndef FILTERPROPERTYPROXY_H
#define FILTERPROPERTYPROXY_H

#include "WinDllMacros.h"

#include <QSortFilterProxyModel>

class BA_CORE_API_ FilterPropertyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterPropertyProxy(int columns, QObject *parent = 0) : QSortFilterProxyModel(parent)
        , m_columns(columns) {}
    int columnCount(const QModelIndex &parent) const;

    static QModelIndex toSourceIndex(QModelIndex index);

//    QMimeData *mimeData(const QModelIndexList &indexes) const;

//    QStringList mimeTypes() const Q_DECL_OVERRIDE;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    int m_columns;
};

#endif
