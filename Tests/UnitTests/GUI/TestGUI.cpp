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
#include "TestSaveService.h"
#include "TestOutputDataIOService.h"
#include "TestIntensityDataItem.h"
#include "TestProjectUtils.h"
#include "TestParticleCoreShell.h"

inline bool TestResult(QObject *testObject, int argc = 0, char **argv = Q_NULLPTR) {
	return QTest::qExec(testObject, argc, argv) != 0;
}

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
    TestSaveService testSaveService;
    TestOutputDataIOService testIO;
    TestIntensityDataItem testIntensityData;
    TestProjectUtils testProjectUtils;
    TestParticleCoreShell testParticleCoreShell;

    bool status(false);

    status |= TestResult(&testFormFactorItems, argc, argv);
    status |= TestResult(&testFTDistributionItems, argc, argv);
    status |= TestResult(&testParameterizedItem, argc, argv);
    status |= TestResult(&testParticleItem, argc, argv);
    status |= TestResult(&testLayerRoughnessItems, argc, argv);
    status |= TestResult(&testParaCrystalItems, argc, argv);
    status |= TestResult(&testSessionModel, argc, argv);
    status |= TestResult(&testGUICoreObjectCorrespondence, argc, argv);
    status |= TestResult(&testSessionItem);
    status |= TestResult(&testMapperCases, argc, argv);
    status |= TestResult(&testSessionModel, argc, argv);
    status |= TestResult(&testMapperForItem, argc, argv);
    status |= TestResult(&testGUIHelpers, argc, argv);
    status |= TestResult(&testFitParameterModel, argc, argv);
    status |= TestResult(&testMaterialModel, argc, argv);
    status |= TestResult(&testComboProperty, argc, argv);
    status |= TestResult(&testTranslations, argc, argv);
    status |= TestResult(&testGroupProperty, argc, argv);
    status |= TestResult(&testParticleDistributionItem, argc, argv);
    status |= TestResult(&testParameterTreeUtils, argc, argv);
    status |= TestResult(&testDetectorItems, argc, argv);
    status |= TestResult(&testLinkInstrument, argc, argv);
    status |= TestResult(&testUpdateTimer, argc, argv);
    status |= TestResult(&testProjectDocument, argc, argv);
    status |= TestResult(&testSaveService, argc, argv);
    status |= TestResult(&testIO, argc, argv);
    status |= TestResult(&testIntensityData, argc, argv);
    status |= TestResult(&testProjectUtils, argc, argv);

    return status;
}
