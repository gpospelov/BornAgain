// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ParameterTuningWidget.cpp
//! @brief     Implements class ParameterTuningWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterTuningWidget.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "InstrumentModel.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "JobModel.h"
#include "JobQueueData.h"
#include "ParameterTreeBuilder.h"
#include "ParameterTreeItems.h"
#include "ParameterTuningDelegate.h"
#include "ParameterTuningModel.h"
#include "SampleModel.h"
#include "SliderSettingsWidget.h"
#include "WarningSignWidget.h"
#include <QApplication>
#include <QDebug>
#include <QItemSelectionModel>
#include <QKeyEvent>
#include <QLabel>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QToolButton>
#include <QTreeView>
#include <QVBoxLayout>

namespace {
const int warning_sign_xpos = 38;
const int warning_sign_ypos = 38;
}

ParameterTuningWidget::ParameterTuningWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_currentJobItem(0)
    , m_parameterTuningModel(0)
    , m_sliderSettingsWidget(new SliderSettingsWidget(this))
    , m_delegate(new ParameterTuningDelegate)
    , m_warningSign(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_treeView = new QTreeView();
    m_treeView->setStyleSheet(
        "QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item "
        "{border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:"
        "adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:"
        "!has-children:!has-siblings:adjoins-item {border-image: "
        "url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed"
        ",QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: "
        "url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,"
        "QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: "
        "url(:/images/treeview-branch-open.png);}");

    m_treeView->setItemDelegate(m_delegate);
    //m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setDragDropMode(QAbstractItemView::NoDragDrop);
    m_treeView->setAttribute(Qt::WA_MacShowFocusRect, false);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_sliderSettingsWidget);
    mainLayout->addWidget(m_treeView);
    setLayout(mainLayout);

    connect(m_sliderSettingsWidget, SIGNAL(sliderRangeFactorChanged(double)),
            this, SLOT(onSliderValueChanged(double)));
    connect(m_sliderSettingsWidget, SIGNAL(lockzChanged(bool)),
            this, SLOT(onLockZValueChanged(bool)));
    connect(m_delegate, SIGNAL(currentLinkChanged(SessionItem*)),
            this, SLOT(onCurrentLinkChanged(SessionItem*)));
    connect(m_treeView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenuRequested(const QPoint &)));
}

void ParameterTuningWidget::setItem(JobItem *item)
{
    if (m_currentJobItem == item) {
        return;

    } else {
        if(m_currentJobItem)
            m_currentJobItem->mapper()->unsubscribe(this);

        m_currentJobItem = item;
        if (!m_currentJobItem) return;

        m_jobModel = dynamic_cast<JobModel *>(m_currentJobItem->model());

        updateParameterModel();
        updateDragAndDropSettings();

        m_currentJobItem->mapper()->setOnPropertyChange(
                [this](const QString &name)
        {
            onPropertyChanged(name);
        }, this);

    }
}

QItemSelectionModel *ParameterTuningWidget::selectionModel()
{
    Q_ASSERT(m_treeView);
    return m_treeView->selectionModel();
}

//! Returns list of ParameterItem's currently selected in parameter tree

QVector<ParameterItem *> ParameterTuningWidget::getSelectedParameters()
{
    QVector<ParameterItem *> result;
    QModelIndexList proxyIndexes = selectionModel()->selectedIndexes();
    foreach(QModelIndex proxyIndex, proxyIndexes) {
        if(ParameterItem *parItem = m_parameterTuningModel->getParameterItem(proxyIndex))
            result.push_back(parItem);
    }
    return result;
}

void ParameterTuningWidget::onCurrentLinkChanged(SessionItem *item)
{
    qDebug() << "ModelTuningWidget::onCurrentLinkChanged";
    Q_ASSERT(m_currentJobItem);

    if(m_currentJobItem->isRunning())
        return;

    if (item) {
        qDebug() << "ModelTuningWidget::onCurrentLinkChanged() -> Starting to tune model";
//                 << link.getItem()->modelType() << link.getPropertyName();
//        link.updateItem();
        m_jobModel->runJob(m_currentJobItem->index());
    }
}

void ParameterTuningWidget::onSliderValueChanged(double value)
{
    m_delegate->setSliderRangeFactor(value);
}

void ParameterTuningWidget::onLockZValueChanged(bool value)
{
    if(!m_currentJobItem) return;
    if(IntensityDataItem *intensityDataItem = m_currentJobItem->intensityDataItem()) {
        qDebug() << "ModelTuningWidget::onLockZValueChanged(bool value) ->" << value;
        intensityDataItem->setZAxisLocked(value);
    }
}

void ParameterTuningWidget::updateParameterModel()
{
    Q_ASSERT(m_jobModel);
    qDebug() << "ModelTuningWidget::updateParameterModel()";

    if(!m_currentJobItem) return;

    if(!m_currentJobItem->multiLayerItem() || !m_currentJobItem->instrumentItem())
        throw GUIHelpers::Error("ModelTuningWidget::updateParameterModel() -> Error."
                                "JobItem doesn't have sample or instrument model.");

    delete m_parameterTuningModel;
    m_parameterTuningModel = new ParameterTuningModel(this);
    m_parameterTuningModel->setSourceModel(m_jobModel);

    m_treeView->setModel(m_parameterTuningModel);
    m_treeView->setRootIndex(
        m_parameterTuningModel->mapFromSource(m_currentJobItem->parameterContainerItem()->index()));
    if (m_treeView->columnWidth(0) < 170)
        m_treeView->setColumnWidth(0, 170);
    m_treeView->expandAll();
}

void ParameterTuningWidget::onCustomContextMenuRequested(const QPoint &point)
{
    emit itemContextMenuRequest(m_treeView->mapToGlobal(point+ QPoint(2, 22)));
}

void ParameterTuningWidget::restoreModelsOfCurrentJobItem()
{
    Q_ASSERT(m_jobModel);
    Q_ASSERT(m_currentJobItem);

    if(m_currentJobItem->isRunning())
        return;

    closeActiveEditors();

    m_jobModel->restore(m_currentJobItem);
    m_jobModel->runJob(m_currentJobItem->index());
}

void ParameterTuningWidget::makeSelected(ParameterItem *item)
{
    QModelIndex proxyIndex = m_parameterTuningModel->mapFromSource(item->index());
    if(proxyIndex.isValid()) {
       selectionModel()->select(proxyIndex, QItemSelectionModel::Select);
    }
}

void ParameterTuningWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(m_warningSign) {
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(),pos.y());
    }
    if(m_treeView) {
        m_treeView->setColumnWidth(0, width()*0.5);
    }
}

//! Context menu reimplemented to suppress the default one
void ParameterTuningWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}

void ParameterTuningWidget::onPropertyChanged(const QString &property_name)
{
    if(property_name == JobItem::P_STATUS) {
        delete m_warningSign;
        m_warningSign = 0;

        if(m_currentJobItem->isFailed()) {
            QString message;
            message.append("Current parameter values cause simulation failure.\n\n");
            message.append(m_currentJobItem->getComments());

            m_warningSign = new WarningSignWidget(this);
            m_warningSign->setWarningMessage(message);
            QPoint pos = getPositionForWarningSign();
            m_warningSign->setPosition(pos.x(), pos.y());
            m_warningSign->show();
        }

        updateDragAndDropSettings();
    }
}

//! Returns position for warning sign at the bottom right corner of the tree view.
//! The position will be adjusted according to the visibility of scroll bars
QPoint ParameterTuningWidget::getPositionForWarningSign()
{
    int x = width()-warning_sign_xpos;
    int y = height()-warning_sign_ypos;

    if(QScrollBar *horizontal = m_treeView->horizontalScrollBar()) {
        if(horizontal->isVisible())
            y -= horizontal->height();
    }

    if(QScrollBar *vertical = m_treeView->verticalScrollBar()) {
        if(vertical->isVisible())
            x -= vertical->width();
    }

    return QPoint(x, y);
}

//! Disable drag-and-drop abilities, if job is in fit running state.

void ParameterTuningWidget::updateDragAndDropSettings()
{
    Q_ASSERT(m_currentJobItem);
    if(m_currentJobItem->getStatus() == Constants::STATUS_FITTING) {
        setTuningDelegateEnabled(false);
        m_treeView->setDragDropMode(QAbstractItemView::NoDragDrop);
    } else {
        setTuningDelegateEnabled(true);
        if(m_currentJobItem->isValidForFitting())
            m_treeView->setDragDropMode(QAbstractItemView::DragOnly);
    }
}

//! Sets delegate to enabled/disabled state.
//! In 'disabled' state the delegate is in ReadOnlyMode, if it was containing already some
//! editing widget, it will be forced to close.
void ParameterTuningWidget::setTuningDelegateEnabled(bool enabled)
{
    if(enabled) {
        m_delegate->setReadOnly(false);

    } else {
        m_delegate->setReadOnly(true);
        closeActiveEditors();
    }
}

void ParameterTuningWidget::closeActiveEditors()
{
    QModelIndex index = m_treeView->currentIndex();
    QWidget *editor = m_treeView->indexWidget(index);
    if(editor) {
        //m_delegate->commitData(editor);
        m_delegate->closeEditor(editor, QAbstractItemDelegate::NoHint);
    }
    m_treeView->selectionModel()->clearSelection();
}

