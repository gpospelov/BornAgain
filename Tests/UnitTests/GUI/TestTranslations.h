#include <QtTest>
#include "SampleModel.h"
#include "ParticleItem.h"
#include "VectorItem.h"
#include "ModelPath.h"
#include "TransformationItem.h"
#include "RotationItems.h"
#include "BeamItem.h"
#include "BeamDistributionItem.h"
#include "DistributionItems.h"
#include <QDebug>

class TestTranslations : public QObject {
    Q_OBJECT

private slots:
    void test_TranslatePosition();
    void test_TranslateRotation();
    void test_BeamDistributionNone();
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
             QString("MultiLayer/Layer/ParticleLayout/Particle/PositionX"));
}

inline void TestTranslations::test_TranslateRotation()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());
    SessionItem *particle = model.insertNewItem(Constants::ParticleType, layout->index());

    SessionItem* transformation= model.insertNewItem(
        Constants::TransformationType, particle->index(), -1, ParticleItem::T_TRANSFORMATION);

    SessionItem* rotationItem = transformation->setGroupProperty(
                TransformationItem::P_ROT, Constants::XRotationType);

    SessionItem *angleItem = rotationItem->getItem(XRotationItem::P_ANGLE);
    QCOMPARE(ModelPath::itemPathTranslation(*angleItem, multilayer->parent()),
             QString("MultiLayer/Layer/ParticleLayout/Particle/XRotation/Angle"));
}

inline void TestTranslations::test_BeamDistributionNone()
{
    SampleModel model;
    SessionItem *instrument = model.insertNewItem(Constants::InstrumentType);
    SessionItem *beam = model.insertNewItem(Constants::BeamType, instrument->index());

    SessionItem* wavelength = beam->getItem(BeamItem::P_WAVELENGTH);

    SessionItem* distr = wavelength->getGroupItem(BeamDistributionItem::P_DISTRIBUTION);
    QCOMPARE(distr->modelType(), Constants::DistributionNoneType);
    SessionItem* value = distr->getItem(DistributionNoneItem::P_VALUE);

    QCOMPARE(ModelPath::itemPathTranslation(*value, instrument->parent()),
             QString("Instrument/Beam/Wavelength"));

    SessionItem* inclinationAngle = beam->getItem(BeamItem::P_INCLINATION_ANGLE);
    distr = inclinationAngle->getGroupItem(BeamDistributionItem::P_DISTRIBUTION);
    value = distr->getItem(DistributionNoneItem::P_VALUE);

    QCOMPARE(ModelPath::itemPathTranslation(*value, instrument->parent()),
             QString("Instrument/Beam/InclinationAngle"));
}
