#include <QtTest>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestParameterizedItem.h"
#include "TestParticleItems.h"
#include "TestLayerRoughnessItems.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    TestFormFactorItems testFormFactorItems;
    TestFTDistributionItems testFTDistributionItems;
    TestParameterizedItem testParameterizedItem;
    TestParticleItems testParticleItems;
    TestLayerRoughnessItems testLayerRoughnessItems;

    return QTest::qExec(&testFormFactorItems, argc, argv) |
           QTest::qExec(&testFTDistributionItems, argc, argv) |
           QTest::qExec(&testParameterizedItem, argc, argv) |
           QTest::qExec(&testParticleItems, argc, argv) |
           QTest::qExec(&testLayerRoughnessItems, argc, argv);
}
