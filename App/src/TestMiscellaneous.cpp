// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestMiscellaneous.cpp
//! @brief     Implements class TestMiscellaneous.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestMiscellaneous.h"
#include "TiffReadStrategy.h"
#include <iostream>


TestMiscellaneous::TestMiscellaneous()
{
}

void TestMiscellaneous::execute()
{
    test_Tiff();
}


void TestMiscellaneous::test_Tiff()
{
    std::cout << "Hello world" << std::endl;

    TiffReadStrategy reader;
//    reader.read("im_0022928_caz.tif");
    reader.read("galaxi_raw_data.tif");
}
