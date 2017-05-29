#include <QtTest>
#include "InterferenceFunctionItems.h"
#include "GroupProperty.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FTDistributions2D.h"
#include "FTDistributionItems.h"
#include "TransformFromDomain.h"
#include "Lattice2D.h"
#include "Lattice2DItems.h"
#include "SampleModel.h"
#include "Units.h"

class TestParaCrystalItems : public QObject {
    Q_OBJECT

private slots:

    void test_Para2D_fromToDomain();
    void test_Inference2DRotationAngleToggle();
};

inline void TestParaCrystalItems::test_Para2D_fromToDomain()
{
    double length1(10.0), length2(20.0), angle(45.0), xi(90.0);
    double damping_length(1000.0), domain_size1(50.0), domain_size2(100.0);

    InterferenceFunction2DParaCrystal orig(length1, length2, angle * Units::deg, xi * Units::deg,
                                           damping_length);
    orig.setDomainSizes(domain_size1, domain_size2);

    double clength_x(1.0), clength_y(2.0), gamma(3.0);
    orig.setProbabilityDistributions(
        FTDistribution2DCauchy(clength_x, clength_y, gamma * Units::deg),
        FTDistribution2DGauss(clength_x, clength_y, gamma * Units::deg));

    // from domain
    InterferenceFunction2DParaCrystalItem item;
    TransformFromDomain::setItemFromSample(&item, &orig);

    QCOMPARE(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH).toDouble(),
             orig.dampingLength());
    QCOMPARE(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1).toDouble(),
             orig.domainSizes()[0]);
    QCOMPARE(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2).toDouble(),
             orig.domainSizes()[1]);
    QCOMPARE(orig.integrationOverXi(), false);
    QCOMPARE(item.getItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION).toBool(),
             orig.integrationOverXi());

    SessionItem* latticeItem = item.getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
    QCOMPARE(latticeItem->modelType(), Constants::BasicLatticeType);
    QCOMPARE(latticeItem->getItemValue(BasicLatticeItem::P_LATTICE_LENGTH1).toDouble(), length1);
    QCOMPARE(latticeItem->getItemValue(BasicLatticeItem::P_LATTICE_LENGTH2).toDouble(), length2);
    QCOMPARE(latticeItem->getItemValue(BasicLatticeItem::P_LATTICE_ANGLE).toDouble(), angle);
    QCOMPARE(latticeItem->getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble(), xi);

    SessionItem* pdfItem1 = item.getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF1);
    QCOMPARE(pdfItem1->modelType(), Constants::FTDistribution2DCauchyType);
    QCOMPARE(pdfItem1->getItemValue(FTDistribution2DItem::P_OMEGA_X).toDouble(), clength_x);
    QCOMPARE(pdfItem1->getItemValue(FTDistribution2DItem::P_OMEGA_Y).toDouble(), clength_y);
    QCOMPARE(pdfItem1->getItemValue(FTDistribution2DItem::P_GAMMA).toDouble(), gamma);

    SessionItem* pdfItem2 = item.getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF2);
    QCOMPARE(pdfItem2->modelType(), Constants::FTDistribution2DGaussType);
    QCOMPARE(pdfItem2->getItemValue(FTDistribution2DItem::P_OMEGA_X).toDouble(), clength_x);
    QCOMPARE(pdfItem2->getItemValue(FTDistribution2DItem::P_OMEGA_Y).toDouble(), clength_y);
    QCOMPARE(pdfItem2->getItemValue(FTDistribution2DItem::P_GAMMA).toDouble(), gamma);

    // to domain
    auto ifun = item.createInterferenceFunction();
    std::unique_ptr<InterferenceFunction2DParaCrystal> domain(
        dynamic_cast<InterferenceFunction2DParaCrystal*>(ifun->clone()));
    QCOMPARE(domain->integrationOverXi(), orig.integrationOverXi());
    QCOMPARE(domain->domainSizes(), orig.domainSizes());
    QCOMPARE(domain->dampingLength(), orig.dampingLength());
    QCOMPARE(domain->lattice().length1(), orig.lattice().length1());
    QCOMPARE(domain->lattice().length2(), orig.lattice().length2());
    QCOMPARE(domain->lattice().latticeAngle(), orig.lattice().latticeAngle());
    QCOMPARE(domain->lattice().rotationAngle(), orig.lattice().rotationAngle());
}

inline void TestParaCrystalItems::test_Inference2DRotationAngleToggle()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    SessionItem *interference = model.insertNewItem(Constants::InterferenceFunction2DParaCrystalType,
                                                       layout->index(), -1, ParticleLayoutItem::T_INTERFERENCE);

    // rotation (xi) should be disabled if integration is on
    interference->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, true);

    SessionItem *angleItem = interference->getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
            ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);

    QVERIFY(angleItem->isEnabled() == false);

    // rotation (xi) should be enabled if integration is off
    interference->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, false);

    angleItem = interference->getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE)
            ->getItem(Lattice2DItem::P_LATTICE_ROTATION_ANGLE);

    QVERIFY(angleItem->isEnabled() == true);

}
