#ifndef _LAYERROUGHNESSITEMS_H
#define _LAYERROUGHNESSITEMS_H

#include <QtTest>
#include "LayerRoughness.h"
#include "LayerRoughnessItems.h"
#include "TransformToDomain.h"
#include "TransformFromDomain.h"

class TestLayerRoughnessItems : public QObject {
    Q_OBJECT

private slots:
    void test_LayerRoughnessToDomain();
    void test_LayerRoughnessFromDomain();
};

inline void TestLayerRoughnessItems::test_LayerRoughnessToDomain()
{
    LayerRoughnessItem roughnessItem;
    roughnessItem.setRegisteredProperty(LayerRoughnessItem::P_SIGMA, 10.0);
    roughnessItem.setRegisteredProperty(LayerRoughnessItem::P_HURST, 20.0);
    roughnessItem.setRegisteredProperty(LayerRoughnessItem::P_LATERAL_CORR_LENGTH, 30.0);

    LayerRoughness *roughness = TransformToDomain::createLayerRoughness(roughnessItem);
    QCOMPARE(roughness->getSigma(), roughnessItem.getRegisteredProperty(LayerRoughnessItem::P_SIGMA).toDouble());
    QCOMPARE(roughness->getHurstParameter(), roughnessItem.getRegisteredProperty(LayerRoughnessItem::P_HURST).toDouble());
    QCOMPARE(roughness->getLatteralCorrLength(), roughnessItem.getRegisteredProperty(LayerRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());
    delete roughness;

    LayerZeroRoughnessItem zeroRoughnessItem;
    QVERIFY(TransformToDomain::createLayerRoughness(zeroRoughnessItem) == 0);
}

inline void TestLayerRoughnessItems::test_LayerRoughnessFromDomain()
{
    LayerRoughness roughness(10.0, 20.0, 30.0);
    LayerRoughnessItem roughnessItem;
    TransformFromDomain::setItemFromSample(&roughnessItem, &roughness);
    QCOMPARE(roughness.getSigma(), roughnessItem.getRegisteredProperty(LayerRoughnessItem::P_SIGMA).toDouble());
    QCOMPARE(roughness.getHurstParameter(), roughnessItem.getRegisteredProperty(LayerRoughnessItem::P_HURST).toDouble());
    QCOMPARE(roughness.getLatteralCorrLength(), roughnessItem.getRegisteredProperty(LayerRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());
}


#endif

