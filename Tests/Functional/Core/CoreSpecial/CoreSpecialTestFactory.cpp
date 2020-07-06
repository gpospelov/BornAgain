// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/CoreSpecialTestFactory.cpp
//! @brief     Implements CoreSpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/CoreSpecial/CoreSpecialTestFactory.h"
#include "Tests/Functional/Core/CoreSpecial/BatchSimulation.h"
#include "Tests/Functional/Core/CoreSpecial/CoreIOPathTest.h"
#include "Tests/Functional/Core/CoreSpecial/CoreIOPerformanceTest.h"
#include "Tests/Functional/Core/CoreSpecial/FourierTransformationTest.h"
#include "Tests/Functional/Core/CoreSpecial/MesoCrystalPerformanceTest.h"
#include "Tests/Functional/Core/CoreSpecial/MultiThreadPerformanceTest.h"
#include "Tests/Functional/Core/CoreSpecial/MultilayerPerformanceTest.h"

CoreSpecialTestFactory::CoreSpecialTestFactory()
{
    registerItem("BatchSimulation", create_new<BatchSimulation>,
                 "Running GISASSimulation in batch mode");

    registerItem("CoreIOPerformance", create_new<CoreIOPerformanceTest>,
                 "Input/output of heavy files");

    registerItem("CoreIOPath", create_new<CoreIOPathTest>,
                 "Input/output to files containing non-ascii characters in a path");

    registerItem("FourierTransformation", create_new<FourierTransformationTest>,
                 "Fourier transformation of GISAS images");

    registerItem("MesoPerformance", create_new<MesoCrystalPerformanceTest>,
                 "Heavy mesocrystal simulation");

    registerItem("MultilayerPerformance", create_new<MultilayerPerformanceTest>,
                 "Reflectometry performance on samples with a large number of layers");

    registerItem("MultiThreadPerformance", create_new<MultiThreadPerformanceTest>,
                 "Performance scaling with number of threads");
}
