#include <QtTest>
#include <QString>
#include <QCoreApplication>

#include "TestComboProperty.h"
#include "TestComponentProxyModel.h"
#include "TestComponentUtils.h"
#include "TestDetectorItems.h"
#include "TestExternalProperty.h"
#include "TestFitParameterModel.h"
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestGroupItem.h"
#include "TestGUICoreObjectCorrespondence.h"
#include "TestGUIHelpers.h"
#include "TestIntensityDataItem.h"
#include "TestLayerItems.h"
#include "TestLayerRoughnessItems.h"
#include "TestLinkInstrument.h"
#include "TestMapperCases.h"
#include "TestMapperForItem.h"
#include "TestMaterialModel.h"
#include "TestMaterialPropertyController.h"
#include "TestModelUtils.h"
#include "TestOutputDataIOService.h"
#include "TestParaCrystalItems.h"
#include "TestParameterizedItem.h"
#include "TestParameterTreeUtils.h"
#include "TestParticleCoreShell.h"
#include "TestParticleDistributionItem.h"
#include "TestParticleItem.h"
#include "TestProjectDocument.h"
#include "TestProjectUtils.h"
#include "TestPropertyRepeater.h"
#include "TestProxyModelStrategy.h"
#include "TestSaveService.h"
#include "TestSessionItemController.h"
#include "TestSessionItem.h"
#include "TestSessionItemUtils.h"
#include "TestSessionModel.h"
#include "TestSessionXML.h"
#include "TestTranslations.h"
#include "TestUpdateTimer.h"
#include <memory>

class GUITestFactory {
public:
    using create_t = std::function<QObject*()>;

    template<typename T> void add() {
        creators.push_back([](){return new T();});
    }

    int runAll(int argc, char** argv)
    {
        int result(0);
        for(auto f : creators) {
            std::unique_ptr<QObject> obj(f());
            result +=  QTest::qExec(obj.get(), argc, argv);
        }
        return result;
    }

private:
    std::vector<create_t> creators;
};

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    QMetaType::registerComparators<ComboProperty>();
    QMetaType::registerComparators<ExternalProperty>();

    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("LayoutChangeHint");

    GUITestFactory tests;

    tests.add<TestComboProperty>();
    tests.add<TestComponentProxyModel>();
    tests.add<TestComponentUtils>();
    tests.add<TestDetectorItems>();
    tests.add<TestExternalProperty>();
    tests.add<TestFitParameterModel>();
    tests.add<TestFormFactorItems>();
    tests.add<TestFTDistributionItems>();
    tests.add<TestGroupItem>();
    tests.add<TestGUICoreObjectCorrespondence>();
    tests.add<TestGUIHelpers>();
    tests.add<TestIntensityDataItem>();
    tests.add<TestLayerItems>();
    tests.add<TestLayerRoughnessItems>();
    tests.add<TestLinkInstrument>();
    tests.add<TestMapperCases>();
    tests.add<TestMapperForItem>();
    tests.add<TestMaterialModel>();
    tests.add<TestMaterialPropertyController>();
    tests.add<TestModelUtils>();
    tests.add<TestOutputDataIOService>();
    tests.add<TestParaCrystalItems>();
    tests.add<TestParameterizedItem>();
    tests.add<TestParameterTreeUtils>();
    tests.add<TestParticleCoreShell>();
    tests.add<TestParticleDistributionItem>();
    tests.add<TestParticleItem>();
    tests.add<TestProjectDocument>();
    tests.add<TestProjectUtils>();
    tests.add<TestPropertyRepeater>();
    tests.add<TestProxyModelStrategy>();
    tests.add<TestSaveService>();
    tests.add<TestSessionItem>();
    tests.add<TestSessionItemController>();
    tests.add<TestSessionItemUtils>();
    tests.add<TestSessionModel>();
    tests.add<TestSessionXML>();
    tests.add<TestTranslations>();
    tests.add<TestUpdateTimer>();

    return tests.runAll(argc, argv);
}
