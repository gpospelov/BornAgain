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

#ifndef OBSOLETEFITPARAMETERWIDGET_H
#define OBSOLETEFITPARAMETERWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QTableWidget>

#include "ObsoleteFitProxyModel.h"
#include "ObsoleteFitModel.h"

class ObsoleteFitModel;



class BA_CORE_API_ ObsoleteFitParameterWidget : public QWidget
{
    Q_OBJECT

public:
    ObsoleteFitParameterWidget(ObsoleteFitProxyModel *fitProxyModel, QWidget *parent = 0);

private:
    ObsoleteFitModel *m_fitModel;
    QStandardItemModel *m_parameterModel;
    QTreeView *m_treeView;
    ObsoleteFitProxyModel *m_fitProxyModel;


    QStandardItemModel *createParameterModel(ObsoleteFitModel *fitModel);
    QStandardItemModel *iterateSessionModel(ObsoleteFitModel *fitModel, const QModelIndex &parentIndex = QModelIndex(), QStandardItemModel *parentItem = 0);
    void insertRowIntoItem(QStandardItemModel *parentItem, QString title, QVariant value, QVariant min, QVariant max, QVariant isUse);


    void initFitModel();
};

#endif
