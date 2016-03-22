// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow_constants.h
//! @brief     Defines namespace Constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MAINWINDOWCONSTANTS_H
#define MAINWINDOWCONSTANTS_H


namespace Constants {

// general application settings
const char APPLICATION_NAME[]     = "BornAgain";
const char ORGANIZATION_NAME[]    = "Scientific Computing at MLZ";

const char ICON_NEWFILE[]          = ":/core/images/filenew.png";
const char ICON_OPENFILE[]         = ":/core/images/fileopen.png";
const char ICON_SAVEFILE[]         = ":/core/images/filesave.png";

// Settings groups
const char S_PROJECTMANAGER[]      = "ProjectManager";
const char S_MAINWINDOW[]          = "MainWindow";
const char S_MASKEDITOR[]          = "MaskEditor";
const char S_UPDATES[]             = "Updates";
const char S_MATERIALEDITOR[]      = "MaterialEditor";

// Settings keys
const char S_DEFAULTPROJECTPATH[]  = "DefaultProjectPath";
const char S_RECENTPROJECTS[]      = "RecentProjects";
const char S_WINDOWSIZE[]          = "size";
const char S_WINDOWPOSITION[]      = "pos";
const char S_SPLITTERSIZE[]        = "SplitterSize";
const char S_CHECKFORUPDATES[]     = "CheckForUpdates";

// Updates
const char S_VERSION_URL[]         = "http://apps.jcns.fz-juelich.de/src/BornAgain/CHANGELOG";
const char S_DOWNLOAD_LINK[]       = "http://www.bornagainproject.org/download";

const int MAX_RECENT_PROJECTS = 10;

const char MIME_JOBQUEUE[] = "application/org.bornagainproject.jobqueue";

// Colors
const unsigned int MAIN_THEME_COLOR    = 0x086FA1;
const unsigned int BUTTON_COLOR        = 0x044362;
const unsigned int BUTTON_TEXT_COLOR   = 0xFFFFFF;
//
}

#endif

