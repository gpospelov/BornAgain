// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/Version.h
//! @brief     Defines namespace AppVersion.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef VERSION_H_
#define VERSION_H_

#include <string>
#include <sstream>

namespace AppVersion {
    const std::string g_app_name = "BornAgain";
    const int major_version_number = 0;
    const int minor_version_number = 8;
    const int patch_version_number = 2;

    inline int GetMajorVersionNumber() { return major_version_number; }
    inline int GetMinorVersionNumber() { return minor_version_number; }
    inline int GetPatchVersionNumber() { return patch_version_number; }

    inline std::string GetVersionNumber()
    {
        std::ostringstream ostr;
        ostr << major_version_number
             << "."
             << minor_version_number
             << "."
             << patch_version_number ;

        return ostr.str();
    }

}



#endif /* VERSION_H_ */

