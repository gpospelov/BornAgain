// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitControlWidget.cpp
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
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>

RunFitControlWidget::RunFitControlWidget(QWidget *parent)
    : QWidget(parent)
    , m_startButton(new QPushButton)
    , m_stopButton(new QPushButton)
    , m_intervalSlider(new QSlider)
{
    QHBoxLayout *layout = new QHBoxLayout;

    m_startButton->setText("Run");
    m_startButton->setToolTip("Run fitting");
    m_startButton->setMaximumWidth(80);
//    m_startButton->setMinimumHeight(50);

    m_stopButton->setText("Stop");
    m_stopButton->setToolTip("Interrupt fitting");
    m_stopButton->setMaximumWidth(80);
    m_stopButton->setEnabled(false);

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
    setLayout(layout);

    connect(m_startButton, SIGNAL(clicked(bool)), this, SIGNAL(startFitting()));
    connect(m_stopButton, SIGNAL(clicked(bool)), this, SIGNAL(stopFitting()));
}

void RunFitControlWidget::onFittingStarted()
{
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
}

void RunFitControlWidget::onFittingFinished()
{
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
}

void RunFitControlWidget::setItem(JobItem *item)
{
    Q_UNUSED(item);
}
