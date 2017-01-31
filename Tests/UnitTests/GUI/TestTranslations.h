#include <QtTest>
#include "SampleModel.h"
#include "ParticleItem.h"
#include "VectorItem.h"
#include "ModelPath.h"
#include <QDebug>

class TestTranslations : public QObject {
    Q_OBJECT

private slots:
    void test_TranslatePosition();
//    void test_TranslateRotation();
};

inline void TestTranslations::test_TranslatePosition()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());
    SessionItem *particle = model.insertNewItem(Constants::ParticleType, layout->index());

    SessionItem* positionItem = particle->getItem(ParticleItem::P_POSITION);
    SessionItem* xItem = positionItem->getItem(VectorItem::P_X);

    QCOMPARE(ModelPath::itemPathTranslation(*xItem, multilayer->parent()),
             "MultiLayer/Layer/ParticleLayout/Particle/PositionX");
}

//inline void TestTranslations::test_TranslateRotation()
//{
//    SampleModel model;
//    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
//    SessionItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
//    SessionItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());
//    SessionItem *particle = model.insertNewItem(Constants::ParticleType, layout->index());

//    SessionItem* transformation_item = model.insertNewItem(
//        Constants::TransformationType, particle->index(), -1, ParticleItem::T_TRANSFORMATION);

//    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
//                TransformationItem::P_ROT, Constants::XRotationType);
//    p_rotationItem->setItemValue(XRotationItem::P_ANGLE,
//                                          Units::rad2deg(sample->getAngle()) );


//}
