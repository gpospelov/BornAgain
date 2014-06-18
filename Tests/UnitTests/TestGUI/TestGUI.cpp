#include <QtTest>
#include <QString>
#include <QDebug>
#include "TestFormFactorItems.h"
#include "TestFTDistributionItems.h"
#include "TestParameterizedItem.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestFormFactorItems test1;
    TestFTDistributionItems test2;
    TestParameterizedItem test3;

    return QTest::qExec(&test1, argc, argv) |
           QTest::qExec(&test2, argc, argv) |
           QTest::qExec(&test3, argc, argv);
}
