#include <QtTest>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include "TestMapper.h"
#include "TestPropertyAttributes.h"
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestParameterizedItem.h"
#include "TestParticleItems.h"
#include "TestLayerRoughnessItems.h"
#include "TestParaCrystalItems.h"
#include "TestSessionModel.h"
#include "TestGUICoreObjectCorrespondence.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    TestPropertyAttributes testPropertyAttributes;
    TestMapper testMapper;
//    TestFormFactorItems testFormFactorItems;
//    TestFTDistributionItems testFTDistributionItems;
//    TestParameterizedItem testParameterizedItem;
//    TestParticleItems testParticleItems;
//    TestLayerRoughnessItems testLayerRoughnessItems;
//    TestParaCrystalItems testParaCrystalItems;
//    TestSessionModel testSessionModel;
//    TestGUICoreObjectCorrespondence testGUICoreObjectCorrespondence;




//    return QTest::qExec(&testFormFactorItems, argc, argv) |
//           QTest::qExec(&testFTDistributionItems, argc, argv) |
//           QTest::qExec(&testParameterizedItem, argc, argv) |
//           QTest::qExec(&testParticleItems, argc, argv) |
//           QTest::qExec(&testLayerRoughnessItems, argc, argv) |
//           QTest::qExec(&testParaCrystalItems, argc, argv) |
//           QTest::qExec(&testSessionModel, argc, argv) |
//           QTest::qExec(&testGUICoreObjectCorrespondence, argc, argv);



    return QTest::qExec(&testPropertyAttributes, argc, argv) |
            QTest::qExec(&testMapper, argc, argv);

}
