//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/libtestmachinery/folderbasedtest.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_FOLDERBASEDTEST_H
#define BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_FOLDERBASEDTEST_H

#include <gtest/gtest.h>
#include <string>

//! Convenience class which creates a directory on disk for test content.

class FolderBasedTest : public ::testing::Test {
public:
    FolderBasedTest(const std::string& test_dir);
    ~FolderBasedTest();

    std::string testDir() const;

    std::string testPath() const;

    std::string createEmptyDir(const std::string& subdir) const;

protected:
    std::string m_test_dir; //! main directory of given test
};

#endif // BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_FOLDERBASEDTEST_H
