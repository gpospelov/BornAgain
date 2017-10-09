#include <QtTest>
#include "ParticleItem.h"
#include "ParticleCoreShellItem.h"
#include "SampleModel.h"
#include "VectorItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleCompositionItem.h"

class TestParticleCoreShell : public QObject {
    Q_OBJECT

private slots:
    void test_propertyAppearance();
    void test_distributionContext();
    void test_compositionContext();
};

//! Checking that adding and removing core/shell leads to enabling/disabling of their position
//! and abundance properties.

inline void TestParticleCoreShell::test_propertyAppearance()
{
    SampleModel model;

    // empty coreshell particle
    SessionItem* coreshell = model.insertNewItem(Constants::ParticleCoreShellType);
    QVERIFY(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    QCOMPARE(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);
    QVERIFY(coreshell->getItem(ParticleItem::P_POSITION)->isEnabled() == true);
    SessionItem* positionItem = coreshell->getItem(ParticleItem::P_POSITION);
    QCOMPARE(positionItem->getItemValue(VectorItem::P_X).toDouble(), 0.0);
    QCOMPARE(positionItem->getItemValue(VectorItem::P_Y).toDouble(), 0.0);
    QCOMPARE(positionItem->getItemValue(VectorItem::P_Z).toDouble(), 0.0);

    // adding core, and checking that abundance is disabled
    SessionItem* core = model.insertNewItem(Constants::ParticleType, coreshell->index(), -1,
                                            ParticleCoreShellItem::T_CORE);
    QVERIFY(core->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);
    QVERIFY(core->getItem(ParticleItem::P_POSITION)->isEnabled() == true);

    // removing core, checking that abundance restored
    coreshell->takeRow(core->parentRow());
    QVERIFY(core->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    QVERIFY(core->getItem(ParticleItem::P_POSITION)->isEnabled() == true);
    delete core;

    // creating shell (not yet attached to the coreshell)
    SessionItem* shell = model.insertNewItem(Constants::ParticleType);
    positionItem = shell->getItem(ParticleItem::P_POSITION);
    // putting some values to position and abundance
    shell->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    positionItem->setItemValue(VectorItem::P_X, 1.0);

    // attaching shell to coreshell and checking abundance disabled
    model.moveParameterizedItem(shell, coreshell, -1, ParticleCoreShellItem::T_SHELL);
    QVERIFY(shell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);
    QVERIFY(shell->getItem(ParticleItem::P_POSITION)->isEnabled() == false);
    // checking that position and abundance values were reset to defaults
    QCOMPARE(positionItem->getItemValue(VectorItem::P_X).toDouble(), 0.0);
    QCOMPARE(shell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing shell and checking abundance, position restored
    coreshell->takeRow(shell->parentRow());
    QVERIFY(shell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    QVERIFY(shell->getItem(ParticleItem::P_POSITION)->isEnabled() == true);
    delete shell;
}

//! Checking that abundance gets disabled in particle distribution context.

inline void TestParticleCoreShell::test_distributionContext()
{
    SampleModel model;

    // coreshell particle
    SessionItem* coreshell = model.insertNewItem(Constants::ParticleCoreShellType);
    coreshell->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    QVERIFY(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    QCOMPARE(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // create distribution, adding coreshell to it
    SessionItem* distribution = model.insertNewItem(Constants::ParticleDistributionType);
    model.moveParameterizedItem(coreshell, distribution, -1, ParticleDistributionItem::T_PARTICLES);
    // checking abundance has switched to defaults
    QVERIFY(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);
    QCOMPARE(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing coreshell
    distribution->takeRow(coreshell->parentRow());
    QVERIFY(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    delete coreshell;
}

//! Checking that abundance gets disabled in particle composition context.

inline void TestParticleCoreShell::test_compositionContext()
{
    SampleModel model;

    // coreshell particle
    SessionItem* coreshell = model.insertNewItem(Constants::ParticleCoreShellType);
    coreshell->setItemValue(ParticleItem::P_ABUNDANCE, 0.2);
    QVERIFY(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    QCOMPARE(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 0.2);

    // create composition, adding coreshell to it
    SessionItem* composition = model.insertNewItem(Constants::ParticleCompositionType);
    model.moveParameterizedItem(coreshell, composition, -1, ParticleCompositionItem::T_PARTICLES);
    // checking abundance has switched to defaults
    QVERIFY(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);
    QCOMPARE(coreshell->getItemValue(ParticleItem::P_ABUNDANCE).toDouble(), 1.0);

    // removing coreshell
    composition->takeRow(coreshell->parentRow());
    QVERIFY(coreshell->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == true);
    delete coreshell;
}

