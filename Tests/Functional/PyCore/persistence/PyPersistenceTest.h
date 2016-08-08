// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PyPersistenceTest.h
//! @brief     Declares class PyPersistenceTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSUITETEST_H
#define PYSUITETEST_H

#include "IReferencedTest.h" // inheriting from
#include "OutputData.h"

//! @class PyPersistenceTest
//! @ingroup standard_samples
//! @brief A functional test of PyCore (the Python wrapper of BornAgain/Core).
//!   Performs a given standard simulation, both directly and from a Python dump.
//!   Invoked from PyPersistenceStandardTest.

class PyPersistenceTest : public IReferencedTest
{
public:
    PyPersistenceTest(const std::string& directory, const std::string& name);
    ~PyPersistenceTest() final {}

    void runTest() final;

    bool compareFilePair(const std::string& dat_fname, const std::string& ref_fname);
    bool compareIntensityPair(const std::string& dat_fname, const std::string& ref_fname);
    bool compareYamlPair(const std::string& dat_fname, const std::string& ref_fname);

private:
    std::string m_directory;
};

#endif // PYSUITETEST_H
