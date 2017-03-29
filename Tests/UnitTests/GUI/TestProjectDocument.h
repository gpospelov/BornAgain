#include <QtTest>
#include "projectdocument.h"
#include "ApplicationModels.h"
#include "InstrumentModel.h"
#include "InstrumentItem.h"
#include "GUIHelpers.h"
#include <QSignalSpy>
#include <QDebug>

class TestProjectDocument : public QObject
{
    Q_OBJECT

private slots:
    // helper method to modify something in a model
    void modify_models(ApplicationModels* models) {
        auto instrument = models->instrumentModel()->instrumentItem();
        instrument->setItemValue(InstrumentItem::P_IDENTIFIER, GUIHelpers::createUuid());
    }

    void test_projectDocument();
};

inline void TestProjectDocument::test_projectDocument()
{
    ApplicationModels models;
    ProjectDocument* document = new ProjectDocument;
    document->setApplicationModels(&models);

    // Checking initial document status
    QVERIFY(document->isModified() == false);
    QVERIFY(document->hasValidNameAndPath() == false);
    QCOMPARE(document->projectDir(), QString());
    QCOMPARE(document->projectName(), QString());
    QCOMPARE(document->projectFileName(), QString());

    // Preparing place for project
    const QString projectDir("test_projectDocument");
    const QString projectFileName("test_projectDocument/document.pro");
    GUIHelpers::createSubdir(".", projectDir);

    // Checking document name and isModified status after project save
    document->save(projectFileName);
    QVERIFY(document->hasValidNameAndPath() == true);
    QCOMPARE(document->projectDir(), projectDir);
    QCOMPARE(document->projectName(), QString("document"));
    QCOMPARE(document->projectFileName(), projectFileName);
    QVERIFY(document->isModified() == false);

    QSignalSpy spyDocument(document, SIGNAL(modified()));
    QCOMPARE(spyDocument.count(), 0);

    // Changing document and checking its status
    modify_models(&models);
    QVERIFY(document->isModified() == true);
    QCOMPARE(spyDocument.count(), 1);

    // Saving document
    document->save(projectFileName);
    QVERIFY(document->isModified() == false);
    QCOMPARE(spyDocument.count(), 2); // save triggers 'modified' signal

    QFileInfo info(projectFileName);
    QVERIFY(info.exists());

    delete document;
}
