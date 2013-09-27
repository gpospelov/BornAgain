// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/BAVersion.h
//! @brief     Defines namespace AppVersion.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BAVERSION_H_
#define BAVERSION_H_

#include <string>
#include <sstream>

namespace AppVersion {
    const std::string g_app_name = "BornAgain";
    const int major_version_number = 0;
    const int minor_version_number = 9;
    const int patch_version_number = 1;

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



#endif /* BAVERSION_H_ */

