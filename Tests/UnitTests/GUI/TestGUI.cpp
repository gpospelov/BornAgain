#include <QtTest>
#include <QString>
#include <QCoreApplication>
#include "TestMapperCases.h"
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestParameterizedItem.h"
#include "TestParticleItem.h"
#include "TestLayerRoughnessItems.h"
#include "TestParaCrystalItems.h"
#include "TestSessionModel.h"
#include "TestSessionItem.h"
#include "TestGUICoreObjectCorrespondence.h"
#include "TestMapperForItem.h"
#include "TestParticleDistributionItem.h"
#include "TestGUIHelpers.h"
#include "TestFitParameterModel.h"
#include "TestMaterialModel.h"
#include "TestComboProperty.h"
#include "TestTranslations.h"
#include "TestGroupProperty.h"
#include "TestParameterTreeUtils.h"
#include "TestDetectorItems.h"
#include "TestLinkInstrument.h"
#include "TestUpdateTimer.h"
#include "TestProjectDocument.h"
#include "TestAutosave.h"
#include "TestOutputDataIOService.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    QMetaType::registerComparators<ComboProperty>();

    TestFormFactorItems testFormFactorItems;
    TestFTDistributionItems testFTDistributionItems;
    TestParameterizedItem testParameterizedItem;
    TestParticleItem testParticleItem;
    TestLayerRoughnessItems testLayerRoughnessItems;
    TestParaCrystalItems testParaCrystalItems;
    TestSessionModel testSessionModel;
    TestGUICoreObjectCorrespondence testGUICoreObjectCorrespondence;
    TestSessionItem testSessionItem;
    TestMapperCases testMapperCases;
    TestMapperForItem testMapperForItem;
    TestGUIHelpers testGUIHelpers;
    TestFitParameterModel testFitParameterModel;
    TestMaterialModel testMaterialModel;
    TestComboProperty testComboProperty;
    TestTranslations testTranslations;
    TestGroupProperty testGroupProperty;
    TestParticleDistributionItem testParticleDistributionItem;
    TestParameterTreeUtils testParameterTreeUtils;
    TestDetectorItems testDetectorItems;
    TestLinkInstrument testLinkInstrument;
    TestUpdateTimer testUpdateTimer;
    TestProjectDocument testProjectDocument;
    TestAutosave testAutosave;
    TestOutputDataIOService testIO;

    bool status(false);

    status |= QTest::qExec(&testFormFactorItems, argc, argv);
    status |= QTest::qExec(&testFTDistributionItems, argc, argv);
    status |= QTest::qExec(&testParameterizedItem, argc, argv);
    status |= QTest::qExec(&testParticleItem, argc, argv);
    status |= QTest::qExec(&testLayerRoughnessItems, argc, argv);
    status |= QTest::qExec(&testParaCrystalItems, argc, argv);
    status |= QTest::qExec(&testSessionModel, argc, argv);
    status |= QTest::qExec(&testGUICoreObjectCorrespondence, argc, argv);
    status |= QTest::qExec(&testSessionItem);
    status |= QTest::qExec(&testMapperCases, argc, argv);
    status |= QTest::qExec(&testSessionModel, argc, argv);
    status |= QTest::qExec(&testMapperForItem, argc, argv);
    status |= QTest::qExec(&testGUIHelpers, argc, argv);
    status |= QTest::qExec(&testFitParameterModel, argc, argv);
    status |= QTest::qExec(&testMaterialModel, argc, argv);
    status |= QTest::qExec(&testComboProperty, argc, argv);
    status |= QTest::qExec(&testTranslations, argc, argv);
    status |= QTest::qExec(&testGroupProperty, argc, argv);
    status |= QTest::qExec(&testParticleDistributionItem, argc, argv);
    status |= QTest::qExec(&testParameterTreeUtils, argc, argv);
    status |= QTest::qExec(&testDetectorItems, argc, argv);
    status |= QTest::qExec(&testLinkInstrument, argc, argv);
    status |= QTest::qExec(&testLinkInstrument, argc, argv);
    status |= QTest::qExec(&testUpdateTimer, argc, argv);
    status |= QTest::qExec(&testProjectDocument, argc, argv);
    status |= QTest::qExec(&testAutosave, argc, argv);
    status |= QTest::qExec(&testIO, argc, argv);

    return status;
}
