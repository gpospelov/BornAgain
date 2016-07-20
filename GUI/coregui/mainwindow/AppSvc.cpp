// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AppSvc.cpp
//! @brief     Implements class AppSvc
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "AppSvc.h"
#include "GUIHelpers.h"

ProjectManager *AppSvc::projectManager()
{
    return instance().this_projectManager();
}

void AppSvc::subscribe(ProjectManager *projectManager)
{
    return instance().this_subscribe(projectManager);
}

void AppSvc::unsubscribe(ProjectManager *projectManager)
{
    instance().this_unsubscribe(projectManager);
}

ProjectManager *AppSvc::this_projectManager()
{
    if(!m_projectManager) {
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to access "
                                "non existing ProjectManager.");
    }
    return m_projectManager;
}

void AppSvc::this_subscribe(ProjectManager *projectManager)
{
    if(m_projectManager != nullptr) {
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to subscribe "
                                "ProjectManager twice.");
    }
    m_projectManager = projectManager;
}

void AppSvc::this_unsubscribe(ProjectManager *projectManager)
{
    if(m_projectManager != projectManager) {
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to unsubscribe "
                                "ProjectManager before it was subscribed.");
    }
    m_projectManager = nullptr;
}
