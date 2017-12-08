#include "google_test.h"
#include <QString>
#include <QCoreApplication>
#include "ComboProperty.h"
#include "TestComboProperty.h"
#include <memory>

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    QMetaType::registerComparators<ComboProperty>();

    ::testing::InitGoogleTest(&argc, argv);

    // run all google tests
    return RUN_ALL_TESTS();
}
