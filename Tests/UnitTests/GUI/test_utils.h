// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/UnitTests/GUI/test_utils.h
//! @brief     Defines auxiliary test functions in a namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TEST_UTILS
#define TEST_UTILS

#include <QString>

namespace TestUtils
{

//! Creates directory in current working directory. If such directory already exists,
//! it will be removed with all its content.
void create_dir(const QString& dir_name);

}

#endif // TEST_UTILS
