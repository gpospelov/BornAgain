// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/UpdateNotifierWidget.cpp
//! @brief     Implements class UpdateNotifierWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "UpdateNotifierWidget.h"
#include "UpdateNotifier.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDebug>


UpdateNotifierWidget::UpdateNotifierWidget(UpdateNotifier* updateNotifier, QWidget* parent)
    : QWidget(parent)
    , m_updateNotifier(updateNotifier)
    , m_updateLabel(new QLabel)
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_updateLabel);
    setLayout(layout);

    m_updateLabel->setText("xxx");
//    m_updateNotification->setContentsMargins(40, 10, 0, 0);
    m_updateLabel->setOpenExternalLinks(true);
    m_updateLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_updateLabel->setTextFormat(Qt::RichText);

    m_updateNotifier = updateNotifier;
    connect(m_updateNotifier, &UpdateNotifier::onUpdateNotification,
            this, &UpdateNotifierWidget::onUpdateNotification);
}

void UpdateNotifierWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    //m_updateNotifier->askForUpdates();
    QTimer::singleShot(200, this, [&](){
        qDebug() << "UpdateNotifierWidget::showEvent";
        m_updateNotifier->askForUpdates();
    });
}

void UpdateNotifierWidget::onUpdateNotification(const QString& text)
{
    qDebug() << "UpdateNotifierWidget::onUpdateNotification" << text;
    m_updateLabel->setText(text);
}
