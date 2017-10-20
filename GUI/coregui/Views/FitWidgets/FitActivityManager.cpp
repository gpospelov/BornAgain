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
#include "FitSuiteManager.h"
#include "FitLog.h"
#include "JobItem.h"
#include "GUIHelpers.h"
#include "JobMessagePanel.h"

FitActivityManager::FitActivityManager(QObject* parent)
    : QObject(parent)
    , m_activeManager(nullptr)
    , m_jobMessagePanel(nullptr)
{

}

void FitActivityManager::setMessagePanel(JobMessagePanel* messagePanel)
{
    m_jobMessagePanel = messagePanel;
}

FitSessionActivity* FitActivityManager::manager(JobItem* item)
{
    FitSessionActivity* result(nullptr);

    auto it = m_item_to_manager.find(item);
    if (it == m_item_to_manager.end()) {
        result = createManager(item);
        m_item_to_manager.insert(item, result);
    } else {
        result = it.value();
    }

    disableLogging();

    result->fitLog()->setMessagePanel(m_jobMessagePanel);
    m_activeManager = result;

    return result;
}

void FitActivityManager::disableLogging()
{
    if (m_activeManager)
        m_activeManager->fitLog()->setMessagePanel(nullptr);

    m_jobMessagePanel->onClearLog();
}


FitSessionActivity* FitActivityManager::createManager(JobItem* jobItem)
{
    jobItem->mapper()->setOnItemDestroy([this](SessionItem* item) {removeManager(item);}, this);

    auto result = new FitSessionActivity(this);
    result->setItem(jobItem);
    return result;
}

//! Removes manager for given jobItem

void FitActivityManager::removeManager(SessionItem* jobItem)
{
    auto it = m_item_to_manager.find(jobItem);
    if (it == m_item_to_manager.end())
        throw GUIHelpers::Error("FitActivityManager::removeManager() -> Error. Can't fine item");

    it.value()->deleteLater();
    m_item_to_manager.erase(it);
}
