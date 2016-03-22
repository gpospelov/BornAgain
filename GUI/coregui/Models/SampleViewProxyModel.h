// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.h
//! @brief     Defines class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef SAMPLEVIEWPROXYMODEL_H
#define SAMPLEVIEWPROXYMODEL_H

#include "WinDllMacros.h"

#include <QSortFilterProxyModel>

class BA_CORE_API_ SampleViewProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SampleViewProxyModel(QObject *parent = 0) : QSortFilterProxyModel(parent) {}
    int columnCount(const QModelIndex &parent) const;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif
