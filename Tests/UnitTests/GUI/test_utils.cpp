// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/UnitTests/GUI/test_utils.h
//! @brief     Implements auxiliary test functions in a namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "test_utils.h"
#include "ProjectUtils.h"
#include "GUIHelpers.h"

void TestUtils::create_dir(const QString& dir_name)
{
    if (ProjectUtils::exists(dir_name))
        ProjectUtils::removeRecursively(dir_name);

    GUIHelpers::createSubdir(".", dir_name);
}
