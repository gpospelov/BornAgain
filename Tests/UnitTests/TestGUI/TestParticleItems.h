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
#include "MaterialSvc.h"
#include "MaterialModel.h"
#include "GroupProperty.h"
#include "FormFactorItems.h"


class TestParticleItems : public QObject {
    Q_OBJECT

private slots:
    void test_ParticleToDomain();
    void test_FormFactorGroupProperty();

};

inline void TestParticleItems::test_ParticleToDomain()
{
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
}


inline void TestParticleItems::test_FormFactorGroupProperty()
{
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


}



#endif
