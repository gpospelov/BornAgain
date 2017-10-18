// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitLog.cpp
//! @brief     Implements class FitLog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitLog.h"
#include "JobMessagePanel.h"

FitLog::FitLog()
    : m_messagePanel(nullptr)
{

}

void FitLog::setMessagePanel(JobMessagePanel* messagePanel)
{
    m_messagePanel = messagePanel;
    if (!m_messagePanel)
        return;

    m_messagePanel->onClearLog();

    for(auto& record : m_records) {
        m_messagePanel->onMessage(QString::fromStdString(record.m_text),
                                  QColor(FitLogFlags::color(record.m_type)));
    }
}

void FitLog::append(const std::string& text, FitLogFlags::MessageType type)
{
    m_records.push_back({text, type});

    if (m_messagePanel)
        m_messagePanel->onMessage(QString::fromStdString(text),
                                  QColor(FitLogFlags::color(type)));
}

void FitLog::clearLog()
{
    m_records.clear();
    if (m_messagePanel)
        m_messagePanel->onClearLog();
}
