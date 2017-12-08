#include "google_test.h"
#include <QString>
#include <QCoreApplication>
#include "ComboProperty.h"
#include "TestComboProperty.h"
#include <memory>

#include "ErrorStreamRedirect.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    QMetaType::registerComparators<ComboProperty>();

    ::testing::InitGoogleTest(&argc, argv);

    // redirect std::cerr stream
    std::stringstream oss;
    ErrorStreamRedirect redirecter( oss.rdbuf() );
    (void)redirecter;

    // run all google tests
    return RUN_ALL_TESTS();
}
