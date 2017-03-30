#include "ParticleItem.h"
#include "SampleModel.h"
#include "SessionItem.h"
#include "GroupItem.h"
#include <QtTest>

class TestParticleItem : public QObject
{
    Q_OBJECT

private slots:
    void test_InitialState();
};

inline void TestParticleItem::test_InitialState()
{
    SampleModel model;
    SessionItem* item = model.insertNewItem(Constants::ParticleType);

    QCOMPARE(item->displayName(), Constants::ParticleType);
    QCOMPARE(item->displayName(), item->itemName());
    // xpos, ypos, P_FORM_FACTOR, P_MATERIAL, P_ABUNDANCE, P_POSITION
    QCOMPARE(item->childItems().size(), 6);
    QCOMPARE(item->defaultTag(), ParticleItem::T_TRANSFORMATION);

    GroupItem* group = dynamic_cast<GroupItem*>(item->getItem(ParticleItem::P_FORM_FACTOR));
    QCOMPARE(group->displayName(), ParticleItem::P_FORM_FACTOR);
    QCOMPARE(group->childItems().size(), 1);
}
