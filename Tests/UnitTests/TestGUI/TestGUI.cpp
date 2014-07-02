#include <QtTest>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestParameterizedItem.h"
#include "TestParticleItems.h"

int main(int argc, char** argv) {
    //QApplication app(argc, argv);
    //Q_UNUSED(app);
    QCoreApplication app(argc, argv);

    TestFormFactorItems testFormFactorItems;
    TestFTDistributionItems testFTDistributionItems;
    TestParameterizedItem testParameterizedItem;
    TestParticleItems testParticleItems;

    return QTest::qExec(&testFormFactorItems, argc, argv) |
           QTest::qExec(&testFTDistributionItems, argc, argv) |
           QTest::qExec(&testParameterizedItem, argc, argv) |
           QTest::qExec(&testParticleItems, argc, argv);
}
