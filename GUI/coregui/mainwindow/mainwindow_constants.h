// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow_constants.h
//! @brief     Defines namespace Constants
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace Constants {

// general application settings
const char APPLICATION_NAME[]     = "BornAgain";
const char APPLICATION_VERSION[]  = "0.9";
const char ORGANIZATION_NAME[]    = "Scientific Computing at MLZ";

// Menubar
const char MENU_BAR[]              = "BornAgain.MenuBar";

// Main menu bar groups
const char G_FILE[]                = "BornAgain.Group.File";
const char G_HELP[]                = "BornAgain.Group.Help";

const char ICON_NEWFILE[]          = ":/core/images/filenew.png";
const char ICON_OPENFILE[]         = ":/core/images/fileopen.png";
const char ICON_SAVEFILE[]         = ":/core/images/filesave.png";

// settings groups
const char S_PROJECTMANAGER[]      = "ProjectManager";

const int MAX_RECENT_PROJECTS = 10;

const char MIME_JOBQUEUE[] = "application/org.bornagainproject.jobqueue";
}

#endif

