// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIObjectBuilder.cpp
//! @brief     Implements class GUIObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIObjectBuilder.h"
#include "BeamDistributionItem.h"
#include "BeamItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "Crystal.h"
#include "DetectorItems.h"
#include "DocumentModel.h"
#include "FormFactorItems.h"
#include "FormFactors.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "HomogeneousMaterial.h"
#include "InstrumentModel.h"
#include "IMultiLayerBuilder.h"
#include "Layer.h"
#include "LayerItem.h"
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "MaterialUtils.h"
#include "MesoCrystal.h"
#include "MesoCrystalItem.h"
#include "MultiLayer.h"
#include "MultiLayerItem.h"
#include "ParticleComposition.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayout.h"
#include "ParticleLayoutItem.h"
#include "RectangularDetector.h"
#include "RotationItems.h"
#include "SampleModel.h"
#include "SimulationOptionsItem.h"
#include "SphericalDetector.h"
#include "TransformFromDomain.h"
#include "TransformationItem.h"
#include "InstrumentItem.h"
#include "DetectorItems.h"
#include "Units.h"
#include "VectorItem.h"
#include "Particle.h"
#include "ParticleCoreShell.h"

GUIObjectBuilder::GUIObjectBuilder()
    : m_sampleModel(0)
{
}

SessionItem* GUIObjectBuilder::populateSampleModel(
    SampleModel* p_sample_model, const GISASSimulation& simulation, const QString& sample_name)
{
    std::unique_ptr<GISASSimulation> sim(simulation.clone());
    sim->prepareSimulation();
    return populateSampleModel(p_sample_model,*sim->sample(), sample_name);
}

SessionItem* GUIObjectBuilder::populateSampleModel(
    SampleModel* p_sample_model, const ISample& sample, const QString& sample_name)
{
    Q_ASSERT(p_sample_model);

    m_levelToParentItem.clear();

    m_topSampleName = sample_name;
    if(m_topSampleName.isEmpty()) m_topSampleName = sample.getName().c_str();

    m_sampleModel = p_sample_model;

    VisitNodesPreorder(sample, *this);
    SessionItem* result = m_levelToParentItem[1];

    result->setItemName(m_topSampleName);
    return result;
}

SessionItem* GUIObjectBuilder::populateInstrumentModel(
    InstrumentModel* p_instrument_model,
    const GISASSimulation& simulation, const QString& instrument_name)
{
    Q_ASSERT(p_instrument_model);

    InstrumentItem* p_instrument_item = dynamic_cast<InstrumentItem*>
            (p_instrument_model->insertNewItem(Constants::InstrumentType));

    if(instrument_name.isEmpty()) {
        p_instrument_item->setItemName(simulation.getInstrument().getName().c_str());
    } else {
        p_instrument_item->setItemName(instrument_name);
    }

    // beam
    auto& beam_item = p_instrument_item->item<BeamItem>(InstrumentItem::P_BEAM);
    TransformFromDomain::setItemFromSample(&beam_item, simulation);

    // detector
    TransformFromDomain::setInstrumentDetectorFromSample(p_instrument_item, simulation);

    // detector masks
    TransformFromDomain::setDetectorMasks(p_instrument_item->detectorItem(), simulation);

    return p_instrument_item;
}

SessionItem* GUIObjectBuilder::populateDocumentModel(DocumentModel* p_document_model,
                                                     const GISASSimulation& simulation)
{
    SimulationOptionsItem* p_options_item = dynamic_cast<SimulationOptionsItem*>(
            p_document_model->insertNewItem(Constants::SimulationOptionsType));
    Q_ASSERT(p_options_item);
    if (simulation.getOptions().isIntegrate()) {
        p_options_item->setComputationMethod(Constants::SIMULATION_MONTECARLO);
        p_options_item->setNumberOfMonteCarloPoints(static_cast<int>(simulation.getOptions().getMcPoints()));
    }
    if (simulation.getOptions().useAvgMaterials()) {
        p_options_item->setFresnelMaterialMethod(Constants::AVERAGE_LAYER_MATERIAL);
    }
    if (simulation.getOptions().includeSpecular()) {
        p_options_item->setIncludeSpecularPeak(Constants::Yes);
    }
    return p_options_item;
}


void GUIObjectBuilder::visit(const ParticleLayout* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth()-1];
    SessionItem* p_layout_item(0);
    if (p_parent) {
        p_layout_item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType,
                                         m_sampleModel->indexOfItem(p_parent));
    } else {
        p_layout_item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType);
    }

    ComboProperty approx_prop;
    approx_prop << Constants::LAYOUT_DA << Constants::LAYOUT_SSCA;
    ILayout::EInterferenceApproximation approx = p_sample->getApproximation();
    switch(approx)
    {
    case ILayout::DA:
        approx_prop.setValue(Constants::LAYOUT_DA);
        break;
    case ILayout::SSCA:
        approx_prop.setValue(Constants::LAYOUT_SSCA);
        break;
    }
    p_layout_item->setItemValue(ParticleLayoutItem::P_APPROX, approx_prop.getVariant());
    p_layout_item->setItemValue(ParticleLayoutItem::P_TOTAL_DENSITY,
                       p_sample->totalParticleSurfaceDensity());
    m_levelToParentItem[depth()] = p_layout_item;
}

void GUIObjectBuilder::visit(const Layer* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(p_parent);

    auto p_multilayer = dynamic_cast<const MultiLayer*>(m_itemToSample[p_parent]);
    Q_ASSERT(p_multilayer);
    int layer_index = p_multilayer->indexOfLayer(p_sample);
    Q_ASSERT(layer_index != -1);
    const LayerInterface* p_interface = p_multilayer->layerTopInterface(layer_index);

    SessionItem* p_layer_item = m_sampleModel->insertNewItem(
        Constants::LayerType, m_sampleModel->indexOfItem(p_parent));
    p_layer_item->setItemValue(LayerItem::P_MATERIAL,
        createMaterialFromDomain(p_sample->material()).getVariant());

    TransformFromDomain::setItemFromSample(p_layer_item, p_sample, p_interface);

    m_levelToParentItem[depth()] = p_layer_item;
}

void GUIObjectBuilder::visit(const MultiLayer* p_sample)
{
    SessionItem* p_multilayer_item =
            m_sampleModel->insertNewItem(Constants::MultiLayerType);
    p_multilayer_item->setItemName(p_sample->getName().c_str());
    p_multilayer_item->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, p_sample->crossCorrLength());
    m_levelToParentItem[depth()] = p_multilayer_item;
    m_itemToSample[p_multilayer_item] = p_sample;
}

void GUIObjectBuilder::visit(const Particle* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(p_parent);

    SessionItem* p_particle_item(0);
    if (p_parent->modelType() == Constants::ParticleCoreShellType) {
        const ParticleCoreShell* p_coreshell
            = dynamic_cast<const ParticleCoreShell*>(m_itemToSample[p_parent]);
        Q_ASSERT(p_coreshell);
        if (p_sample == p_coreshell->coreParticle()) {
            p_particle_item = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                        m_sampleModel->indexOfItem(p_parent), -1,
                                                        ParticleCoreShellItem::T_CORE);
            Q_ASSERT(p_particle_item);
        } else if (p_sample == p_coreshell->shellParticle()) {
            p_particle_item = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                        m_sampleModel->indexOfItem(p_parent), -1,
                                                        ParticleCoreShellItem::T_SHELL);
            Q_ASSERT(p_particle_item);
        } else {
            throw GUIHelpers::Error(
                "GUIObjectBuilder::visit"
                "(const Particle* p_sample) -> Error. Logically should not be here");
        }
    } else if (p_parent->modelType() == Constants::ParticleCompositionType
               || p_parent->modelType() == Constants::ParticleLayoutType
               || p_parent->modelType() == Constants::ParticleDistributionType) {
        p_particle_item = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                    m_sampleModel->indexOfItem(p_parent));
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
                                "(const Particle* p_sample) -> Logic error.");
    }

    buildPositionInfo(p_particle_item, p_sample);

    p_particle_item->setItemValue(ParticleItem::P_ABUNDANCE, p_sample->abundance());
    p_particle_item->setItemValue(ParticleItem::P_MATERIAL,
        createMaterialFromDomain(p_sample->material()).getVariant());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const ParticleDistribution* p_sample)
{
    SessionItem* p_layout_item = m_levelToParentItem[depth() - 1];
    Q_ASSERT(p_layout_item);
    SessionItem* p_particle_distribution_item = m_sampleModel->insertNewItem(
        Constants::ParticleDistributionType, m_sampleModel->indexOfItem(p_layout_item));
    Q_ASSERT(p_particle_distribution_item);

    TransformFromDomain::setItemFromSample(p_particle_distribution_item, p_sample);

    m_levelToParentItem[depth()] = p_particle_distribution_item;
    m_itemToSample[p_particle_distribution_item] = p_sample;
}

void GUIObjectBuilder::visit(const ParticleCoreShell* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(p_parent);

    SessionItem* p_coreshell_item = m_sampleModel->insertNewItem(
        Constants::ParticleCoreShellType, m_sampleModel->indexOfItem(p_parent));
    p_coreshell_item->setItemValue(ParticleItem::P_ABUNDANCE, p_sample->abundance());

    buildPositionInfo(p_coreshell_item, p_sample);

    m_levelToParentItem[depth()] = p_coreshell_item;
    m_itemToSample[p_coreshell_item] = p_sample;
}

void GUIObjectBuilder::visit(const ParticleComposition* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(p_parent);
    SessionItem* p_particle_composition_item = m_sampleModel->insertNewItem(
        Constants::ParticleCompositionType, m_sampleModel->indexOfItem(p_parent));
    p_particle_composition_item->setItemValue(ParticleItem::P_ABUNDANCE, p_sample->abundance());

    buildPositionInfo(p_particle_composition_item, p_sample);

    m_levelToParentItem[depth()] = p_particle_composition_item;
    m_itemToSample[p_particle_composition_item] = p_sample;
}

void GUIObjectBuilder::visit(const MesoCrystal* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(p_parent);
    SessionItem* p_mesocrystal_item = m_sampleModel->insertNewItem(
        Constants::MesoCrystalType, m_sampleModel->indexOfItem(p_parent));
    p_mesocrystal_item->setItemValue(MesoCrystalItem::P_ABUNDANCE, p_sample->abundance());

    buildPositionInfo(p_mesocrystal_item, p_sample);

    m_levelToParentItem[depth()] = p_mesocrystal_item;
    m_itemToSample[p_mesocrystal_item] = p_sample;
}

void GUIObjectBuilder::visit(const Crystal* p_sample)
{
    SessionItem* p_mesocrystal_item = m_levelToParentItem[depth() - 1];
    Q_ASSERT(p_mesocrystal_item);
    if (p_mesocrystal_item->modelType() != Constants::MesoCrystalType) {
        throw GUIHelpers::Error(
                    "GUIObjectBuilder::visit(const Crystal*) "
                    "-> Error. Parent is not a MesoCrystal");
    }
    auto lattice = p_sample->transformedLattice();
    auto vector_a = lattice.getBasisVectorA();
    auto vector_b = lattice.getBasisVectorB();
    auto vector_c = lattice.getBasisVectorC();

    SessionItem* p_vector_a_item = p_mesocrystal_item->getItem(MesoCrystalItem::P_VECTOR_A);
    SessionItem* p_vector_b_item = p_mesocrystal_item->getItem(MesoCrystalItem::P_VECTOR_B);
    SessionItem* p_vector_c_item = p_mesocrystal_item->getItem(MesoCrystalItem::P_VECTOR_C);
    Q_ASSERT(p_vector_a_item);
    Q_ASSERT(p_vector_b_item);
    Q_ASSERT(p_vector_c_item);
    p_vector_a_item->setItemValue(VectorItem::P_X, vector_a.x());
    p_vector_a_item->setItemValue(VectorItem::P_Y, vector_a.y());
    p_vector_a_item->setItemValue(VectorItem::P_Z, vector_a.z());
    p_vector_b_item->setItemValue(VectorItem::P_X, vector_b.x());
    p_vector_b_item->setItemValue(VectorItem::P_Y, vector_b.y());
    p_vector_b_item->setItemValue(VectorItem::P_Z, vector_b.z());
    p_vector_c_item->setItemValue(VectorItem::P_X, vector_c.x());
    p_vector_c_item->setItemValue(VectorItem::P_Y, vector_c.y());
    p_vector_c_item->setItemValue(VectorItem::P_Z, vector_c.z());
}

void GUIObjectBuilder::visit(const FormFactorAnisoPyramid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::AnisoPyramidType);
    p_ff_item->setItemValue(AnisoPyramidItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(AnisoPyramidItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(AnisoPyramidItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(AnisoPyramidItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorBox* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::BoxType);
    p_ff_item->setItemValue(BoxItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(BoxItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(BoxItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorCone* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::ConeType);
    p_ff_item->setItemValue(ConeItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(ConeItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(ConeItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorCone6* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Cone6Type);
    p_ff_item->setItemValue(Cone6Item::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(Cone6Item::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(Cone6Item::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorCuboctahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::CuboctahedronType);
    p_ff_item->setItemValue(CuboctahedronItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(CuboctahedronItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(CuboctahedronItem::P_HEIGHT_RATIO, p_sample->getHeightRatio());
    p_ff_item->setItemValue(CuboctahedronItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorCylinder* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::CylinderType);
    p_ff_item->setItemValue(CylinderItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(CylinderItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorDodecahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::DodecahedronType);
    p_ff_item->setItemValue(DodecahedronItem::P_EDGE, p_sample->getEdge());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorDot*)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    p_particle_item->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::DotType);
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorEllipsoidalCylinder* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
       ParticleItem::P_FORM_FACTOR, Constants::EllipsoidalCylinderType);
    p_ff_item->setItemValue(EllipsoidalCylinderItem::P_RADIUS_X, p_sample->getRadiusX());
    p_ff_item->setItemValue(EllipsoidalCylinderItem::P_RADIUS_Y, p_sample->getRadiusY());
    p_ff_item->setItemValue(EllipsoidalCylinderItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorFullSphere* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::FullSphereType);
    p_ff_item->setItemValue(FullSphereItem::P_RADIUS, p_sample->getRadius());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorFullSpheroid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::FullSpheroidType);
    p_ff_item->setItemValue(FullSpheroidItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(FullSpheroidItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorIcosahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::IcosahedronType);
    p_ff_item->setItemValue(IcosahedronItem::P_EDGE, p_sample->getEdge());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorHemiEllipsoid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::HemiEllipsoidType);
    p_ff_item->setItemValue(HemiEllipsoidItem::P_RADIUS_X, p_sample->getRadiusX());
    p_ff_item->setItemValue(HemiEllipsoidItem::P_RADIUS_Y, p_sample->getRadiusY());
    p_ff_item->setItemValue(HemiEllipsoidItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorPrism3* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Prism3Type);
    p_ff_item->setItemValue(Prism3Item::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(Prism3Item::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorPrism6* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Prism6Type);
    p_ff_item->setItemValue(Prism6Item::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(Prism6Item::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorPyramid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::PyramidType);
    p_ff_item->setItemValue(PyramidItem::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(PyramidItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(PyramidItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorRipple1* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Ripple1Type);
    p_ff_item->setItemValue(Ripple1Item::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(Ripple1Item::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(Ripple1Item::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorRipple2* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Ripple2Type);
    p_ff_item->setItemValue(Ripple2Item::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(Ripple2Item::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(Ripple2Item::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(Ripple2Item::P_ASYMMETRY, p_sample->getAsymmetry());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorTetrahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TetrahedronType);
    p_ff_item->setItemValue(TetrahedronItem::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(TetrahedronItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(TetrahedronItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedCube* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TruncatedCubeType);
    p_ff_item->setItemValue(TruncatedCubeItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(TruncatedCubeItem::P_REMOVED_LENGTH, p_sample->getRemovedLength());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedSphere* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TruncatedSphereType);
    p_ff_item->setItemValue(TruncatedSphereItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(TruncatedSphereItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(TruncatedSphereItem::P_REMOVED_TOP, p_sample->getRemovedTop());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedSpheroid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth()-1];
    SessionItem* p_ff_item = p_particle_item->setGroupProperty(
                ParticleItem::P_FORM_FACTOR, Constants::TruncatedSpheroidType);
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_HFC, p_sample->getHeightFlattening());
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_REMOVED_TOP, p_sample->getRemovedTop());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIObjectBuilder::visit(const InterferenceFunctionRadialParaCrystal* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunctionRadialParaCrystalType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DParaCrystal* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DParaCrystalType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction1DLattice* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction1DLatticeType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DLattice* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DLatticeType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const RotationX* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::XRotationType);
    p_rotationItem->setItemValue(XRotationItem::P_ANGLE,
                                          Units::rad2deg(p_sample->getAngle()) );
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationY* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
        TransformationItem::P_ROT, Constants::YRotationType);
    p_rotationItem->setItemValue(YRotationItem::P_ANGLE, Units::rad2deg(p_sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationZ* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::ZRotationType);
    p_rotationItem->setItemValue(ZRotationItem::P_ANGLE, Units::rad2deg(p_sample->getAngle()) );
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationEuler* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    Q_ASSERT(transformation_item);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::EulerRotationType);
    p_rotationItem->setItemValue(EulerRotationItem::P_ALPHA,  Units::rad2deg(p_sample->getAlpha()) );
    p_rotationItem->setItemValue(EulerRotationItem::P_BETA, Units::rad2deg(p_sample->getBeta()) );
    p_rotationItem->setItemValue(EulerRotationItem::P_GAMMA, Units::rad2deg(p_sample->getGamma()) );
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::buildPositionInfo(SessionItem* p_particle_item, const IParticle* p_sample)
{
    kvector_t position = p_sample->position();
    SessionItem* positionItem = p_particle_item->getItem(ParticleItem::P_POSITION);
    Q_ASSERT(positionItem);
    positionItem->setItemValue(VectorItem::P_X, position.x());
    positionItem->setItemValue(VectorItem::P_Y, position.y());
    positionItem->setItemValue(VectorItem::P_Z, position.z());
}

MaterialProperty GUIObjectBuilder::createMaterialFromDomain(
        const HomogeneousMaterial* material)
{
    QString materialName = m_topSampleName + QString("_") + QString(material->getName().c_str());

    MaterialProperty materialProperty = MaterialSvc::getMaterialProperty(materialName);
    if(materialProperty.isDefined()) return materialProperty;

    MaterialModel* model = MaterialSvc::getMaterialModel();

    if(material->isScalarMaterial()) {
        complex_t rindex = material->refractiveIndex();
        MaterialItem* materialItem  =
            model->addMaterial(materialName, 1-rindex.real(),rindex.imag());
        return MaterialProperty(materialItem->getIdentifier());
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::createMaterialFromDomain()"
                                " -> Not implemented.");
    }
}
