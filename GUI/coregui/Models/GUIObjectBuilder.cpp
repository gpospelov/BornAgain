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
#include "ParticleDistribution.h"
#include "ParticleDistributionItem.h"
#include <QDebug>


GUIObjectBuilder::GUIObjectBuilder()
    : m_sampleModel(0)
{
}

ParameterizedItem *GUIObjectBuilder::populateSampleModel(
        SampleModel *sampleModel, ISample *sample)
{
    Q_ASSERT(sampleModel);
    Q_ASSERT(sample);

    m_levelToParentItem.clear();

    m_topSampleName = sample->getName().c_str();
    m_sampleModel = sampleModel;

    qDebug() << "GUIObjectBuilder::populateModel()" << m_topSampleName;

    //sample->accept(this);
    VisitSampleTree(*sample, *this);
    return m_levelToParentItem[0];
}

ParameterizedItem *GUIObjectBuilder::populateInstrumentModel(
        InstrumentModel *instrumentModel, Instrument *instrument)
{
    Q_UNUSED(instrumentModel);
    Q_UNUSED(instrument);

    ParameterizedItem *instrumentItem =
            instrumentModel->insertNewItem(Constants::InstrumentType);
    instrumentItem->setItemName(instrument->getName().c_str());

    Beam beam = instrument->getBeam();
    ParameterizedItem *beamItem = instrumentModel->insertNewItem(
                Constants::BeamType,
                instrumentModel->indexOfItem(instrumentItem));
    beamItem->setRegisteredProperty(BeamItem::P_INTENSITY,
                                    beam.getIntensity());
    beamItem->setRegisteredProperty(BeamItem::P_WAVELENGTH,
                                    beam.getWavelength());

    beamItem->setRegisteredProperty(BeamItem::P_INCLINATION_ANGLE,
        AngleProperty::Degrees(Units::rad2deg(-1.0*beam.getAlpha())));
    beamItem->setRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE,
        AngleProperty::Degrees(Units::rad2deg(-1.0*beam.getPhi())));

    Detector detector = instrument->getDetector();
    ParameterizedItem *detectorItem = instrumentModel->insertNewItem(
        Constants::DetectorType, instrumentModel->indexOfItem(instrumentItem));
    ParameterizedItem *detectorSubItem =
            detectorItem->getSubItems()[DetectorItem::P_DETECTOR];
    Q_ASSERT(detectorSubItem);


    const IAxis &phi_axis = detector.getAxis(0);
    const IAxis &alpha_axis = detector.getAxis(1);

    ComboProperty binning_property = detectorSubItem->getRegisteredProperty(
        PhiAlphaDetectorItem::P_BINNING).value<ComboProperty>();
    binning_property.setValue(TransformFromDomain::getDetectorBinning(&detector));
    detectorSubItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_BINNING, binning_property.getVariant());

    detectorSubItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_NPHI, (int)phi_axis.getSize());

    detectorSubItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_PHI_MIN,
        AngleProperty::Degrees(Units::rad2deg(phi_axis.getMin())));
    detectorSubItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_PHI_MAX,
        AngleProperty::Degrees(Units::rad2deg(phi_axis.getMax())));

    detectorSubItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_NALPHA, (int)alpha_axis.getSize());
    detectorSubItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_ALPHA_MIN,
        AngleProperty::Degrees(Units::rad2deg(alpha_axis.getMin())));
    detectorSubItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_ALPHA_MAX,
        AngleProperty::Degrees(Units::rad2deg(alpha_axis.getMax())));

    return instrumentItem;
}

void GUIObjectBuilder::visit(const ParticleLayout *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleLayout *)"  << getLevel();
    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    ParameterizedItem *item(0);
    if(parent) {
        item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType,
                                         m_sampleModel->indexOfItem(parent));
    } else {
        item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType);
    }
    item->setItemName(sample->getName().c_str());

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

    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);

    ParameterizedItem *particleItem(0);
    if(parent->modelType() == Constants::ParticleCoreShellType) {
        const ParticleCoreShell *coreshell =
                dynamic_cast<const ParticleCoreShell *>(m_itemToSample[parent]);
        Q_ASSERT(coreshell);
        if(sample == coreshell->getCoreParticle()) {
            particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                m_sampleModel->indexOfItem(parent), -1,
                ParameterizedItem::PortInfo::PORT_0);
            const Geometry::Transform3D *p_transformation =
                    sample->getPTransform3D();
            if (p_transformation) {
                ParameterizedItem *transformation_item =
                        m_sampleModel->insertNewItem(
                            Constants::TransformationType,
                            m_sampleModel->indexOfItem(particleItem));
                addRotationItem(p_transformation, transformation_item);
            }
        }
        else if(sample == coreshell->getShellParticle()) {
            particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                m_sampleModel->indexOfItem(parent), -1,
                ParameterizedItem::PortInfo::PORT_1);
            const Geometry::Transform3D *p_transformation =
                    sample->getPTransform3D();
            if (p_transformation) {
                ParameterizedItem *transformation_item =
                        m_sampleModel->insertNewItem(
                            Constants::TransformationType,
                            m_sampleModel->indexOfItem(particleItem));
                addRotationItem(p_transformation, transformation_item);
            }
        } else {
            throw GUIHelpers::Error("GUIObjectBuilder::visit"
             "(const Particle *sample) -> Error. Logically should not be here");
        }
    }
    else if(parent->modelType() == Constants::ParticleLayoutType
         || parent->modelType() == Constants::ParticleDistributionType){
        particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                                      m_sampleModel->indexOfItem(parent));
        bool has_position_info = m_sample_encountered[
                Constants::TransformationType];
        const Geometry::Transform3D *p_transformation = sample->getPTransform3D();
        if (has_position_info || p_transformation) {
            ParameterizedItem *transformation_item =
                m_sampleModel->insertNewItem(Constants::TransformationType,
                    m_sampleModel->indexOfItem(particleItem));
            if (has_position_info) {
                ParameterizedItem *p_position_item =
                  transformation_item->getSubItems()[TransformationItem::P_POS];
                p_position_item->setRegisteredProperty(VectorItem::P_X,
                     m_propertyToValue[VectorItem::P_X]);
                p_position_item->setRegisteredProperty(VectorItem::P_Y,
                     m_propertyToValue[VectorItem::P_Y]);
                p_position_item->setRegisteredProperty(VectorItem::P_Z,
                     m_propertyToValue[VectorItem::P_Z]);
                m_sample_encountered[Constants::TransformationType] = false;
            }
            if (p_transformation) {
                addRotationItem(p_transformation, transformation_item);
            }
        }
    }
    else {
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
          "(const Particle *sample) -> Logic error.");
    }

    if(!m_propertyToValue.contains(ParticleItem::P_DEPTH))
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
          "(const ParticleCoreShell *sample) -> Error. No depth property.");
    if(!m_propertyToValue.contains(ParticleItem::P_ABUNDANCE))
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
          "(const ParticleCoreShell *sample) -> Error. No abundance property.");

    particleItem->setRegisteredProperty(ParticleItem::P_DEPTH,
        m_propertyToValue[ParticleItem::P_DEPTH]);
    particleItem->setRegisteredProperty(ParticleItem::P_ABUNDANCE,
        m_propertyToValue[ParticleItem::P_ABUNDANCE]);
    particleItem->setItemName(sample->getName().c_str());
    particleItem->setRegisteredProperty(ParticleItem::P_MATERIAL,
        createMaterialFromDomain(sample->getMaterial()).getVariant());
    m_levelToParentItem[getLevel()] = particleItem;
}

void GUIObjectBuilder::visit(const ParticleDistribution *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleDistribution *)"
             << getLevel();

    ParameterizedItem *layoutItem = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(layoutItem);
    ParameterizedItem *item =
            m_sampleModel->insertNewItem(Constants::ParticleDistributionType,
                                        m_sampleModel->indexOfItem(layoutItem));
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[getLevel()] = item;
    m_itemToSample[item] = sample;
}

void GUIObjectBuilder::visit(const ParticleCoreShell *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleCoreShell *)"
             << getLevel();

    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);

    ParameterizedItem *coreshellItem =
            m_sampleModel->insertNewItem(Constants::ParticleCoreShellType,
                                         m_sampleModel->indexOfItem(parent));

    if(!m_propertyToValue.contains(ParticleItem::P_DEPTH))
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
          "(const ParticleCoreShell *sample) -> Error. No depth property.");
    if(!m_propertyToValue.contains(ParticleItem::P_ABUNDANCE))
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
          "(const ParticleCoreShell *sample) -> Error. No abundance property.");

    coreshellItem->setRegisteredProperty(ParticleItem::P_DEPTH,
                       m_propertyToValue[ParticleItem::P_DEPTH]);
    coreshellItem->setRegisteredProperty(ParticleItem::P_ABUNDANCE,
                       m_propertyToValue[ParticleItem::P_ABUNDANCE]);
    coreshellItem->setItemName(sample->getName().c_str());
    kvector_t pos = sample->getRelativeCorePosition();

    ParameterizedItem *vectorItem =
            coreshellItem->getSubItems()[ParticleCoreShellItem::P_CORE_POS];

    vectorItem->setRegisteredProperty(VectorItem::P_X, pos.x());
    vectorItem->setRegisteredProperty(VectorItem::P_Y, pos.y());
    vectorItem->setRegisteredProperty(VectorItem::P_Z, pos.z());

    m_levelToParentItem[getLevel()] = coreshellItem;
    m_itemToSample[coreshellItem] = sample;
}

void GUIObjectBuilder::visit(const ParticleInfo *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleInfo *)" << getLevel();
    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);
    m_propertyToValue[ParticleItem::P_DEPTH] = sample->getDepth();
    m_propertyToValue[ParticleItem::P_ABUNDANCE] = sample->getAbundance();
    kvector_t position = sample->getPosition();
    if (position.x()!=0.0 || position.y()!=0.0){
        m_sample_encountered[Constants::TransformationType] = true;
        m_propertyToValue[VectorItem::P_X] = position.x();
        m_propertyToValue[VectorItem::P_Y] = position.y();
        m_propertyToValue[VectorItem::P_Z] = position.z();
    }
    m_levelToParentItem[getLevel()] = parent;
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
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_RADIUS_A,
                                  sample->getRadiusA());
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_RADIUS_B,
                                  sample->getRadiusB());
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
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_RADIUS_A,
                                  sample->getRadiusA());
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_RADIUS_B,
                                  sample->getRadiusB());
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
    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunctionRadialParaCrystalType,
                m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[getLevel()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DParaCrystal *sample)
{
    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DParaCrystalType,
                m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[getLevel()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DLattice *sample)
{
    ParameterizedItem *parent = m_levelToParentItem[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DLatticeType,
                m_sampleModel->indexOfItem(parent));
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

    return MaterialProperty();
}

void GUIObjectBuilder::addRotationItem(
        const Geometry::Transform3D *p_transformation,
        ParameterizedItem *transformation_item)
{
    Geometry::Transform3D::ERotationType rot_type =
            p_transformation->getRotationType();
    double alpha, beta, gamma;
    p_transformation->calculateEulerAngles(&alpha, &beta, &gamma);
    ParameterizedItem *p_rotation_item = 0;
    switch (rot_type) {
    case Geometry::Transform3D::XAXIS:
        p_rotation_item = transformation_item->setGroupProperty(
                    TransformationItem::P_ROT,
                    Constants::XRotationType);
        if (alpha>0.0) beta = -beta;
        p_rotation_item->setRegisteredProperty(
                    XRotationItem::P_ANGLE, Units::rad2deg(beta));
        break;
    case Geometry::Transform3D::YAXIS:
        p_rotation_item = transformation_item->setGroupProperty(
                    TransformationItem::P_ROT,
                    Constants::YRotationType);
        if (alpha>0.0 && alpha<3.14) beta = -beta;
        p_rotation_item->setRegisteredProperty(
                    YRotationItem::P_ANGLE, Units::rad2deg(beta));
        break;
    case Geometry::Transform3D::ZAXIS:
        p_rotation_item = transformation_item->setGroupProperty(
                    TransformationItem::P_ROT,
                    Constants::ZRotationType);
        p_rotation_item->setRegisteredProperty(
                    ZRotationItem::P_ANGLE, Units::rad2deg(alpha));
        break;
    default:
        p_rotation_item = transformation_item->setGroupProperty(
                    TransformationItem::P_ROT,
                    Constants::EulerRotationType);
        p_rotation_item->setRegisteredProperty(
                    EulerRotationItem::P_ALPHA, Units::rad2deg(alpha));
        p_rotation_item->setRegisteredProperty(
                    EulerRotationItem::P_BETA, Units::rad2deg(beta));
        p_rotation_item->setRegisteredProperty(
                    EulerRotationItem::P_GAMMA, Units::rad2deg(gamma));
        break;
    }
}


