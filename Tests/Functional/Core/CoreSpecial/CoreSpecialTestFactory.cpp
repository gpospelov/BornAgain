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
    registerItem("BatchSimulation", create_new<BatchSimulation>);

    registerItem("CoreIOPerformance", create_new<CoreIOPerformanceTest>);

    registerItem("CoreIOPath", create_new<CoreIOPathTest>);

    registerItem("FourierTransformation", create_new<FourierTransformationTest>);

    registerItem("MesoPerformance", create_new<MesoCrystalPerformanceTest>);

    registerItem("MultilayerPerformance", create_new<MultilayerPerformanceTest>);

    registerItem("MultiThreadPerformance", create_new<MultiThreadPerformanceTest>);
}
