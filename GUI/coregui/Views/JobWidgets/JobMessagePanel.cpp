// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobMessagePanel.cpp
//! @brief     Implements class JobMessagePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobMessagePanel.h"
#include "mainwindow_constants.h"
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QScrollBar>

JobMessagePanel::JobMessagePanel(QWidget *parent)
    : QWidget(parent)
    , m_plainLog(new QPlainTextEdit)
{
    setWindowTitle(Constants::JobMessagePanelName);

    m_plainLog->setReadOnly(true);
    m_plainLog->setMaximumBlockCount(100000);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    m_plainLog->setFont(f);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_plainLog);

    setLayout(layout);
}

void JobMessagePanel::onClearLog()
{
    m_plainLog->clear();
}

void JobMessagePanel::onMessage(const QString &message)
{
    QScrollBar *scrollbar = m_plainLog->verticalScrollBar();
    bool autoscroll = scrollbar->value() == scrollbar->maximum();
    m_plainLog->appendPlainText(message);
    if (autoscroll) {
        QTextCursor c = m_plainLog->textCursor();
        c.movePosition(QTextCursor::End);
        m_plainLog->setTextCursor(c);
    }

}


