// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow_constants.h
//! @brief     Declares namespace Constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MAINWINDOWCONSTANTS_H
#define MAINWINDOWCONSTANTS_H

#include <QString>

namespace Constants {

// general application settings
const char APPLICATION_NAME[]     = "BornAgain";
const char ORGANIZATION_NAME[]    = "Scientific Computing at MLZ";

// Settings groups
const char S_PROJECTMANAGER[]      = "ProjectManager";
const char S_MAINWINDOW[]          = "MainWindow";
const char S_MASKEDITOR[]          = "MaskEditor";
const char S_UPDATES[]             = "Updates";
const char S_MATERIALEDITOR[]      = "MaterialEditor";
const char S_SESSIONMODELVIEW[]    = "SessionModelView";

// Settings keys
const char S_DEFAULTPROJECTPATH[]  = "DefaultProjectPath";
const char S_RECENTPROJECTS[]      = "RecentProjects";
const char S_LASTUSEDIMPORTDIR[]   = "LastUsedImportDir";
const char S_WINDOWSIZE[]          = "size";
const char S_WINDOWPOSITION[]      = "pos";
const char S_SPLITTERSIZE[]        = "SplitterSize";
const char S_CHECKFORUPDATES[]     = "CheckForUpdates";
const char S_VIEWISACTIVE[]        = "ViewIsActive";

// Updates
const char S_VERSION_URL[]         = "http://apps.jcns.fz-juelich.de/src/BornAgain/CHANGELOG";
const char S_DOWNLOAD_LINK[]       = "http://www.bornagainproject.org/download";

const int MAX_RECENT_PROJECTS = 10;

const char MIME_JOBQUEUE[] = "application/org.bornagainproject.jobqueue";

// Colors
const unsigned int MAIN_THEME_COLOR    = 0x086FA1;
const unsigned int BUTTON_COLOR        = 0x044362;
const unsigned int BUTTON_TEXT_COLOR   = 0xFFFFFF;

const unsigned int REALTIME_WIDGET_WIDTH_HINT = 480;

// JobView

const QString JobRealTimeWidgetName = "Job Real Time";
const QString JobPropertiesWidgetName = "Job Properties";
const QString JobFitPanelName = "Fit Panel";
const QString JobSelectorWidgetName = "Job Selector";
const QString JobMessagePanelName = "Message Panel";

const QString JobViewActivityName = "Job View Activity";
const QString JobRealTimeActivityName = "Real Time Activity";
const QString JobFittingActivityName = "Fitting Activity";

}

#endif

