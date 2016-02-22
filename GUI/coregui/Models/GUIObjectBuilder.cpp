// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GUIObjectBuilder.cpp
//! @brief     Implements class GUIObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "Units.h"
#include "LayerItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "MultiLayerItem.h"
#include "MaterialUtils.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include "ParticleItem.h"
#include "TransformationItem.h"
#include "FormFactorItems.h"
#include "InterferenceFunctionItems.h"
#include "TransformFromDomain.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "ParticleCoreShell.h"
#include "ParticleCoreShellItem.h"
#include "LayerRoughnessItems.h"
#include "VectorItem.h"
#include "ParticleLayoutItem.h"
#include "AngleProperty.h"
#include "ConstKBinAxis.h"
#include "FixedBinAxis.h"
#include "RotationItems.h"
#include "AxesItems.h"
#include "ParticleDistribution.h"
#include "ParticleDistributionItem.h"
#include <QDebug>


GUIObjectBuilder::GUIObjectBuilder()
    : m_sampleModel(0)
{
}


ParameterizedItem *GUIObjectBuilder::populateSampleModel(SampleModel *sampleModel,
                                       const GISASSimulation &simulation, const QString &sampleName)
{
    std::unique_ptr<ISample> P_sample;
    if(simulation.getSampleBuilder()) {
        P_sample.reset(simulation.getSampleBuilder()->buildSample());
    } else if(simulation.getSample()) {
        P_sample.reset(simulation.getSample()->clone());
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::populateSampleModel() -> No valid sample");
    }

    return populateSampleModel(sampleModel, *P_sample, sampleName);
}

ParameterizedItem *GUIObjectBuilder::populateSampleModel(SampleModel *sampleModel,
                                                         const ISample &sample,
                                                         const QString &sampleName)
{
    Q_ASSERT(sampleModel);

    m_levelToParentItem.clear();

    m_topSampleName = sampleName;
    if(m_topSampleName.isEmpty()) m_topSampleName = sample.getName().c_str();

    m_sampleModel = sampleModel;

    VisitSampleTreePreorder(sample, *this);
    ParameterizedItem *result = m_levelToParentItem[1];

    result->setItemName(m_topSampleName);
    return result;
}

ParameterizedItem *GUIObjectBuilder::populateInstrumentModel(InstrumentModel *instrumentModel,
                                                             const GISASSimulation &simulation,
                                                             const QString &instrumentName)
{
    Q_ASSERT(instrumentModel);
    ParameterizedItem *instrumentItem =
            instrumentModel->insertNewItem(Constants::InstrumentType);

    if(instrumentName.isEmpty()) {
        instrumentItem->setItemName(simulation.getInstrument().getName().c_str());
    } else {
        instrumentItem->setItemName(instrumentName);
    }

    // beam
    BeamItem *beamItem = dynamic_cast<BeamItem *>(instrumentModel->insertNewItem(
                Constants::BeamType,
                instrumentModel->indexOfItem(instrumentItem)));

    TransformFromDomain::setItemFromSample(beamItem, simulation);

    // detector
    DetectorItem *detectorItem = dynamic_cast<DetectorItem *>(instrumentModel->insertNewItem(
        Constants::DetectorType, instrumentModel->indexOfItem(instrumentItem)));
    TransformFromDomain::setItemFromSample(detectorItem, simulation);

    // detector masks
    TransformFromDomain::setDetectorMasks(detectorItem, simulation);


    return instrumentItem;
}


void GUIObjectBuilder::visit(const ParticleLayout *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleLayout *)"  << getLevel();
    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *item(0);
    if (parent) {
        item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType,
                                         m_sampleModel->indexOfItem(parent));
    } else {
        item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType);
    }

    ComboProperty approx_prop;
    approx_prop << "Decoupling Approximation"
                << "Size Space Coupling Approximation";
    ILayout::EInterferenceApproximation approx = sample->getApproximation();
    switch(approx)
    {
    case ILayout::DA:
        approx_prop.setValue("Decoupling Approximation");
        break;
    case ILayout::SSCA:
        approx_prop.setValue("Size Space Coupling Approximation");
        break;
    default:
        approx_prop.setValue("Decoupling Approximation");
        break;
    }
    item->setRegisteredProperty(ParticleLayoutItem::P_APPROX,
                                approx_prop.getVariant());
    item->setRegisteredProperty(ParticleLayoutItem::P_TOTAL_DENSITY,
                                sample->getTotalParticleSurfaceDensity());
    m_levelToParentItem[getLevel()] = item;
}

void GUIObjectBuilder::visit(const Layer *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Layer *)"  << getLevel();
    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);

    const MultiLayer *multilayer =
            dynamic_cast<const MultiLayer *>(m_itemToSample[parent]);
    Q_ASSERT(multilayer);
    int layer_index = multilayer->getIndexOfLayer(sample);
    Q_ASSERT(layer_index != -1);
    const LayerInterface *interface =
            multilayer->getLayerTopInterface(layer_index);

    ParameterizedItem *layerItem = m_sampleModel->insertNewItem(
        Constants::LayerType, m_sampleModel->indexOfItem(parent));
    layerItem->setRegisteredProperty(LayerItem::P_MATERIAL,
        createMaterialFromDomain(sample->getMaterial()).getVariant());

    TransformFromDomain::setItemFromSample(layerItem, sample, interface);

    m_levelToParentItem[getLevel()] = layerItem;
}

void GUIObjectBuilder::visit(const LayerInterface *)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerInterface *)"  << getLevel();

}

void GUIObjectBuilder::visit(const MultiLayer *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const MultiLayer *)" << getLevel();

    ParameterizedItem *item =
            m_sampleModel->insertNewItem(Constants::MultiLayerType);
    item->setItemName(sample->getName().c_str());
    item->setRegisteredProperty(MultiLayerItem::P_CROSS_CORR_LENGTH,
                                sample->getCrossCorrLength());
    m_levelToParentItem[getLevel()] = item;
    m_itemToSample[item] = sample;
}

void GUIObjectBuilder::visit(const Particle *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Particle *)" << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);

    ParameterizedItem *particleItem(0);
    if (parent->modelType() == Constants::ParticleCoreShellType) {
        const ParticleCoreShell *coreshell
            = dynamic_cast<const ParticleCoreShell *>(m_itemToSample[parent]);
        Q_ASSERT(coreshell);
        if (sample == coreshell->getCoreParticle()) {
            particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                        m_sampleModel->indexOfItem(parent), -1,
                                                        ParameterizedItem::PortInfo::PORT_0);
        } else if (sample == coreshell->getShellParticle()) {
            particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                        m_sampleModel->indexOfItem(parent), -1,
                                                        ParameterizedItem::PortInfo::PORT_1);
        } else {
            throw GUIHelpers::Error(
                "GUIObjectBuilder::visit"
                "(const Particle *sample) -> Error. Logically should not be here");
        }
    } else if (parent->modelType() == Constants::ParticleCompositionType
               || parent->modelType() == Constants::ParticleLayoutType
               || parent->modelType() == Constants::ParticleDistributionType) {
        particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                    m_sampleModel->indexOfItem(parent));
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
                                "(const Particle *sample) -> Logic error.");
    }

    buildPositionInfo(particleItem, sample);

    particleItem->setRegisteredProperty(ParticleItem::P_ABUNDANCE, sample->getAbundance());
    particleItem->setRegisteredProperty(ParticleItem::P_MATERIAL,
        createMaterialFromDomain(sample->getMaterial()).getVariant());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const ParticleDistribution *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleDistribution *)" << getLevel();

    ParameterizedItem *layoutItem = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(layoutItem);
    ParameterizedItem *particle_distribution_item = m_sampleModel->insertNewItem(
        Constants::ParticleDistributionType, m_sampleModel->indexOfItem(layoutItem));
    Q_ASSERT(particle_distribution_item);

    TransformFromDomain::setItemFromSample(particle_distribution_item, sample);

    m_levelToParentItem[getLevel()] = particle_distribution_item;
    m_itemToSample[particle_distribution_item] = sample;
}

void GUIObjectBuilder::visit(const ParticleCoreShell *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleCoreShell *)" << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);

    ParameterizedItem *coreshellItem = m_sampleModel->insertNewItem(
        Constants::ParticleCoreShellType, m_sampleModel->indexOfItem(parent));
    coreshellItem->setRegisteredProperty(ParticleItem::P_ABUNDANCE, sample->getAbundance());

    buildPositionInfo(coreshellItem, sample);

    m_levelToParentItem[getLevel()] = coreshellItem;
    m_itemToSample[coreshellItem] = sample;
}

void GUIObjectBuilder::visit(const ParticleComposition *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleComposition *)" << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);
    ParameterizedItem *particle_composition_item = m_sampleModel->insertNewItem(
        Constants::ParticleCompositionType, m_sampleModel->indexOfItem(parent));
    particle_composition_item->setRegisteredProperty(ParticleItem::P_ABUNDANCE,
                                                     sample->getAbundance());

    buildPositionInfo(particle_composition_item, sample);

    m_levelToParentItem[getLevel()] = particle_composition_item;
    m_itemToSample[particle_composition_item] = sample;
}

void GUIObjectBuilder::visit(const FormFactorAnisoPyramid *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::AnisoPyramidType);
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_LENGTH,
                                  sample->getLength());
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_WIDTH,
                                  sample->getWidth());
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_HEIGHT,
                                  sample->getHeight());
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_ALPHA,
                                  Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorBox *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::BoxType);
    ffItem->setRegisteredProperty(BoxItem::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(BoxItem::P_WIDTH, sample->getWidth());
    ffItem->setRegisteredProperty(BoxItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCone *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::ConeType);
    ffItem->setRegisteredProperty(ConeItem::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(ConeItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(ConeItem::P_ALPHA,
                                  Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCone6 *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Cone6Type);
    ffItem->setRegisteredProperty(Cone6Item::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(Cone6Item::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(Cone6Item::P_ALPHA,
                                  Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCuboctahedron *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::CuboctahedronType);
    ffItem->setRegisteredProperty(CuboctahedronItem::P_LENGTH,
                                  sample->getLength());
    ffItem->setRegisteredProperty(CuboctahedronItem::P_HEIGHT,
                                  sample->getHeight());
    ffItem->setRegisteredProperty(CuboctahedronItem::P_HEIGHT_RATIO,
                                  sample->getHeightRatio());
    ffItem->setRegisteredProperty(CuboctahedronItem::P_ALPHA,
                                  Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCylinder *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::CylinderType);
    ffItem->setRegisteredProperty(CylinderItem::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(CylinderItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorEllipsoidalCylinder *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
       ParticleItem::P_FORM_FACTOR, Constants::EllipsoidalCylinderType);
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_RADIUS_X,
                                  sample->getRadiusX());
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_RADIUS_Y,
                                  sample->getRadiusY());
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_HEIGHT,
                                  sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorFullSphere *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::FullSphereType);
    ffItem->setRegisteredProperty(FullSphereItem::P_RADIUS,
                                  sample->getRadius());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorFullSpheroid *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::FullSpheroidType);
    ffItem->setRegisteredProperty(FullSpheroidItem::P_RADIUS,
                                  sample->getRadius());
    ffItem->setRegisteredProperty(FullSpheroidItem::P_HEIGHT,
                                  sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorHemiEllipsoid *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::HemiEllipsoidType);
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_RADIUS_X,
                                  sample->getRadiusX());
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_RADIUS_Y,
                                  sample->getRadiusY());
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_HEIGHT,
                                  sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorPrism3 *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Prism3Type);
    ffItem->setRegisteredProperty(Prism3Item::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(Prism3Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorPrism6 *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Prism6Type);
    ffItem->setRegisteredProperty(Prism6Item::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(Prism6Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorPyramid *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::PyramidType);
    ffItem->setRegisteredProperty(PyramidItem::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(PyramidItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(PyramidItem::P_ALPHA,
                                  Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorRipple1 *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Ripple1Type);
    ffItem->setRegisteredProperty(Ripple1Item::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(Ripple1Item::P_WIDTH, sample->getWidth());
    ffItem->setRegisteredProperty(Ripple1Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorRipple2 *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Ripple2Type);
    ffItem->setRegisteredProperty(Ripple2Item::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(Ripple2Item::P_WIDTH, sample->getWidth());
    ffItem->setRegisteredProperty(Ripple2Item::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(Ripple2Item::P_ASYMMETRY,
                                  sample->getAsymmetry());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTetrahedron *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TetrahedronType);
    ffItem->setRegisteredProperty(TetrahedronItem::P_LENGTH,
                                  sample->getLength());
    ffItem->setRegisteredProperty(TetrahedronItem::P_HEIGHT,
                                  sample->getHeight());
    ffItem->setRegisteredProperty(TetrahedronItem::P_ALPHA,
                                  Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedCube *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TruncatedCubeType);
    ffItem->setRegisteredProperty(TruncatedCubeItem::P_LENGTH,
                                  sample->getLength());
    ffItem->setRegisteredProperty(TruncatedCubeItem::P_REMOVED_LENGTH,
                                  sample->getRemovedLength());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedSphere *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TruncatedSphereType);
    ffItem->setRegisteredProperty(TruncatedSphereItem::P_RADIUS,
                                  sample->getRadius());
    ffItem->setRegisteredProperty(TruncatedSphereItem::P_HEIGHT,
                                  sample->getHeight());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedSpheroid *sample)
{
    ParameterizedItem *particleItem = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(
                ParticleItem::P_FORM_FACTOR, Constants::TruncatedSpheroidType);
    ffItem->setRegisteredProperty(TruncatedSpheroidItem::P_RADIUS,
                                  sample->getRadius());
    ffItem->setRegisteredProperty(TruncatedSpheroidItem::P_HEIGHT,
                                  sample->getHeight());
    ffItem->setRegisteredProperty(TruncatedSpheroidItem::P_HFC,
                                  sample->getHeightFlattening());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const InterferenceFunctionRadialParaCrystal *sample)
{
    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunctionRadialParaCrystalType, m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[getLevel()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DParaCrystal *sample)
{
    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DParaCrystalType, m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[getLevel()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction1DLattice *sample)
{
    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction1DLatticeType, m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[getLevel()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DLattice *sample)
{
    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DLatticeType, m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[getLevel()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunctionNone *)
{
    qDebug() << "GUIObjectBuilder::visit(const InterferenceFunctionNone *)"
             << getLevel();
}

void GUIObjectBuilder::visit(const LayerRoughness *)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerRoughness *)" << getLevel();
}

void GUIObjectBuilder::visit(const RotationX *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationX *)" << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);

    ParameterizedItem *transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent));
    ParameterizedItem *p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::XRotationType);
    p_rotationItem->setRegisteredProperty(XRotationItem::P_ANGLE,
                                          Units::rad2deg(sample->getAngle()) );
    m_levelToParentItem[getLevel()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationY *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationY *)" << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel() - 1];
    Q_ASSERT(parent);

    ParameterizedItem *transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent));
    ParameterizedItem *p_rotationItem = transformation_item->setGroupProperty(
        TransformationItem::P_ROT, Constants::YRotationType);
    p_rotationItem->setRegisteredProperty(YRotationItem::P_ANGLE,
                                          Units::rad2deg(sample->getAngle()));
    m_levelToParentItem[getLevel()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationZ *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationZ *)" << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);

    ParameterizedItem *transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent));
    ParameterizedItem *p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::ZRotationType);
    p_rotationItem->setRegisteredProperty(ZRotationItem::P_ANGLE,
                                          Units::rad2deg(sample->getAngle()) );
    m_levelToParentItem[getLevel()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationEuler *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationEuler *)" << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);

    ParameterizedItem *transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent));
    ParameterizedItem *p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::EulerRotationType);
    p_rotationItem->setRegisteredProperty(EulerRotationItem::P_ALPHA,
                                          Units::rad2deg(sample->getAlpha()) );
    p_rotationItem->setRegisteredProperty(EulerRotationItem::P_BETA,
                                          Units::rad2deg(sample->getBeta()) );
    p_rotationItem->setRegisteredProperty(EulerRotationItem::P_GAMMA,
                                          Units::rad2deg(sample->getGamma()) );
    m_levelToParentItem[getLevel()] = transformation_item;
}

void GUIObjectBuilder::buildPositionInfo(ParameterizedItem *particleItem, const IParticle *sample)
{
    kvector_t position = sample->getPosition();
    ParameterizedItem *p_position_item = particleItem->getSubItems()[ParticleItem::P_POSITION];
    p_position_item->setRegisteredProperty(VectorItem::P_X, position.x());
    p_position_item->setRegisteredProperty(VectorItem::P_Y, position.y());
    p_position_item->setRegisteredProperty(VectorItem::P_Z, position.z());
}

MaterialProperty GUIObjectBuilder::createMaterialFromDomain(
        const IMaterial *material)
{
    QString materialName = m_topSampleName + QString("_")
            + QString(material->getName().c_str());

    MaterialProperty materialProperty =
            MaterialEditor::getMaterialProperty(materialName);
    if(materialProperty.isDefined()) return materialProperty;

    MaterialModel *model = MaterialEditor::getMaterialModel();

    if(material->isScalarMaterial()) {
      complex_t rindex = material->getRefractiveIndex();
      MaterialItem *materialItem  =
              model->addMaterial(materialName, 1-rindex.real(),rindex.imag());
      return MaterialProperty(materialItem->getIdentifier());
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::createMaterialFromDomain()"
                                " -> Not implemented.");
    }
}
