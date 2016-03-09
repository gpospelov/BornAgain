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
    LayerBasicRoughnessItem roughnessItem;
    roughnessItem.setChildValue(LayerBasicRoughnessItem::P_SIGMA, 10.0);
    roughnessItem.setChildValue(LayerBasicRoughnessItem::P_HURST, 20.0);
    roughnessItem.setChildValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH, 30.0);

    auto P_roughness = TransformToDomain::createLayerRoughness(roughnessItem);
    QCOMPARE(P_roughness->getSigma(), roughnessItem.getChildValue(LayerBasicRoughnessItem::P_SIGMA).toDouble());
    QCOMPARE(P_roughness->getHurstParameter(), roughnessItem.getChildValue(LayerBasicRoughnessItem::P_HURST).toDouble());
    QCOMPARE(P_roughness->getLatteralCorrLength(), roughnessItem.getChildValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());

    LayerZeroRoughnessItem zeroRoughnessItem;
    QVERIFY(TransformToDomain::createLayerRoughness(zeroRoughnessItem) == nullptr);
}

inline void TestLayerRoughnessItems::test_LayerRoughnessFromDomain()
{
    LayerRoughness roughness(10.0, 20.0, 30.0);
    LayerBasicRoughnessItem roughnessItem;
    TransformFromDomain::setItemFromSample(&roughnessItem, &roughness);
    QCOMPARE(roughness.getSigma(), roughnessItem.getChildValue(LayerBasicRoughnessItem::P_SIGMA).toDouble());
    QCOMPARE(roughness.getHurstParameter(), roughnessItem.getChildValue(LayerBasicRoughnessItem::P_HURST).toDouble());
    QCOMPARE(roughness.getLatteralCorrLength(), roughnessItem.getChildValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());
}


#endif

