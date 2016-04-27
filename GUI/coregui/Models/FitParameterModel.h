// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterModel.h
//! @brief     Declares class FitParameterModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERMODEL_H
#define FITPARAMETERMODEL_H

#include "WinDllMacros.h"
#include "SessionModel.h"
#include <QMap>

class ParameterItem;
class FitParameterItem;
class FitParameterContainerItem;

//! The FitParameterModel adopt fit parameters from FitParameterContainer to be shown
//! in 5 column tree view. It doesn't own its root item (it still belongs to the original JobModel)
//! and serves merely as a proxy model. Any changes should be done via original model
//! accessible via rootItem->model()

class BA_CORE_API_ FitParameterModel : public SessionModel
{
    Q_OBJECT

public:
    explicit FitParameterModel(SessionItem *fitParContainer, QObject *parent = 0);
    ~FitParameterModel();

    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;

    void createFitParameter(ParameterItem *parameterItem = 0);
    void removeFromFitParameters(ParameterItem *parameterItem);
    void addToFitParameter(ParameterItem *parameterItem, const QString &fitParName);

    FitParameterItem *getFitParameterItem(ParameterItem *parameterItem);

    FitParameterContainerItem *getFitParContainer();

    QStringList getFitParameterNames();

private:
    QMap<int, QString> m_columnNames;
};



#endif
