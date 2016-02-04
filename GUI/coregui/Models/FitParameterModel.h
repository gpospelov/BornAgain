// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitModel.h
//! @brief     Defines class FitModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERMODEL_H
#define FITPARAMETERMODEL_H

#include "WinDllMacros.h"
#include "SessionModel.h"
#include <QMap>

class FitModel;
class QModelIndex;
class QParameterizedItem;


class BA_CORE_API_ FitParameterModel : public SessionModel
{
    Q_OBJECT

public:
    explicit FitParameterModel(FitModel *fitmodel, QWidget *parent);
    ~FitParameterModel();
    QModelIndex itemForLink(const QString &link) const;

    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                             const QModelIndex &parent) const Q_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;

public slots:
    ParameterizedItem *addParameter();

private:
    QMap<int, QString> *m_columnNames;
};



#endif
