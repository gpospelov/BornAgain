// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/RunFitControlWidget.cpp
//! @brief     Implements class RunFitControlWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RunFitControlWidget.h"
#include "DesignerHelper.h"
#include "FitSuiteItem.h"
#include "JobItem.h"
#include "JobMessagePanel.h"
#include "WarningSign.h"
#include "mainwindow_constants.h"
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

namespace {
const int default_update_interval = 10;
const std::vector<int> slider_to_interval = {1,2,3,4,5,10,15,20,25,30,50,100,200,500,1000};
const QString slider_tooltip = "Updates fit progress every Nth iteration";
}

RunFitControlWidget::RunFitControlWidget(QWidget *parent)
    : QWidget(parent)
    , m_startButton(new QPushButton)
    , m_stopButton(new QPushButton)
    , m_intervalSlider(new QSlider)
    , m_updateIntervalLabel(new QLabel("25"))
    , m_iterationsCountLabel(new QLabel)
    , m_currentItem(0)
    , m_warningSign(new WarningSign(this))
    , m_jobMessagePanel(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(Constants::RUN_FIT_CONTROL_WIDGET_HEIGHT);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);

    m_startButton->setText("Run");
    m_startButton->setToolTip("Run fitting");
    m_startButton->setMaximumWidth(80);
//    m_startButton->setMinimumHeight(50);

    m_stopButton->setText("Stop");
    m_stopButton->setToolTip("Interrupt fitting");
    m_stopButton->setMaximumWidth(80);
//    m_stopButton->setEnabled(false);

    m_intervalSlider->setToolTip(slider_tooltip);
    m_intervalSlider->setOrientation(Qt::Horizontal);
    m_intervalSlider->setRange(0, static_cast<int>(slider_to_interval.size())-1);
    m_intervalSlider->setMaximumWidth(120);
    m_intervalSlider->setMinimumWidth(120);
    m_intervalSlider->setFocusPolicy(Qt::NoFocus);
    m_intervalSlider->setValue(5);

    QFont font("Monospace", DesignerHelper::getLabelFontSize(), QFont::Normal);
    font.setPointSize(DesignerHelper::getPortFontSize());
    m_updateIntervalLabel->setToolTip(slider_tooltip);
    m_updateIntervalLabel->setFont(font);
    m_updateIntervalLabel->setText(QString::number(sliderUpdateInterval()));

    layout->addWidget(m_startButton);
    layout->addSpacing(5);
    layout->addWidget(m_stopButton);
    layout->addSpacing(5);
    layout->addWidget(m_intervalSlider);
    layout->addSpacing(2);
    layout->addWidget(m_updateIntervalLabel);
    layout->addSpacing(5);
    layout->addStretch();
    layout->addWidget(m_iterationsCountLabel);
    setLayout(layout);

    connect(m_startButton, SIGNAL(clicked(bool)), this, SIGNAL(startFittingPushed()));
    connect(m_stopButton, SIGNAL(clicked(bool)), this, SIGNAL(stopFittingPushed()));
    connect(m_intervalSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));

    setEnabled(false);
}

void RunFitControlWidget::setJobMessagePanel(JobMessagePanel *jobMessagePanel)
{
    m_jobMessagePanel = jobMessagePanel;
}

void RunFitControlWidget::onFittingStarted(JobItem *jobItem)
{
    m_currentItem = jobItem;
    m_warningSign->clear();
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);

    Q_ASSERT(fitSuiteItem());

    fitSuiteItem()->setItemValue(FitSuiteItem::P_UPDATE_INTERVAL, sliderUpdateInterval());

    fitSuiteItem()->mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        onFitSuitePropertyChange(name);
    }, this);

    onFitSuitePropertyChange(FitSuiteItem::P_ITERATION_COUNT);

    Q_ASSERT(m_jobMessagePanel);
    m_jobMessagePanel->onClearLog();
}

void RunFitControlWidget::onFittingFinished(JobItem *jobItem)
{
    Q_ASSERT(jobItem = m_currentItem);

    if(jobItem->isCompleted())
        m_jobMessagePanel->onMessage(QStringLiteral("Done"), QColor(Qt::darkBlue));

    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
    fitSuiteItem()->mapper()->unsubscribe(this);
    m_currentItem = 0;
}

void RunFitControlWidget::onFittingError(const QString &what)
{
    m_warningSign->clear();
    m_iterationsCountLabel->setText("");

    QString message;
    message.append("Current settings cause fitting failure.\n\n");
    message.append(what);
    m_warningSign->setWarningMessage(message);
    m_jobMessagePanel->onMessage(message, QColor(Qt::darkRed));
}

void RunFitControlWidget::onFittingLog(const QString &text)
{
    Q_ASSERT(m_jobMessagePanel);
    m_jobMessagePanel->onMessage(text);
}

void RunFitControlWidget::setItem(JobItem *item)
{
    Q_UNUSED(item);
    // If item is not suitable for fitting, disable widget
    if(!isValidJobItem(item)) {
        setEnabled(false);
        return;
    }

    // if item is ready for fitting, or already has fitting running, enable widget
    if(m_currentItem == 0 || m_currentItem == item) {
        setEnabled(true);
        return;
    }

    // it's not possible to run new fitting if old is running
    setEnabled(false);
}

void RunFitControlWidget::onSliderValueChanged(int value)
{
    int interval = sliderValueToUpdateInterval(value);
    m_updateIntervalLabel->setText(QString::number(interval));
    if(fitSuiteItem())
        fitSuiteItem()->setItemValue(FitSuiteItem::P_UPDATE_INTERVAL, interval);
}

void RunFitControlWidget::onFitSuitePropertyChange(const QString &name)
{
    if(name == FitSuiteItem::P_ITERATION_COUNT) {
        int niter = fitSuiteItem()->getItemValue(FitSuiteItem::P_ITERATION_COUNT).toInt();
        m_iterationsCountLabel->setText(QString::number(niter));
    }
}

int RunFitControlWidget::sliderUpdateInterval()
{
    return sliderValueToUpdateInterval(m_intervalSlider->value());
}

//! converts slider value (1-15) to update interval to be propagated to FitSuiteWidget
int RunFitControlWidget::sliderValueToUpdateInterval(int value)
{
    if(value < (int)slider_to_interval.size())
        return slider_to_interval[value];

    return default_update_interval;
}

FitSuiteItem *RunFitControlWidget::fitSuiteItem()
{
    if(m_currentItem)
        return m_currentItem->fitSuiteItem();

    return nullptr;
}

bool RunFitControlWidget::isValidJobItem(JobItem *jobItem)
{
    if(!jobItem) return false;
    return jobItem->isValidForFitting();
}
