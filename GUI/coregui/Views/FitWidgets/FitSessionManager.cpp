// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionManager.cpp
//! @brief     Implements class FitSessionManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitSessionManager.h"
#include "FitSessionController.h"
#include "FitLog.h"
#include "JobItem.h"
#include "GUIHelpers.h"
#include "JobMessagePanel.h"

FitSessionManager::FitSessionManager(QObject* parent)
    : QObject(parent)
    , m_activeController(nullptr)
    , m_jobMessagePanel(nullptr)
{

}

void FitSessionManager::setMessagePanel(JobMessagePanel* messagePanel)
{
    m_jobMessagePanel = messagePanel;
}

FitSessionController* FitSessionManager::sessionController(JobItem* item)
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
    m_activeController = result;

    return result;
}

void FitSessionManager::disableLogging()
{
    if (m_activeController)
        m_activeController->fitLog()->setMessagePanel(nullptr);

    m_jobMessagePanel->onClearLog();
}


FitSessionController* FitSessionManager::createController(JobItem* jobItem)
{
    jobItem->mapper()->setOnItemDestroy([this](SessionItem* item) {removeController(item);}, this);

    auto result = new FitSessionController(this);
    result->setItem(jobItem);
    return result;
}

//! Removes manager for given jobItem

void FitSessionManager::removeController(SessionItem* jobItem)
{
    auto it = m_item_to_controller.find(jobItem);
    if (it == m_item_to_controller.end())
        throw GUIHelpers::Error("FitActivityManager::removeFitSession() -> Error. "
                                "Can't find fit session");

    it.value()->deleteLater();
    m_item_to_controller.erase(it);
}
