// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

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
