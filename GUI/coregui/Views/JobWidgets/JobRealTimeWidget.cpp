// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobRealTimeWidget.cpp
//! @brief     Implements class JobRealTimeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobRealTimeWidget.h"
#include "JobModel.h"
#include "JobItem.h"
#include "JobQueueData.h"
#include "ParameterTuningWidget.h"
#include "JobRealTimeToolBar.h"
#include "GUIHelpers.h"
#include "mainwindow_constants.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QAction>
#include <QLabel>
#include <QDebug>

JobRealTimeWidget::JobRealTimeWidget(JobModel *jobModel, QWidget *parent)
    : JobPresenter(jobModel, parent)
//    , m_stack(new QStackedWidget(this))
    , m_toolBar(new JobRealTimeToolBar)
    , m_stackedWidget(new ItemStackPresenter<ParameterTuningWidget>)

{
    setWindowTitle(Constants::JobRealTimeWidgetName);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stackedWidget);

    setLayout(mainLayout);

    m_stackedWidget->setModel(jobModel);
    connect(m_toolBar, SIGNAL(resetParameters()), this, SLOT(onResetParameters()));
}

ParameterTuningWidget *JobRealTimeWidget::parameterTuningWidget(JobItem *jobItem)
{
    return m_stackedWidget->itemWidget(jobItem);
}

QSize JobRealTimeWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, 480);
}

QSize JobRealTimeWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

void JobRealTimeWidget::setItem(JobItem * jobItem)
{
    if(!isValidJobItem(jobItem)) {
        m_stackedWidget->hideWidgets();
        return;
    }

    bool isNew(false);
    m_stackedWidget->setItem(jobItem, isNew);

    if(isNew) {
        ParameterTuningWidget *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(jobItem);
    }




    //qDebug() << "JobOutputDataWidget::setItem()";
//    if(!item) return;

//    m_currentItem = item;

//    if(!isVisible()) return;

//    ParameterTuningWidget *widget = m_jobItemToTuningWidget[item];
//    if( !widget && isValidJobItem(item)) {
//        widget = new ParameterTuningWidget(m_jobModel);
//        widget->setItem(item);
//        m_stack->addWidget(widget);
//        m_jobItemToTuningWidget[item] = widget;

//    } else {
//        if( m_stack->currentWidget()) {
//            m_stack->currentWidget()->hide();
//        }
//    }

//    if(widget) {
//        if(widget->isHidden()) {
//            widget->show();
//        }

//        m_stack->setCurrentWidget(widget);
//    }
}

//void JobRealTimeWidget::onJobItemFinished(const QString &identifier)
//{
//    Q_UNUSED(identifier);
////    Q_ASSERT(0);
////    //qDebug() << "JobOutputDataWidget::onJobItemFinished()";
////    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(identifier);

////    if(jobItem == m_currentItem) {
////        if((jobItem->isCompleted() || jobItem->isCanceled()) && jobItem->getIntensityDataItem()) {
////            qDebug() << "JobOutputDataWidget::dataChanged() JobItem::Completed";
////            setItem(jobItem);
////        }
////    }
//}

void JobRealTimeWidget::onResetParameters()
{
    if(auto widget = currentParameterTuningWidget())
        widget->restoreModelsOfCurrentJobItem();
}

void JobRealTimeWidget::updateCurrentItem()
{
    if(!m_currentItem) return;
    setItem(m_currentItem);
}

//void JobRealTimeWidget::onModelLoaded()
//{
//    JobItem *item = dynamic_cast<JobItem*>(m_jobModel->rootItem()->getItem());
//    if (item) {
//        setItem(item);
//    } else {
//        onJobItemDelete(m_currentItem);
//    }
//}

ParameterTuningWidget *JobRealTimeWidget::currentParameterTuningWidget()
{
    return m_stackedWidget->currentWidget();
}

//! Returns true if JobItem is valid for real time simulation.

bool JobRealTimeWidget::isValidJobItem(JobItem *item)
{
    if(!item) return false;
    if(item->isCompleted() || item->isCanceled()) return true;
    return false;
}
