#include <QtTest>
#include <QString>
#include <QDebug>
#include "TestFormFactorItems.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestFormFactorItems test1;

    return QTest::qExec(&test1, argc, argv);
}
