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

// settings groups
const char S_PROJECTMANAGER[]      = "ProjectManager";

const int MAX_RECENT_PROJECTS = 7;

const char MIME_JOBQUEUE[] = "application/org.bornagainproject.jobqueue";
}

#endif

