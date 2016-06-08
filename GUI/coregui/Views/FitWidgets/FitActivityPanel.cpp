// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitActivityPanel.h
//! @brief     Implements class FitActivityPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitActivityPanel.h"
#include "JobModel.h"
#include "JobItem.h"
#include "JobQueueData.h"
#include "FitSuiteWidget.h"
#include "JobRealTimeWidget.h"
#include "mainwindow_constants.h"
#include "RunFitControlWidget.h"
#include <QStackedWidget>
#include <QVBoxLayout>

FitActivityPanel::FitActivityPanel(JobModel *jobModel, QWidget *parent)
    : JobPresenter(jobModel, parent)
    , m_stackedWidget(new ItemStackPresenter<FitSuiteWidget>)
//    , m_stack(new QStackedWidget(this))
    , m_controlWidget(new RunFitControlWidget(this))
    , m_realTimeWidget(0)
{
    setWindowTitle(Constants::JobFitPanelName);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_stackedWidget);
    mainLayout->addWidget(m_controlWidget);

    setLayout(mainLayout);

    connect(m_controlWidget, SIGNAL(startFitting()), this, SLOT(onStartFitting()));
    connect(m_controlWidget, SIGNAL(stopFitting()), this, SLOT(onStopFitting()));
}

void FitActivityPanel::setRealTimeWidget(JobRealTimeWidget *realTimeWidget)
{
    m_realTimeWidget = realTimeWidget;
}

QSize FitActivityPanel::sizeHint() const {
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, 240);
}

QSize FitActivityPanel::minimumSizeHint() const {
    return QSize(100, 100);
}

void FitActivityPanel::setItem(JobItem *item)
{
    qDebug() << "FitActivityPanel::setItem(JobItem *item)" << item->isValidForFitting();
    if(!item->isValidForFitting()) {
        m_stackedWidget->hideWidgets();
        return;
    }

    m_controlWidget->setItem(item);

    m_currentItem = item;

    if(!isVisible()) return;

    bool isNew(false);
    m_stackedWidget->setItem(item, isNew);

    if(isNew) {
        FitSuiteWidget *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(item);
        widget->setModelTuningWidget(m_realTimeWidget->getTuningWidgetForItem(item));
        connect(widget, SIGNAL(fittingStarted()), m_controlWidget,
                SLOT(onFittingStarted()), Qt::UniqueConnection);
        connect(widget, SIGNAL(fittingFinished()), m_controlWidget,
                SLOT(onFittingFinished()), Qt::UniqueConnection);
        connect(widget, SIGNAL(fittingError(QString)), m_controlWidget,
                SLOT(onFittingError(QString)), Qt::UniqueConnection);
    }
}

void FitActivityPanel::onJobItemDelete(JobItem *item)
{
    Q_UNUSED(item);
    return;
}

void FitActivityPanel::onJobItemFinished(const QString &identifier)
{
    Q_UNUSED(identifier);
    return;
}

void FitActivityPanel::updateCurrentItem()
{
    if(!m_currentItem) return;
    setItem(m_currentItem);
}

void FitActivityPanel::onStartFitting()
{
    if(FitSuiteWidget *widget = currentFitSuiteWidget()) {
        widget->startFitting();
    }
}

void FitActivityPanel::onStopFitting()
{
    if(FitSuiteWidget *widget = currentFitSuiteWidget()) {
        widget->stopFitting();
    }
}

bool FitActivityPanel::isValidJobItem(JobItem *item)
{
    Q_UNUSED(item);
    return item->isValidForFitting();
    //    return (item->isCompleted() || item->isCanceled()) && item->getMultiLayerItem() && item->getInstrumentItem();
}

FitSuiteWidget *FitActivityPanel::currentFitSuiteWidget()
{
    return m_stackedWidget->currentWidget();
}
