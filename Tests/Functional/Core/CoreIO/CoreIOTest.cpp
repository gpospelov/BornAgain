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

    Benchmark bm;

    bm.start("createData");
    bm.start("sum");
    bm.start("sum2");
    auto data = createData(2048, 2049, true);
    bm.stop("createData");
    bm.stop("sum");

    bm.start("sum");

    bm.start("writeGz");
    IntensityDataIOFactory::writeOutputData(*data, "xxx.int.gz");
    bm.stop("writeGz");

    bm.start("write bz2");
    IntensityDataIOFactory::writeOutputData(*data, "xxx.int.bz2");
    bm.stop("write bz2");

    bm.start("readGz");
    auto newdata = IntensityDataIOFactory::readOutputData("xxx.int.gz");
    bm.stop("readGz");
    std::cout << "Diff: " << biggest_difference(*newdata, *data) << std::endl;

    bm.start("read bz2");
    auto newdata2 = IntensityDataIOFactory::readOutputData("xxx.int.bz2");
    bm.stop("read bz2");
    std::cout << "Diff: " << biggest_difference(*newdata2, *data) << std::endl;

    bm.stop("sum");
    bm.stop("sum2");

    std::cout << bm.report() << std::endl;
    return true;
}

std::unique_ptr<OutputData<double> > CoreIOTest::createData(int nx, int ny, bool fill)
{
    std::unique_ptr<OutputData<double> > result(new OutputData<double>);
    result->addAxis("x", nx, 0.0, static_cast<double>(nx));
    result->addAxis("y", ny, 0.0, static_cast<double>(ny));

    if(fill) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 12);
        for(size_t i=0; i<result->getAllocatedSize(); ++i) {
            double value = std::pow(10, dis(gen));
            (*result)[i] = value;
        }

    }

    return result;
}

//! Returns biggest element difference found;

double CoreIOTest::biggest_difference(const OutputData<double>& data, const OutputData<double>& ref)
{
    if(data.getAllocatedSize() != ref.getAllocatedSize())
        throw std::runtime_error("CoreIOTest::biggest_difference() -> Error. Size is different.");

    double max_diff = std::numeric_limits<double>::min();

    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
        double diff = Numeric::get_relative_difference(data[i], ref[i]);
        max_diff = std::max(diff, max_diff);
    }
    return max_diff;
}
