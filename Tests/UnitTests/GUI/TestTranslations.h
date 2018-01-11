#include "google_test.h"
#include "BeamDistributionItem.h"
#include "BeamItem.h"
#include "DistributionItems.h"
#include "InstrumentItem.h"
#include "ModelPath.h"
#include "ParticleItem.h"
#include "RotationItems.h"
#include "SampleModel.h"
#include "TransformationItem.h"
#include "VectorItem.h"

class TestTranslations : public ::testing::Test
{
public:
    ~TestTranslations();
};

TestTranslations::~TestTranslations() = default;

TEST_F(TestTranslations, test_TranslatePosition)
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem* layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem* layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());
    SessionItem* particle = model.insertNewItem(Constants::ParticleType, layout->index());

    SessionItem* positionItem = particle->getItem(ParticleItem::P_POSITION);
    SessionItem* xItem = positionItem->getItem(VectorItem::P_X);

    EXPECT_EQ(ModelPath::itemPathTranslation(*xItem, multilayer->parent()),
              QString("MultiLayer/Layer/ParticleLayout/Particle/PositionX"));
}

TEST_F(TestTranslations, test_TranslateRotation)
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem* layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem* layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());
    SessionItem* particle = model.insertNewItem(Constants::ParticleType, layout->index());

    SessionItem* transformation = model.insertNewItem(Constants::RotationType, particle->index(),
                                                      -1, ParticleItem::T_TRANSFORMATION);

    SessionItem* rotationItem
        = transformation->setGroupProperty(TransformationItem::P_ROT, Constants::XRotationType);

    SessionItem* angleItem = rotationItem->getItem(XRotationItem::P_ANGLE);
    EXPECT_EQ(ModelPath::itemPathTranslation(*angleItem, multilayer->parent()),
              QString("MultiLayer/Layer/ParticleLayout/Particle/XRotation/Angle"));
}

TEST_F(TestTranslations, test_BeamDistributionNone)
{
    SampleModel model;
    SessionItem* instrument = model.insertNewItem(Constants::GISASInstrumentType);
    SessionItem* beam = instrument->getItem(InstrumentItem::P_BEAM);

    SessionItem* wavelength = beam->getItem(BeamItem::P_WAVELENGTH);

    SessionItem* distr = wavelength->getGroupItem(BeamDistributionItem::P_DISTRIBUTION);
    EXPECT_EQ(distr->modelType(), Constants::DistributionNoneType);
    SessionItem* value = distr->getItem(DistributionNoneItem::P_VALUE);

    EXPECT_EQ(ModelPath::itemPathTranslation(*value, instrument->parent()),
              QString("Instrument/Beam/Wavelength"));

    SessionItem* inclinationAngle = beam->getItem(BeamItem::P_INCLINATION_ANGLE);
    distr = inclinationAngle->getGroupItem(BeamDistributionItem::P_DISTRIBUTION);
    value = distr->getItem(DistributionNoneItem::P_VALUE);

    EXPECT_EQ(ModelPath::itemPathTranslation(*value, instrument->parent()),
              QString("Instrument/Beam/InclinationAngle"));
}
