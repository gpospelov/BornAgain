// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreIO/CoreIOTest.cpp
//! @brief     Implements CoreIOTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreIOTest.h"
#include "IntensityDataIOFactory.h"
#include "Benchmark.h"
#include "Numeric.h"
#include <iostream>
#include <cassert>
#include <random>
#include <iomanip>

bool CoreIOTest::runTest()
{
    std::cout << "CoreIOTest::runTest()" << std::endl;

    test_configuration(1024, 768, false);
    test_configuration(1024, 768, true);
    test_configuration(2048, 2048, true);

    return true;
}

void CoreIOTest::test_configuration(int nx, int ny, bool random_data)
{
    Benchmark bm;

    std::ostringstream report;
    report << std::string(60, '-') << "\n";
    report << "Test " << nx << "x" << ny << (random_data ? " random data" : " zeros") << "\n";

    bm.start("createData");
    auto ref_data = createData(nx, ny, random_data);
    bm.stop("createData");

    bm.start("write gz");
    IntensityDataIOFactory::writeOutputData(*ref_data, "xxx.int.gz");
    bm.stop("write gz");

    bm.start("write bz2");
    IntensityDataIOFactory::writeOutputData(*ref_data, "xxx.int.bz2");
    bm.stop("write bz2");

    bm.start("write int");
    IntensityDataIOFactory::writeOutputData(*ref_data, "xxx.int");
    bm.stop("write int");

    bm.start("read gz");
    auto data_gz = IntensityDataIOFactory::readOutputData("xxx.int.gz");
    bm.stop("read gz");

    bm.start("read bz2");
    auto data_bz2 = IntensityDataIOFactory::readOutputData("xxx.int.bz2");
    bm.stop("read bz2");

    bm.start("read int");
    auto data_int = IntensityDataIOFactory::readOutputData("xxx.int");
    bm.stop("read int");

    report << bm.report();

    report << "Diff_gz: " << biggest_difference(*data_gz, *ref_data)
           << " Diff_bz: " << biggest_difference(*data_bz2, *ref_data)
           << " Diff_int: " << biggest_difference(*data_int, *ref_data)
           << "\n";

    std::cout << report.str() << std::endl;
}

std::unique_ptr<OutputData<double>> CoreIOTest::createData(int nx, int ny, bool fill)
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis("x", nx, 0.0, static_cast<double>(nx));
    result->addAxis("y", ny, 0.0, static_cast<double>(ny));

    if (fill) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 12);
        for (size_t i = 0; i < result->getAllocatedSize(); ++i) {
            double value = std::pow(10, dis(gen));
            (*result)[i] = value;
        }
    }

    return result;
}

//! Returns biggest element difference found;

double CoreIOTest::biggest_difference(const OutputData<double>& data, const OutputData<double>& ref)
{
    if (data.getAllocatedSize() != ref.getAllocatedSize())
        throw std::runtime_error("CoreIOTest::biggest_difference() -> Error. Size is different.");

    double max_diff = std::numeric_limits<double>::min();

    for (size_t i = 0; i < data.getAllocatedSize(); ++i) {
        double diff = Numeric::get_relative_difference(data[i], ref[i]);
        max_diff = std::max(diff, max_diff);
    }
    return max_diff;
}
