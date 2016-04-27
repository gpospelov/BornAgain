// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParametersWidget.cpp
//! @brief     Implements class FitParametersWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParametersWidget.h"
#include "JobItem.h"
#include "JobModel.h"
#include "FitSuiteItem.h"
#include "FitParameterItems.h"
#include "FitParameterModel.h"
#include "ModelTuningWidget.h"
#include "FilterPropertyProxy.h"
#include "ParameterTreeItems.h"
#include <QMenu>
#include <QTreeView>
#include <QVBoxLayout>
#include <QAction>
#include <QDebug>

FitParametersWidget::FitParametersWidget(QWidget *parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_jobItem(0)
    , m_tuningWidget(0)
    , m_createFitParAction(0)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_treeView);
    setLayout(layout);
    init_actions();
}

FitParametersWidget::~FitParametersWidget()
{

}

void FitParametersWidget::setItem(JobItem *jobItem)
{
    if(jobItem == m_jobItem) {
        return;
    }

    else {
        if(m_jobItem)
            stop_tracking_job_item();

        m_jobItem = jobItem;
        if (!m_jobItem) return;

        init_job_item();

    }
}

//! Our FitParametersWidget will provide model tuning widget with context menu.
//! It also will take care of cross-item-selection between parameterTuningTree
//! and fitParametersTree
void FitParametersWidget::setModelTuningWidget(ModelTuningWidget *tuningWidget)
{
    if(tuningWidget == m_tuningWidget) {
        return;
    }

    else {
        if(m_tuningWidget) {
            disconnect(m_tuningWidget,
                SIGNAL(itemContextMenuRequest(QPoint)),
                this,
                SLOT(onTuningWidgetContextMenu(QPoint)));
        }

        m_tuningWidget = tuningWidget;
        if(!m_tuningWidget) return;

        connect(m_tuningWidget,
            SIGNAL(itemContextMenuRequest(QPoint)),
            this,
            SLOT(onTuningWidgetContextMenu(QPoint)), Qt::UniqueConnection);

    }

}

void FitParametersWidget::onTuningWidgetContextMenu(const QPoint &point)
{
    QMenu menu;
    initTuningWidgetContextMenu(menu);
    menu.exec(point);
}

void FitParametersWidget::onCreateFitParAction()
{
    Q_ASSERT(m_jobItem);
    Q_ASSERT(m_tuningWidget);
    Q_ASSERT(m_tuningWidget->selectionModel());
    QModelIndexList proxyIndexes = m_tuningWidget->selectionModel()->selectedIndexes();
    foreach(QModelIndex proxyIndex, proxyIndexes) {
        QModelIndex index = FilterPropertyProxy::toSourceIndex(proxyIndex);
        qDebug() << proxyIndex << index << index.column();
        if(index.column() != 0) continue;

        if(SessionItem *item = m_jobItem->model()->itemForIndex(index)) {
            if(ParameterItem *parameterItem = dynamic_cast<ParameterItem *>(item)) {
                qDebug() << item->modelType() << item->displayName() << item->parent()->modelType() << item->getItemValue(ParameterItem::P_LINK);
                m_fitParameterModel->createFitParameter(parameterItem);
//                if(FitParameterItem *fitPar = dynamic_cast<FitParameterItem *>(item->parent())) {
//                    qDebug() << item->modelType() << item->displayName() << fitPar->modelType();
//                }
            }
        }

    }
    spanParameters();


//    QModelIndex index = indexes.front();
//    if(SessionItem *item = m_jobItem->model()->itemForIndex(index)) {
//        qDebug() << item->modelType();
//    }

}

void FitParametersWidget::init_actions()
{
    m_createFitParAction = new QAction(QStringLiteral("Create fit parameter"), this);
    connect(m_createFitParAction, SIGNAL(triggered()), this, SLOT(onCreateFitParAction()));

}

void FitParametersWidget::initTuningWidgetContextMenu(QMenu &menu)
{
    Q_ASSERT(m_jobItem);
    menu.addAction(m_createFitParAction);
}

//! stop tracking job item
void FitParametersWidget::stop_tracking_job_item()
{
    Q_ASSERT(m_jobItem);

}

//! init job item: create fit containers if necessary, subscribes for item changing
void FitParametersWidget::init_job_item()
{
    SessionItem *fitSuiteItem = m_jobItem->getItem(JobItem::T_FIT_SUITE);
    if (!fitSuiteItem) {
        fitSuiteItem = m_jobItem->model()->insertNewItem(
            Constants::FitSuiteType, m_jobItem->index(), -1, JobItem::T_FIT_SUITE);
    }
    Q_ASSERT(fitSuiteItem);

    SessionItem *parsContainerItem = fitSuiteItem->getItem(FitSuiteItem::T_FIT_PARAMETERS);
    if (!parsContainerItem) {
        parsContainerItem = fitSuiteItem->model()->insertNewItem(
            Constants::FitParameterContainerType, fitSuiteItem->index(), -1,
            FitSuiteItem::T_FIT_PARAMETERS);
    }

//    SessionItem *fitPar = parsContainerItem->model()->insertNewItem(Constants::FitParameterType,
//                                                                    parsContainerItem->index());

//    Q_ASSERT(fitPar);
//    SessionItem *link1 = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
//    link1->setItemValue(FitParameterLinkItem::P_LINK, "abc1");
//    SessionItem *link2 = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
//    link2->setItemValue(FitParameterLinkItem::P_LINK, "xyz1");

    m_fitParameterModel.reset(new FitParameterModel(parsContainerItem));
    m_treeView->setModel(m_fitParameterModel.get());

    m_fitParameterModel->createFitParameter();
    m_fitParameterModel->createFitParameter();
//    spanParameters();


//        m_treeView->setModel(parsContainerItem->model());
//        m_treeView->setRootIndex(parsContainerItem->index());

}

//! Make first column in FitParameterItem's link occupy whole space
void FitParametersWidget::spanParameters()
{
    m_treeView->expandAll();
    for (int i = 0; i < m_fitParameterModel->rowCount(QModelIndex()); i++){
        QModelIndex parameter = m_fitParameterModel->index(i,0,QModelIndex());
        if (!parameter.isValid())
            break;
        int childRowCount = m_fitParameterModel->rowCount(parameter);
        if (childRowCount > 0){
            for (int j = 0; j < childRowCount; j++) {
                m_treeView->setFirstColumnSpanned(j, parameter, true);
            }
        }
    }

}
