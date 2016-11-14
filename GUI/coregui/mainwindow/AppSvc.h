// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AppSvc.h
//! @brief     Defines class AppSvc
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef APPSVC_H
#define APPSVC_H

#include "ISingleton.h"
#include "WinDllMacros.h"

class ProjectManager;

//! The AppSvc class provides common access for key components of the GUI.

class BA_CORE_API_ AppSvc : public ISingleton<AppSvc>
{
    friend class ISingleton<AppSvc>;
public:
    static ProjectManager *projectManager();
    static void subscribe(ProjectManager *projectManager);
    static void unsubscribe(ProjectManager *projectManager);

private:
    AppSvc() {}
    ProjectManager *this_projectManager();
    void this_subscribe(ProjectManager *projectManager);
    void this_unsubscribe(ProjectManager *projectManager);

    ProjectManager *m_projectManager;
};

#endif // APPSVC_H
