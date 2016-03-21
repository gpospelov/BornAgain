#ifndef TESTPARTICLEITEM_H
#define TESTPARTICLEITEM_H


#include <QtTest>
#include "SampleModel.h"
#include "SessionItem.h"
#include "ParticleItem.h"
#include "GroupItem.h"


class TestParticleItem : public QObject {
    Q_OBJECT

private slots:
    void test_InitialState();
};

inline void TestParticleItem::test_InitialState()
{
    SampleModel model;
    SessionItem *item = model.insertNewItem(Constants::ParticleType);

    QCOMPARE(item->displayName(), Constants::ParticleType);
    QCOMPARE(item->displayName(), item->itemName());
    QCOMPARE(item->childItems().size(), 6); // xpos, ypos, P_FORM_FACTOR, P_MATERIAL, P_ABUNDANCE, P_POSITION
    QCOMPARE(item->defaultTag(), ParticleItem::T_TRANSFORMATION);

    GroupItem *group = dynamic_cast<GroupItem *>(item->getItem(ParticleItem::P_FORM_FACTOR));
    QCOMPARE(group->displayName(), ParticleItem::P_FORM_FACTOR);
    QCOMPARE(group->childItems().size(), 1);




//    QCOMPARE(item->acceptableDefaultItemTypes(),
//             QVector<QString>() << Constants::ParticleType
//             << Constants::ParticleCoreShellType << Constants::ParticleCompositionType);

}


//inline void TestParticleItems::test_ParticleToDomain()
//{
//    MaterialModel materialModel;
//    MaterialEditor editor(&materialModel);
//    Q_UNUSED(editor);
//    ParticleItem item;
//    item.setRegisteredProperty(ParticleItem::P_DEPTH, 10.0);
//    item.setRegisteredProperty(ParticleItem::P_ABUNDANCE, 5.0);
//    double depth, abundance;
//    Particle *particle = TransformToDomain::createParticle(item, depth, abundance);
//    QCOMPARE(depth, 10.0);
//    QCOMPARE(abundance, 5.0);
//    Q_UNUSED(particle);
//}


//inline void TestParticleItems::test_FormFactorGroupProperty()
//{
//    // FIXME remove MaterialEditor and model from SessionItem
//    MaterialModel materialModel;
//    MaterialEditor editor(&materialModel);
//    Q_UNUSED(editor);

//    ParticleItem item;

//    FancyGroupProperty *group_property = item.getRegisteredProperty(ParticleItem::P_FORM_FACTOR).value<FancyGroupProperty *>();
//    QCOMPARE(group_property->type(), FancyGroupProperty::SelectableGroupType);
//    QCOMPARE(item.getSubItems().size(), 1);

//    // check that request for new subItem generates item of correct modelType and
//    // correct signals (one propertyItemChanged, and no propertyChanged)
//    QStringList formfactors;
//    formfactors << Constants::AnisoPyramidType
//                << Constants::BoxType
//                << Constants::ConeType
//                << Constants::Cone6Type
//                << Constants::CuboctahedronType
//                << Constants::CylinderType
//                << Constants::EllipsoidalCylinderType
//                << Constants::FullSphereType
//                << Constants::FullSpheroidType
//                << Constants::HemiEllipsoidType
//                << Constants::Prism3Type
//                << Constants::Prism6Type
//                << Constants::PyramidType
//                << Constants::Ripple1Type
//                << Constants::Ripple2Type
//                << Constants::TetrahedronType
//                << Constants::TruncatedSphereType
//                << Constants::TruncatedSpheroidType;
//    foreach(QString ff_name, formfactors) {
//        QSignalSpy spyItem(&item, SIGNAL(propertyChanged(QString)));
//        QSignalSpy spyPropertyItem(&item, SIGNAL(propertyItemChanged(QString)));
//        SessionItem *ffItem = item.setFancyGroupProperty(ParticleItem::P_FORM_FACTOR, ff_name);
//        QVERIFY(ffItem);
//        QCOMPARE(item.getSubItems().size(), 1);
//        QCOMPARE(ffItem, item.getGroupItem(ParticleItem::P_FORM_FACTOR));

//        QCOMPARE(spyItem.count(), 0);
//        if(ff_name == Constants::AnisoPyramidType) { // default ff
//            QCOMPARE(spyPropertyItem.count(), 0);
//        } else {
//            QCOMPARE(spyPropertyItem.count(), 1);
//            QList<QVariant> arguments = spyPropertyItem.takeFirst(); // take the first signal
//            QCOMPARE(arguments.at(0).toString(), ParticleItem::P_FORM_FACTOR);
//        }

//        QCOMPARE(ffItem->modelType(), ff_name);
//    }

//    // checks that change in subItem properties has no affect on signals of ParticleItem
//    SessionItem *cylinderItem = item.setFancyGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::CylinderType);
//    QSignalSpy spyItem(&item, SIGNAL(propertyChanged(QString)));
//    QSignalSpy spyPropertyItem(&item, SIGNAL(propertyItemChanged(QString)));
//    cylinderItem->setRegisteredProperty(CylinderItem::P_RADIUS, 99.9);
//    QCOMPARE(spyItem.count(), 0);
//    QCOMPARE(spyPropertyItem.count(), 0);


//}



#endif
