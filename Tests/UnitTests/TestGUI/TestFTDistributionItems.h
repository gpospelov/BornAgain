#ifndef TESTFTDISTRIBUTIONSITEMS_H
#define TESTFTDISTRIBUTIONSITEMS_H

#include <QtTest>
#include "TransformToDomain.h"
#include "TransformFromDomain.h"
#include "FTDistributions.h"
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
    item.setItemValue(FTDistribution1DItem::P_CORR_LENGTH, 2.0);
    FTDistribution1DCauchy *pdf = dynamic_cast<FTDistribution1DCauchy *>(item.createFTDistribution());
    QVERIFY(pdf->getOmega() == 2.0);
    delete pdf;

    // from domain
    FTDistribution1DCauchy pdf2(3.0);
    FTDistribution1DCauchyItem item2;
    item2.setItemValue(FTDistribution1DGaussItem::P_CORR_LENGTH, pdf2.getOmega());
    QVERIFY(item2.getItemValue(FTDistribution1DGaussItem::P_CORR_LENGTH) == 3.0);
}

#endif
