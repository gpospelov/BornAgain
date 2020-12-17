//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/libtestmachinery/folderbasedtest.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "folderbasedtest.h"
#include "mvvm/utils/fileutils.h"
#include "test_utils.h"

FolderBasedTest::FolderBasedTest(const std::string& test_dir) : m_test_dir(test_dir) {
    TestUtils::CreateTestDirectory(m_test_dir);
}

std::string FolderBasedTest::testDir() const {
    return m_test_dir;
}

//! Return full path to the test folder. Located in CMAKE_BINARY_DIR/test_output/<m_test_dir>.

std::string FolderBasedTest::testPath() const {
    return TestUtils::TestDirectoryPath(m_test_dir);
}

//! Creates an empty directory in main test folder.
//! Remove recursively previous one with the same name, if exist.

std::string FolderBasedTest::createEmptyDir(const std::string& subdir) const {
    auto path = ModelView::Utils::join(testPath(), subdir);
    ModelView::Utils::remove_all(path);
    ModelView::Utils::create_directory(path);
    return path;
}

FolderBasedTest::~FolderBasedTest() = default;
