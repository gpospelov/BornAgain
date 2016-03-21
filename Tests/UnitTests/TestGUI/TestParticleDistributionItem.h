#ifndef TESTPARTICLEDISTRIBUTIONITEM_H
#define TESTPARTICLEDISTRIBUTIONITEM_H


#include <QtTest>
#include "SampleModel.h"
#include "ParticleDistributionItem.h"
#include "ComboProperty.h"
#include <QDebug>

class TestParticleDistributionItem : public QObject {
    Q_OBJECT

private slots:
    void test_InitialState();
    void test_AddParticle();

};

inline void TestParticleDistributionItem::test_InitialState()
{
    SampleModel model;
    SessionItem *item = model.insertNewItem(Constants::ParticleDistributionType);

    QCOMPARE(item->displayName(), Constants::ParticleDistributionType);
    QCOMPARE(item->displayName(), item->itemName());
    QCOMPARE(item->childItems().size(), 5); // xpos, ypos, P_ABUNDANCE, P_DISTRIBUTION, P_DISTRIBUTED_PARAMETER
    QCOMPARE(item->defaultTag(), ParticleDistributionItem::T_PARTICLES);
    QCOMPARE(item->acceptableDefaultItemTypes(),
             QVector<QString>() << Constants::ParticleType
             << Constants::ParticleCoreShellType << Constants::ParticleCompositionType);

    ComboProperty prop = item->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();

    QCOMPARE(prop.getValues(), QStringList() << QStringLiteral("None"));
    QCOMPARE(prop.getValue(), QStringLiteral("None"));
    QVERIFY(prop.getCachedValue().isEmpty());
}

inline void TestParticleDistributionItem::test_AddParticle()
{
    SampleModel model;
    SessionItem *item = model.insertNewItem(Constants::ParticleDistributionType);
    SessionItem *particle = model.insertNewItem(Constants::ParticleType, item->index());

    QCOMPARE(item->childItems().size(), 6); // xpos, ypos, P_ABUNDANCE, P_DISTRIBUTION, T_PARTICLES, P_DISTRIBUTED_PARAMETER

    ComboProperty prop = item->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();
    qDebug() << prop.getValues();

}


#endif
