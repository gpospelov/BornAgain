#include <QtTest>
#include "TransformToDomain.h"
#include "TransformFromDomain.h"
#include "FTDistributions1D.h"
#include "FTDistributionItems.h"

class TestFTDistributionItems : public QObject {
    Q_OBJECT

private slots:
    void test_FTDistribution1DCauchy();
};


inline void TestFTDistributionItems::test_FTDistribution1DCauchy()
{
    // to domain
    FTDistribution1DCauchyItem item;
    item.setItemValue(FTDistribution1DItem::P_OMEGA, 2.0);
    auto pdf = item.createFTDistribution();
    const FTDistribution1DCauchy *cauchy = dynamic_cast<FTDistribution1DCauchy *>(pdf.get());
    QVERIFY(cauchy->omega() == 2.0);

    // from domain
    FTDistribution1DCauchy pdf2(3.0);
    FTDistribution1DCauchyItem item2;
    item2.setItemValue(FTDistribution1DGaussItem::P_OMEGA, pdf2.omega());
    QVERIFY(item2.getItemValue(FTDistribution1DGaussItem::P_OMEGA) == 3.0);
}
