#ifndef TESTPARTICLEITEMS_H
#define TESTPARTICLEITEMS_H


#include <QtTest>
#include "Particle.h"
#include "ParticleLayout.h"
#include "ParticleCoreShell.h"
#include "SessionModel.h"
#include "GUIObjectBuilder.h"
#include "ParticleItem.h"
#include "TransformToDomain.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"


class TestParticleItems : public QObject {
    Q_OBJECT

private slots:
    void test_ParticleToDomain();
};


inline void TestParticleItems::test_ParticleToDomain()
{
    MaterialModel materialModel;
    MaterialEditor editor(&materialModel);
    Q_UNUSED(editor);
    ParticleItem item;
    item.setRegisteredProperty(ParticleItem::P_DEPTH, 10.0);
    item.setRegisteredProperty(ParticleItem::P_ABUNDANCE, 5.0);
    double depth, abundance;
    Particle *particle = TransformToDomain::createParticle(item, depth, abundance);
    QCOMPARE(depth, 10.0);
    QCOMPARE(abundance, 5.0);
    Q_UNUSED(particle);
}

#endif
