// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidgetOld.h
//! @brief     Defines class FitParameterWidgetOld
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FitParameterWidgetOld_H
#define FitParameterWidgetOld_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QTableWidget>

#include "FitProxyModel.h"
#include "FitModel.h"

class FitModel;



class BA_CORE_API_ FitParameterWidgetOld : public QWidget
{
    Q_OBJECT

public:
    FitParameterWidgetOld(FitProxyModel *fitProxyModel, QWidget *parent = 0);

private:
    FitModel *m_fitModel;
    QStandardItemModel *m_parameterModel;
    QTreeView *m_treeView;
    FitProxyModel *m_fitProxyModel;


    QStandardItemModel *createParameterModel(FitModel *fitModel);
    QStandardItemModel *iterateSessionModel(FitModel *fitModel, const QModelIndex &parentIndex = QModelIndex(), QStandardItemModel *parentItem = 0);
    void insertRowIntoItem(QStandardItemModel *parentItem, QString title, QVariant value, QVariant min, QVariant max, QVariant isUse);


    void initFitModel();
};

#endif
