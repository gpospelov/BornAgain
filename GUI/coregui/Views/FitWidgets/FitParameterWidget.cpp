// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidget.cpp
//! @brief     Implements class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterWidget.h"
#include "JobItem.h"
#include "JobModel.h"
#include "FitSuiteItem.h"
#include "FitParameterItems.h"
#include "ParameterTuningWidget.h"
#include "FilterPropertyProxy.h"
#include "ParameterTreeItems.h"
#include "FitParameterProxyModel.h"
#include "FitModelHelper.h"
#include "SessionModelDelegate.h"
#include "CustomEventFilters.h"
#include "OverlayLabelController.h"
#include "mainwindow_constants.h"
#include <QMenu>
#include <QSignalMapper>
#include <QTreeView>
#include <QVBoxLayout>
#include <QAction>
#include <QDebug>

FitParameterWidget::FitParameterWidget(QWidget *parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_jobItem(0)
    , m_tuningWidget(0)
    , m_createFitParAction(0)
    , m_removeFromFitParAction(0)
    , m_removeFitParAction(0)
    , m_signalMapper(0)
    , m_fitParameterModel(0)
    , m_delegate(new SessionModelDelegate(this))
    , m_keyboardFilter(new DeleteEventFilter(this))
    , m_infoLabel(new OverlayLabelController(this))
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_treeView);
    setLayout(layout);
    init_actions();

    m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setItemDelegate(m_delegate);
    m_treeView->setDragEnabled(true);
    m_treeView->setDragDropMode(QAbstractItemView::DragDrop);
    m_treeView->installEventFilter(m_keyboardFilter);

    connect(m_treeView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onFitParameterTreeContextMenu(const QPoint &)));

    m_infoLabel->setArea(m_treeView);
    m_infoLabel->setText(QStringLiteral("Drop parameter(s) to fit here"));
}

void FitParameterWidget::setItem(JobItem *jobItem)
{
    if(jobItem == m_jobItem) {
        return;
    }

    else {
        m_jobItem = jobItem;
        if (!m_jobItem) return;

        init_fit_containers();
        init_fit_model();
    }
}

//! Sets ParameterTuningWidget to be able to provide it with context menu and steer
//! it behaviour in the course of fit settings or fit runnig

void FitParameterWidget::setParameterTuningWidget(ParameterTuningWidget *tuningWidget)
{
    if(tuningWidget == m_tuningWidget) {
        return;

    } else {
        if(m_tuningWidget)
            disconnect(m_tuningWidget, SIGNAL(itemContextMenuRequest(QPoint)),
                this, SLOT(onTuningWidgetContextMenu(QPoint)));

        m_tuningWidget = tuningWidget;
        if(!m_tuningWidget) return;

        connect(m_tuningWidget, SIGNAL(itemContextMenuRequest(QPoint)),
            this, SLOT(onTuningWidgetContextMenu(QPoint)), Qt::UniqueConnection);
    }
}

//QSize FitParameterWidget::sizeHint() const
//{
//    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_PARAMETER_WIDGET_HEIGHT);
//}

//QSize FitParameterWidget::minimumSizeHint() const
//{
//    return QSize(25, 25);
//}

//! Creates context menu for ParameterTuningWidget

void FitParameterWidget::onTuningWidgetContextMenu(const QPoint &point)
{
    QMenu menu;
    initTuningWidgetContextMenu(menu);
    menu.exec(point);
    setActionsEnabled(true);
}

//! Creates context menu for the tree with fit parameters

void FitParameterWidget::onFitParameterTreeContextMenu(const QPoint &point)
{
    QMenu menu;
    initFitParameterTreeContextMenu(menu);
    menu.exec(m_treeView->mapToGlobal(point+ QPoint(2, 22)));
    setActionsEnabled(true);
}

void FitParameterWidget::onTuningWidgetSelectionChanged(const QItemSelection &selection)
{
    Q_UNUSED(selection);
}

//! Propagates selection form the tree with fit parameters to the tuning widget

void FitParameterWidget::onFitParametersSelectionChanged(const QItemSelection &selection)
{
    Q_UNUSED(selection);
    qDebug() << "onFitParametersSelectionChanged ->";
    if (selection.indexes().isEmpty())
        return;

    foreach(QModelIndex index, selection.indexes()) {
        m_tuningWidget->selectionModel()->clearSelection();
        SessionItem *item = m_fitParameterModel->itemForIndex(index);
        if(item->parent()->modelType() == Constants::FitParameterLinkType) {
            QString link = item->parent()->getItemValue(FitParameterLinkItem::P_LINK).toString();
            m_tuningWidget->makeSelected(FitModelHelper::getParameterItem(m_jobItem->fitParameterContainerItem(), link));
        }
        qDebug() << "XXX index" << index << item->modelType();

    }

}

//! Creates fit parameters for all selected ParameterItem's in tuning widget

void FitParameterWidget::onCreateFitParAction()
{
    foreach(ParameterItem *item, m_tuningWidget->getSelectedParameters()) {
        if(!FitModelHelper::getFitParameterItem(m_jobItem->fitParameterContainerItem(), item)) {
            FitModelHelper::createFitParameter(m_jobItem->fitParameterContainerItem(), item);
        }
    }
}

//! All ParameterItem's selected in tuning widget will be removed from link section of
//! corresponding fitParameterItem.

void FitParameterWidget::onRemoveFromFitParAction()
{
    foreach(ParameterItem *item, m_tuningWidget->getSelectedParameters()) {
        if(FitModelHelper::getFitParameterItem(m_jobItem->fitParameterContainerItem(), item)) {
            FitModelHelper::removeFromFitParameters(m_jobItem->fitParameterContainerItem(), item);
        }
    }
}

//! All selected FitParameterItem's of FitParameterItemLink's will be removed

void FitParameterWidget::onRemoveFitParAction()
{
    FitParameterContainerItem *container = m_jobItem->fitParameterContainerItem();

    // retrieve both, selected FitParameterItem and FitParameterItemLink
    QVector<FitParameterLinkItem *> linksToRemove = selectedFitParameterLinks();
    QVector<FitParameterItem *> itemsToRemove = selectedFitParameters();

    foreach(FitParameterLinkItem *item, linksToRemove) {
        container->model()->removeRow(item->index().row(), item->index().parent());
    }

    foreach(FitParameterItem *item, itemsToRemove) {
        container->model()->removeRow(item->index().row(), item->index().parent());
    }
}

//! Add all selected parameters to fitParameter with given index

void FitParameterWidget::onAddToFitParAction(int ipar)
{
    QStringList fitParNames
        = FitModelHelper::getFitParameterNames(m_jobItem->fitParameterContainerItem());
    foreach (ParameterItem *item, m_tuningWidget->getSelectedParameters()) {
        FitModelHelper::addToFitParameter(m_jobItem->fitParameterContainerItem(), item,
                                          fitParNames.at(ipar));
    }
}

void FitParameterWidget::onFitParameterModelChange()
{
    qDebug() << "FitParameterWidget::onFitParameterModelChange()";
    spanParameters();
    updateInfoLabel();
}


//! Context menu reimplemented to suppress the default one

void FitParameterWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}

void FitParameterWidget::init_actions()
{
    m_createFitParAction = new QAction(QStringLiteral("Create fit parameter"), this);
    connect(m_createFitParAction, SIGNAL(triggered()), this, SLOT(onCreateFitParAction()));

    m_removeFromFitParAction = new QAction(QStringLiteral("Remove from fit parameters"), this);
    connect(m_removeFromFitParAction, SIGNAL(triggered()), this, SLOT(onRemoveFromFitParAction()));

    m_removeFitParAction = new QAction(QStringLiteral("Remove fit parameter"), this);
    connect(m_removeFitParAction, SIGNAL(triggered()), this, SLOT(onRemoveFitParAction()));

    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(onAddToFitParAction(int)));

    connect(m_keyboardFilter, SIGNAL(removeItem()), this, SLOT(onRemoveFitParAction()));
}

//! Fills context menu for ParameterTuningWidget with content.

void FitParameterWidget::initTuningWidgetContextMenu(QMenu &menu)
{
    m_removeFromFitParAction->setEnabled(canRemoveFromFitParameters());
    m_createFitParAction->setEnabled(canCreateFitParameter());

    menu.addAction(m_createFitParAction);
    QMenu *addToFitParMenu = menu.addMenu("Add to existing fit parameter");

    QStringList fitParNames
        = FitModelHelper::getFitParameterNames(m_jobItem->fitParameterContainerItem());
    if(fitParNames.isEmpty() || canCreateFitParameter()==false) {
        addToFitParMenu->setEnabled(false);
    }

    for(int i =0; i<fitParNames.count(); ++i) {
        QAction *action = new QAction(QString("to ").append(fitParNames.at(i)), addToFitParMenu);
        connect(action, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
        m_signalMapper->setMapping(action, i);
        addToFitParMenu->addAction(action);
    }

    menu.addSeparator();
    menu.addAction(m_removeFromFitParAction);
}

//! Fills context menu for FitParameterTree with content.

void FitParameterWidget::initFitParameterTreeContextMenu(QMenu &menu)
{
    menu.addAction(m_removeFitParAction);
}

//! Initializes FitParameterModel and its tree.

void FitParameterWidget::init_fit_model()
{
    m_treeView->setModel(0);

    delete m_fitParameterModel;
    m_fitParameterModel = new FitParameterProxyModel(m_jobItem->fitParameterContainerItem(),
                                                   m_jobItem->fitParameterContainerItem()->model());
    m_treeView->setModel(m_fitParameterModel);

    connect(m_fitParameterModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(onFitParameterModelChange()));
    connect(m_fitParameterModel, SIGNAL(modelReset()), this, SLOT(onFitParameterModelChange()));

    onFitParameterModelChange();
    connectFitParametersSelection(true);
}

//! Adds to JobItem all fit containers, if necessary.

void FitParameterWidget::init_fit_containers()
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
}

//! Returns true if tuning widget contains selected ParameterItem's which can be used to create
//! a fit parameter (i.e. it is not linked with some fit parameter already).

bool FitParameterWidget::canCreateFitParameter()
{
    QVector<ParameterItem *> selected = m_tuningWidget->getSelectedParameters();
    foreach(ParameterItem *item, selected) {
        if(FitModelHelper::getFitParameterItem(
                    m_jobItem->fitParameterContainerItem(), item) == nullptr)
            return true;
    }
    return false;
}

//! Returns true if tuning widget contains selected ParameterItem's which can be removed from
//! fit parameters.

bool FitParameterWidget::canRemoveFromFitParameters()
{
    QVector<ParameterItem *> selected = m_tuningWidget->getSelectedParameters();
    foreach(ParameterItem *item, selected) {
        if(FitModelHelper::getFitParameterItem(m_jobItem->fitParameterContainerItem(), item))
            return true;
    }
    return false;
}

//! Enables/disables all context menu actions.

void FitParameterWidget::setActionsEnabled(bool value)
{
    m_createFitParAction->setEnabled(value);
    m_removeFromFitParAction->setEnabled(value);
    m_removeFitParAction->setEnabled(value);
}

//! Returns list of FitParameterItem's currently selected in FitParameterItem tree

QVector<FitParameterItem *> FitParameterWidget::selectedFitParameters()
{
    QVector<FitParameterItem *> result;
    QModelIndexList indexes = m_treeView->selectionModel()->selectedIndexes();
    foreach(QModelIndex index, indexes) {
        if(SessionItem *item = m_fitParameterModel->itemForIndex(index)) {
            if(item->modelType() == Constants::FitParameterType) {
                FitParameterItem *fitParItem = dynamic_cast<FitParameterItem *>(item);
                Q_ASSERT(fitParItem);
                result.push_back(fitParItem);
            }
        }
    }
    return result;
}

//! Returns links of FitParameterLink's item selected in FitParameterItem tree

QVector<FitParameterLinkItem *> FitParameterWidget::selectedFitParameterLinks()
{
    QVector<FitParameterLinkItem *> result;
    QModelIndexList indexes = m_treeView->selectionModel()->selectedIndexes();
    foreach (QModelIndex index, indexes) {
        if (SessionItem *item = m_fitParameterModel->itemForIndex(index)) {
            if (item->parent()->modelType() == Constants::FitParameterLinkType) {
                FitParameterLinkItem *fitParItem
                    = dynamic_cast<FitParameterLinkItem *>(item->parent());
                Q_ASSERT(fitParItem);
                result.push_back(fitParItem);
            }
        }
    }
    return result;
}

//! Makes first column in FitParameterItem's tree related to ParameterItem link occupy whole space.

void FitParameterWidget::spanParameters()
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

//! Places overlay label on top of tree view, if there is no fit parameters
void FitParameterWidget::updateInfoLabel()
{
    Q_ASSERT(m_jobItem);
    bool is_to_show_label = m_jobItem->fitParameterContainerItem()->isEmpty();
    m_infoLabel->setShown(is_to_show_label);
}


void FitParameterWidget::connectTuningWidgetSelection(bool active)
{
    Q_ASSERT(m_tuningWidget);

    if (active) {
        connect(m_tuningWidget->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onTuningWidgetSelectionChanged(QItemSelection)), Qt::UniqueConnection);
    } else {
        disconnect(m_tuningWidget->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onTuningWidgetSelectionChanged(QItemSelection)));
    }
}

void FitParameterWidget::connectFitParametersSelection(bool active) {
    if (active) {
        connect(m_treeView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onFitParametersSelectionChanged(QItemSelection)), Qt::UniqueConnection);
    } else {
        disconnect(m_treeView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onFitParametersSelectionChanged(QItemSelection)));
    }
}
