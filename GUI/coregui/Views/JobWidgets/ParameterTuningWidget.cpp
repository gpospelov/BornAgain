// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/ParameterTuningWidget.cpp
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
#include "JobQueueData.h"
#include "JobItem.h"
#include "SliderSettingsWidget.h"
#include "ParameterModelBuilder.h"
#include "GUIHelpers.h"
#include "ParameterTuningDelegate.h"
#include "JobModel.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "IntensityDataItem.h"
#include "DesignerHelper.h"
#include "WarningSignWidget.h"
#include "ParameterTuningModel.h"
#include "FitTools.h"
#include "ParameterTreeItems.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QToolButton>
#include <QDebug>
#include <QScrollBar>
#include <QApplication>
#include <QKeyEvent>
#include <QItemSelectionModel>

namespace {
const int warning_sign_xpos = 38;
const int warning_sign_ypos = 38;
}

ParameterTuningWidget::ParameterTuningWidget(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_jobModel(jobModel)
    , m_currentJobItem(0)
    , m_sliderSettingsWidget(0)
    , m_delegate(new ParameterTuningDelegate)
    , m_warningSign(0)
//    , m_mapper(0)
    , m_fitTools(new FitTools(jobModel, parent))
{
//    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_sliderSettingsWidget = new SliderSettingsWidget();
    connect(m_sliderSettingsWidget, SIGNAL(sliderRangeFactorChanged(double)), this, SLOT(onSliderValueChanged(double)));
    connect(m_sliderSettingsWidget, SIGNAL(lockzChanged(bool)), this, SLOT(onLockZValueChanged(bool)));

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
    m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(m_delegate, SIGNAL(currentLinkChanged(SessionItem*)), this, SLOT(onCurrentLinkChanged(SessionItem*)));
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_treeView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenuRequested(const QPoint &)));

    m_treeView->setDragEnabled(true);
    m_treeView->setDragDropMode(QAbstractItemView::DragOnly);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    // assembling all together
    mainLayout->addWidget(m_sliderSettingsWidget);
    mainLayout->addWidget(m_treeView);
    mainLayout->addWidget(m_fitTools);

    setLayout(mainLayout);
}

ParameterTuningWidget::~ParameterTuningWidget()
{
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

        updateParameterModel();

        m_currentJobItem->mapper()->setOnPropertyChange(
                [this](const QString &name)
        {
            onPropertyChanged(name);
        }, this);

        m_fitTools->setCurrentItem(m_currentJobItem, m_treeView->selectionModel());
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
        QModelIndex index = ParameterTuningModel::toSourceIndex(proxyIndex);
        if(index.column() != 0)
            continue;

        if (ParameterItem *parameterItem
            = dynamic_cast<ParameterItem *>(m_currentJobItem->model()->itemForIndex(index))) {
            result.push_back(parameterItem);
        }
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
        m_jobModel->getJobQueueData()->runJob(m_currentJobItem);
    }
}

void ParameterTuningWidget::onSliderValueChanged(double value)
{
    m_delegate->setSliderRangeFactor(value);
}

void ParameterTuningWidget::onLockZValueChanged(bool value)
{
    if(!m_currentJobItem) return;
    if(IntensityDataItem *intensityDataItem = m_currentJobItem->getIntensityDataItem()) {
        qDebug() << "ModelTuningWidget::onLockZValueChanged(bool value) ->" << value;
        intensityDataItem->setZAxisLocked(value);
    }
}

void ParameterTuningWidget::updateParameterModel()
{
    qDebug() << "ModelTuningWidget::updateParameterModel()";

    if(!m_currentJobItem) return;

    if(!m_currentJobItem->getMultiLayerItem() || !m_currentJobItem->getInstrumentItem())
        throw GUIHelpers::Error("ModelTuningWidget::updateParameterModel() -> Error."
                                "JobItem doesn't have sample or instrument model.");

    ParameterTuningModel *parameterModel = new ParameterTuningModel(this);
    parameterModel->setSourceModel(m_jobModel);
    m_treeView->setModel(parameterModel);
    m_treeView->setRootIndex(parameterModel->mapFromSource(m_currentJobItem->getItem(JobItem::T_PARAMETER_TREE)->index()));
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
    Q_ASSERT(m_currentJobItem);

    if(m_currentJobItem->isRunning())
        return;

    m_jobModel->restore(m_currentJobItem);

//    updateParameterModel();

    m_jobModel->getJobQueueData()->runJob(m_currentJobItem);
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

