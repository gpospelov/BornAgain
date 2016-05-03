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
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>

FitActivityPanel::FitActivityPanel(JobModel *jobModel, QWidget *parent)
    : JobPresenter(jobModel, parent)
    , m_startButton(new QPushButton)
    , m_stopButton(new QPushButton)
    , m_intervalSlider(new QSlider)
    , m_stack(new QStackedWidget(this))
    , m_realTimeWidget(0)
{
    setWindowTitle(QLatin1String("Fit Panel"));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

//    m_stack->setMinimumSize(100, 100);
//    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_stack);
    mainLayout->addWidget(createRunControlWidget());

    setLayout(mainLayout);
}

void FitActivityPanel::setRealTimeWidget(JobRealTimeWidget *realTimeWidget)
{
    m_realTimeWidget = realTimeWidget;
}

QWidget *FitActivityPanel::createRunControlWidget()
{
    QWidget *result = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    m_startButton->setText("Run");
    m_startButton->setToolTip("Run fitting");
    m_startButton->setMaximumWidth(70);
//    m_startButton->setMinimumHeight(50);

    m_stopButton->setText("Stop");
    m_stopButton->setToolTip("Interrupt fitting");

    m_intervalSlider->setOrientation(Qt::Horizontal);
    m_intervalSlider->setRange(1,20);
    m_intervalSlider->setMaximumWidth(150);
    m_intervalSlider->setMinimumWidth(150);
    m_intervalSlider->setFocusPolicy(Qt::NoFocus);
    m_intervalSlider->setValue(10);

    layout->addWidget(m_startButton);
    layout->addWidget(m_stopButton);
    layout->addWidget(m_intervalSlider);
    layout->addStretch();
    result->setLayout(layout);

    connect(m_startButton, SIGNAL(clicked(bool)), this, SLOT(onStartClick()));
    connect(m_stopButton, SIGNAL(clicked(bool)), this, SLOT(onStopClicked()));

    return result;
}

void FitActivityPanel::setItem(JobItem *item)
{
    if(!item) return;

    m_currentItem = item;

    if(!isVisible()) return;

    FitSuiteWidget *widget = m_jobItemToFitWidget[item];
    if( !widget && isValidJobItem(item)) {
        widget = new FitSuiteWidget(m_jobModel);
        widget->setItem(item);
        widget->setModelTuningWidget(m_realTimeWidget->getTuningWidgetForItem(item));

        connect(widget, SIGNAL(fittingStarted()), this, SLOT(onFittingStarted()));
        connect(widget, SIGNAL(fittingFinished()), this, SLOT(onFittingFinished()));


        m_stack->addWidget(widget);
        m_jobItemToFitWidget[item] = widget;

    } else {
        if( m_stack->currentWidget()) {
            m_stack->currentWidget()->hide();
        }
    }

    if(widget) {
        if(widget->isHidden()) {
            widget->show();
        }

        m_stack->setCurrentWidget(widget);
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

void FitActivityPanel::onStartClick()
{
    if(FitSuiteWidget *widget = getCurrentFitSuiteWidget()) {
        widget->startFitting();
    }
}

void FitActivityPanel::onStopClicked()
{
    if(FitSuiteWidget *widget = getCurrentFitSuiteWidget()) {
        widget->stopFitting();
    }
}

void FitActivityPanel::onFittingStarted()
{
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
}

void FitActivityPanel::onFittingFinished()
{
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
}

bool FitActivityPanel::isValidJobItem(JobItem *item)
{
    Q_UNUSED(item);
    return true;
    //    return (item->isCompleted() || item->isCanceled()) && item->getMultiLayerItem() && item->getInstrumentItem();
}

FitSuiteWidget *FitActivityPanel::getCurrentFitSuiteWidget()
{
    FitSuiteWidget *result = dynamic_cast<FitSuiteWidget *>(m_stack->currentWidget());
    if(result && result->isHidden()) result = 0;
    return result;
}
