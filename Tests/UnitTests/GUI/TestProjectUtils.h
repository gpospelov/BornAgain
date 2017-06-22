#include <QtTest>
#include "ProjectUtils.h"
#include "GUIHelpers.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

namespace {
const QString& projectDir = "test_ProjectUtils";
}

class TestProjectUtils : public QObject
{
    Q_OBJECT

private slots:
    //! Helper function to create test file in a given directory (directory should exist).
    void createTestFile(const QString& dirname, const QString& fileName)
    {
        QString filename = dirname.isEmpty() ? fileName : dirname +"/"+fileName;

        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw GUIHelpers::Error("TestProjectUtils::createTestFile() -> Error. "
                                    "Can't create file");

        QTextStream out(&file);
        out << "Test file " << 42 << "\n";
        file.close();
    }

    void test_basicFileOperations();
    void test_nonXMLDataInDir();
    void test_stringListSubstraction();
};

inline void TestProjectUtils::test_basicFileOperations()
{
    QDir dir(projectDir);
    if(dir.exists()) {
        QVERIFY(ProjectUtils::removeRecursively(projectDir) == true);
        QVERIFY(dir.exists() == false);
    }

    GUIHelpers::createSubdir(".", projectDir);
    QVERIFY(ProjectUtils::exists(projectDir));

    createTestFile(projectDir, "a.txt");
    QVERIFY(ProjectUtils::exists(projectDir+"/a.txt"));
}


inline void TestProjectUtils::test_nonXMLDataInDir()
{
    QCOMPARE(1,1);
    QStringList test_nonxml_files = QStringList()
            << "jobdata_job2_0.int.gz"
            << "refdata_job2_0.int.gz"
            << "realdata_box_nanodots_0.int.gz"
            << "realdata_untitled_0.int.gz";

    QStringList test_some_other_files = QStringList()
            << "user_0.int.gz"
            << "b.txt"
            << "untitled.pro";

    // creating files
    QStringList test_files = QStringList() << test_nonxml_files << test_some_other_files;
    for(auto name : test_files) {
        createTestFile(projectDir, name);
        QVERIFY(ProjectUtils::exists(projectDir+"/"+name));
    }

    // Checking nonXMLDataInDir method, should contain only files from test_nonxml_files.
    QStringList nonxml = ProjectUtils::nonXMLDataInDir(projectDir);

    nonxml.sort();
    test_nonxml_files.sort();

    QCOMPARE(nonxml.size(), 4);
    QCOMPARE(test_nonxml_files, nonxml);

    // removing nonxml files
    QVERIFY(ProjectUtils::removeFiles(projectDir, nonxml) == true);

    // checking that no files left
    nonxml = ProjectUtils::nonXMLDataInDir(projectDir);
    QCOMPARE(nonxml.size(), 0);
}

//! Test substraction of two lists (scenario: old files on disk vs new files).

inline void TestProjectUtils::test_stringListSubstraction()
{
    QStringList oldFiles = QStringList()
            << "a.int.gz" << "b.int.gz" << "c.int.gz";

    QStringList newFiles = QStringList()
            << "d.int.gz" << "b_renamed.int.gz" << "c.int.gz" << "a.int.gz";

    QStringList diff = ProjectUtils::substract(oldFiles, newFiles);
    QCOMPARE(diff.size(), 1);
    QCOMPARE(diff.at(0), QString("b.int.gz"));
}

