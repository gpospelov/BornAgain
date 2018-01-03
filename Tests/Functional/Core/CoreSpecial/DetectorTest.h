// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/DetectorTest.h
//! @brief     Defines class DetectorTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTORTEST_H
#define DETECTORTEST_H

#include "IFunctionalTest.h"
#include <vector>
#include <memory>

class Simulation;
class Benchmark;

//! Functional test for measuring simulation performance on detectors of different sizes.
//! No comparison with reference data provided since it is not the concern
//! of the test.

class DetectorTest : public IFunctionalTest
{
public:
    DetectorTest();
    virtual ~DetectorTest();

private:
    typedef std::vector<std::string> OutputDataTable;

    virtual bool runTest() override;

    //! Runs tests on a detector of size \f$ size \cross size \f$.
    //! _run_n_times_ is the number of repetitions
    std::unique_ptr<Benchmark> runSingleSizeDetectorTest(size_t size, int run_n_times) const;

    //! Creates a table with header and no content
    OutputDataTable createTableWithHeader() const;

    //! Writes data to table
    void writeDataToTable(std::unique_ptr<Benchmark> test_result, int n_runs);

    void printResult();

    //! Vector of pairs (detector size, number of runs) for running subtests
    const std::vector<std::pair<size_t, int>> m_input_parameters;
    OutputDataTable m_data_table; //!< output data table with running times
    const size_t m_init_table_size;
};

#endif // DETECTOR_H
