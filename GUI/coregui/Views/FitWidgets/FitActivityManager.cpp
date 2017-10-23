// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitActivityManager.cpp
//! @brief     Implements class FitActivityManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitActivityManager.h"
#include "FitSessionController.h"
#include "FitLog.h"
#include "JobItem.h"
#include "GUIHelpers.h"
#include "JobMessagePanel.h"

FitActivityManager::FitActivityManager(QObject* parent)
    : QObject(parent)
    , m_activeSession(nullptr)
    , m_jobMessagePanel(nullptr)
{

}

void FitActivityManager::setMessagePanel(JobMessagePanel* messagePanel)
{
    m_jobMessagePanel = messagePanel;
}

FitSessionController* FitActivityManager::sessionController(JobItem* item)
{
    FitSessionController* result(nullptr);

    auto it = m_item_to_controller.find(item);
    if (it == m_item_to_controller.end()) {
        result = createController(item);
        m_item_to_controller.insert(item, result);
    } else {
        result = it.value();
    }

    disableLogging();

    result->fitLog()->setMessagePanel(m_jobMessagePanel);
    m_activeSession = result;

    return result;
}

void FitActivityManager::disableLogging()
{
    if (m_activeSession)
        m_activeSession->fitLog()->setMessagePanel(nullptr);

    m_jobMessagePanel->onClearLog();
}


FitSessionController* FitActivityManager::createController(JobItem* jobItem)
{
    jobItem->mapper()->setOnItemDestroy([this](SessionItem* item) {removeController(item);}, this);

    auto result = new FitSessionController(this);
    result->setItem(jobItem);
    return result;
}

//! Removes manager for given jobItem

void FitActivityManager::removeController(SessionItem* jobItem)
{
    auto it = m_item_to_controller.find(jobItem);
    if (it == m_item_to_controller.end())
        throw GUIHelpers::Error("FitActivityManager::removeFitSession() -> Error. "
                                "Can't find fit session");

    it.value()->deleteLater();
    m_item_to_controller.erase(it);
}
