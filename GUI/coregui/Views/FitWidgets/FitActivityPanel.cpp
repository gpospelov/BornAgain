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
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>

FitActivityPanel::FitActivityPanel(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_startButton(new QPushButton)
    , m_stopButton(new QPushButton)
    , m_intervalSlider(new QSlider)
    , m_jobModel(0)
    , m_currentItem(0)
    , m_stack(new QStackedWidget(this))
{
    setJobModel(jobModel);

    setWindowTitle(QLatin1String("Fit Panel"));
    setObjectName(QLatin1String("Fit Panel"));

    setMinimumSize(100, 120);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_stack->setMinimumSize(100, 100);
    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_stack);
    mainLayout->addWidget(createRunControlWidget());

    setLayout(mainLayout);
}

void FitActivityPanel::setJobModel(JobModel *jobModel)
{
    Q_ASSERT(jobModel);
    if(jobModel != m_jobModel) {
        if(m_jobModel) {
            disconnect(m_jobModel,
                SIGNAL( selectionChanged(JobItem *) ),
                this,
                SLOT( setItem(JobItem *) )
                );

            disconnect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                    , this, SLOT(onJobItemFinished(QString)));

            disconnect(m_jobModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                    , this, SLOT(onJobItemDelete(JobItem*)));
        }

        m_jobModel = jobModel;

        connect(m_jobModel,
            SIGNAL( selectionChanged(JobItem *) ),
            this,
            SLOT( setItem(JobItem *) )
            );

        connect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                , this, SLOT(onJobItemFinished(QString)));

        connect(m_jobModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                , this, SLOT(onJobItemDelete(JobItem*)));
    }
}

QWidget *FitActivityPanel::createRunControlWidget()
{
    QWidget *result = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    m_startButton->setText("Run Fit");
    m_stopButton->setText("Stop");
    m_intervalSlider->setOrientation(Qt::Horizontal);
    m_intervalSlider->setRange(1,20);
    m_intervalSlider->setMaximumWidth(150);
    m_intervalSlider->setMinimumWidth(150);
    m_intervalSlider->setFocusPolicy(Qt::NoFocus);
    m_intervalSlider->setValue(10);

    layout->addWidget(m_startButton);
    layout->addWidget(m_stopButton);
    layout->addWidget(m_intervalSlider);
    result->setLayout(layout);

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

bool FitActivityPanel::isValidJobItem(JobItem *item)
{
    Q_UNUSED(item);
    return true;
//    return (item->isCompleted() || item->isCanceled()) && item->getMultiLayerItem() && item->getInstrumentItem();
}
