#include <QtTest>
#include "GUIHelpers.h"

class TestGUIHelpers : public QObject {
    Q_OBJECT

private slots:
    void test_VersionString();
};

inline void TestGUIHelpers::test_VersionString()
{
    int vmajor(0), vminor(0), vpatch(0);

    QCOMPARE(true, GUIHelpers::parseVersion(QString("1.5.0"), vmajor, vminor, vpatch));
    QCOMPARE(1, vmajor);
    QCOMPARE(5, vminor);
    QCOMPARE(0, vpatch);

    QCOMPARE(false, GUIHelpers::parseVersion(QString("15.0"), vmajor, vminor, vpatch));

    QString min_version("1.5.0");
    QCOMPARE(GUIHelpers::isVersionMatchMinimal("1.5.0", min_version), true);
    QCOMPARE(GUIHelpers::isVersionMatchMinimal("1.5.1", min_version), true);
    QCOMPARE(GUIHelpers::isVersionMatchMinimal("1.6.0", min_version), true);
    QCOMPARE(GUIHelpers::isVersionMatchMinimal("2.4.9", min_version), true);

    QCOMPARE(GUIHelpers::isVersionMatchMinimal("1.4.9", min_version), false);
    QCOMPARE(GUIHelpers::isVersionMatchMinimal("0.6.9", min_version), false);
}
