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
#include "WarningSignWidget.h"
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>

namespace {
const int warning_sign_xpos = 38;
const int warning_sign_ypos = 38;
}

RunFitControlWidget::RunFitControlWidget(QWidget *parent)
    : QWidget(parent)
    , m_startButton(new QPushButton)
    , m_stopButton(new QPushButton)
    , m_intervalSlider(new QSlider)
    , m_currentItem(0)
    , m_warningSign(0)
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
    clearWarningSign();
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
}

void RunFitControlWidget::onFittingFinished()
{
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
}

void RunFitControlWidget::onFittingError(const QString &what)
{
    clearWarningSign();

    QString message;
    message.append("Current settings cause fitting failure.\n\n");
    message.append(what);

    m_warningSign = new WarningSignWidget(this);
    m_warningSign->setWarningMessage(message);
    QPoint pos = getPositionForWarningSign();
    m_warningSign->setPosition(pos.x(), pos.y());
    m_warningSign->show();
}

void RunFitControlWidget::setItem(JobItem *item)
{
    Q_UNUSED(item);
    m_currentItem = item;
}

void RunFitControlWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(m_warningSign) {
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(),pos.y());
    }
}

QPoint RunFitControlWidget::getPositionForWarningSign()
{
    int x = width()-warning_sign_xpos;
    int y = height()-warning_sign_ypos;
    return QPoint(x, y);
}

void RunFitControlWidget::clearWarningSign()
{
    delete m_warningSign;
    m_warningSign = 0;
}
