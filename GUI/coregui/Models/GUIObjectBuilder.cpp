#include "GUIObjectBuilder.h"
#include "SessionModel.h"
#include "Units.h"
#include "LayerItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "MultiLayerItem.h"
#include "MaterialUtils.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "ParaCrystalItems.h"
#include "TransformFromDomain.h"
#include "ComboProperty.h"
#include <QDebug>


GUIObjectBuilder::GUIObjectBuilder()
    : m_sampleModel(0)
//    , m_parentItem(0)
{

}


ParameterizedItem *GUIObjectBuilder::populateSampleModel(SessionModel *sampleModel, ISample *sample)
{
    Q_ASSERT(sampleModel);
    Q_ASSERT(sample);

    m_levelToParent.clear();

    m_topSampleName = sample->getName().c_str();
    m_sampleModel = sampleModel;

    qDebug() << "GUIObjectBuilder::populateModel()" << m_topSampleName;

    //sample->accept(this);
    VisitSampleTree(*sample, *this);
    return m_levelToParent[0];
}

ParameterizedItem *GUIObjectBuilder::populateInstrumentModel(SessionModel *instrumentModel, Instrument *instrument)
{
    Q_UNUSED(instrumentModel);
    Q_UNUSED(instrument);

    ParameterizedItem *instrumentItem = instrumentModel->insertNewItem("Instrument");
    instrumentItem->setItemName(instrument->getName().c_str());

    Beam beam = instrument->getBeam();
    ParameterizedItem *beamItem = instrumentModel->insertNewItem("Beam", instrumentModel->indexOfItem(instrumentItem));
    beamItem->setRegisteredProperty(BeamItem::P_INTENSITY, beam.getIntensity());
    beamItem->setRegisteredProperty(BeamItem::P_WAVELENGTH, beam.getWavelength());
    beamItem->setRegisteredProperty(BeamItem::P_INCLINATION_ANGLE, Units::rad2deg(-1.0*beam.getAlpha()));
    beamItem->setRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE, Units::rad2deg(beam.getPhi()));

    Detector detector = instrument->getDetector();
    ParameterizedItem *detectorItem = instrumentModel->insertNewItem("Detector", instrumentModel->indexOfItem(instrumentItem));
    ParameterizedItem *detectorSubItem = detectorItem->getSubItems()[DetectorItem::P_DETECTOR_TYPE];
    Q_ASSERT(detectorSubItem);

    const IAxis &phi_axis = detector.getAxis(0);
    const IAxis &alpha_axis = detector.getAxis(1);

    detectorSubItem->setRegisteredProperty(ThetaPhiDetectorItem::P_NPHI, (int)phi_axis.getSize());
    detectorSubItem->setRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MIN, Units::rad2deg(phi_axis.getMin()));
    detectorSubItem->setRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MAX,  Units::rad2deg(phi_axis.getMax()));
    detectorSubItem->setRegisteredProperty(ThetaPhiDetectorItem::P_NALPHA, (int)alpha_axis.getSize());
    detectorSubItem->setRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MIN, Units::rad2deg(alpha_axis.getMin()));
    detectorSubItem->setRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MAX,  Units::rad2deg(alpha_axis.getMax()));

    if(instrument->getIsgisaxsStyle()) {
        ComboProperty binning_property = detectorSubItem->getRegisteredProperty(DetectorItem::P_BINNING).value<ComboProperty>();
        binning_property.setValue("Flat in sin");
        detectorSubItem->setRegisteredProperty(DetectorItem::P_BINNING, binning_property.getVariant());

    }
    return instrumentItem;
}


void GUIObjectBuilder::visit(const ParticleLayout *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleLayout *)"  << getLevel();
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem("ParticleLayout", m_sampleModel->indexOfItem(parent));
    item->setItemName(sample->getName().c_str());
    m_levelToParent[getLevel()] = item;
}


void GUIObjectBuilder::visit(const Layer *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Layer *)"  << getLevel();
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem("Layer", m_sampleModel->indexOfItem(parent));
    item->setItemName(sample->getName().c_str());
    item->setRegisteredProperty(LayerItem::P_THICKNESS, sample->getThickness());
    item->setMaterialProperty(createMaterialFromDomain(sample->getMaterial()));
    m_levelToParent[getLevel()] = item;
}


void GUIObjectBuilder::visit(const LayerInterface *)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerInterface *)"  << getLevel();

}


void GUIObjectBuilder::visit(const MultiLayer *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const MultiLayer *)" << getLevel();

    ParameterizedItem *item = m_sampleModel->insertNewItem("MultiLayer");
    item->setItemName(sample->getName().c_str());
    item->setRegisteredProperty(MultiLayerItem::P_CROSS_CORR_LENGTH, sample->getCrossCorrLength());
    m_levelToParent[getLevel()] = item;
}


void GUIObjectBuilder::visit(const Particle *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Particle *)" << getLevel();

    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    particleItem->setItemName(sample->getName().c_str());
    particleItem->setMaterialProperty(createMaterialFromDomain(sample->getMaterial()));
    m_levelToParent[getLevel()] = particleItem;

}


void GUIObjectBuilder::visit(const ParticleInfo *sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleInfo *)" << getLevel();
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem("Particle", m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    item->setRegisteredProperty(ParticleItem::P_DEPTH, sample->getDepth());
    item->setRegisteredProperty(ParticleItem::P_ABUNDANCE, sample->getAbundance());
    m_levelToParent[getLevel()] = item;
}


void GUIObjectBuilder::visit(const FormFactorAnisoPyramid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "AnisoPyramid");
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_WIDTH, sample->getWidth());
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(AnisoPyramidItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorBox *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Box");
    ffItem->setRegisteredProperty(BoxItem::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(BoxItem::P_WIDTH, sample->getWidth());
    ffItem->setRegisteredProperty(BoxItem::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCone *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cone");
    ffItem->setRegisteredProperty(ConeItem::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(ConeItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(ConeItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCone6 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cone6");
    ffItem->setRegisteredProperty(Cone6Item::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(Cone6Item::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(Cone6Item::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCuboctahedron *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cuboctahedron");
    ffItem->setRegisteredProperty(CuboctahedronItem::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(CuboctahedronItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(CuboctahedronItem::P_HEIGHT_RATIO, sample->getHeightRatio());
    ffItem->setRegisteredProperty(CuboctahedronItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorCylinder *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cylinder");
    ffItem->setRegisteredProperty(CylinderItem::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(CylinderItem::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorEllipsoidalCylinder *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "EllipsoidalCylinder");
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_RADIUS_A, sample->getRadiusA());
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_RADIUS_B, sample->getRadiusB());
    ffItem->setRegisteredProperty(EllipsoidalCylinderItem::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorFullSphere *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "FullSphere");
    ffItem->setRegisteredProperty(FullSphereItem::P_RADIUS, sample->getRadius());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorFullSpheroid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "FullSpheroid");
    ffItem->setRegisteredProperty(FullSpheroidItem::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(FullSpheroidItem::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorHemiEllipsoid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "HemiEllipsoid");
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_RADIUS_A, sample->getRadiusA());
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_RADIUS_B, sample->getRadiusB());
    ffItem->setRegisteredProperty(HemiEllipsoidItem::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorPrism3 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Prism3");
    ffItem->setRegisteredProperty(Prism3Item::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(Prism3Item::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorPrism6 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Prism6");
    ffItem->setRegisteredProperty(Prism6Item::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(Prism6Item::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorPyramid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Pyramid");
    ffItem->setRegisteredProperty(PyramidItem::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(PyramidItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(PyramidItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorRipple1 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Ripple1");
    ffItem->setRegisteredProperty(Ripple1Item::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(Ripple1Item::P_WIDTH, sample->getWidth());
    ffItem->setRegisteredProperty(Ripple1Item::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorRipple2 *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Ripple2");
    ffItem->setRegisteredProperty(Ripple2Item::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(Ripple2Item::P_WIDTH, sample->getWidth());
    ffItem->setRegisteredProperty(Ripple2Item::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(Ripple2Item::P_ASYMMETRY, sample->getAsymmetry());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorTetrahedron *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Tetrahedron");
    ffItem->setRegisteredProperty(TetrahedronItem::P_LENGTH, sample->getLength());
    ffItem->setRegisteredProperty(TetrahedronItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(TetrahedronItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorTruncatedSphere *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "TruncatedSphere");
    ffItem->setRegisteredProperty(TruncatedSphereItem::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(TruncatedSphereItem::P_HEIGHT, sample->getHeight());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const FormFactorTruncatedSpheroid *sample)
{
    ParameterizedItem *particleItem = m_levelToParent[getLevel()-1];
    ParameterizedItem *ffItem = particleItem->setGroupProperty(ParticleItem::P_FORM_FACTOR, "TruncatedSpheroid");
    ffItem->setRegisteredProperty(TruncatedSpheroidItem::P_RADIUS, sample->getRadius());
    ffItem->setRegisteredProperty(TruncatedSpheroidItem::P_HEIGHT, sample->getHeight());
    ffItem->setRegisteredProperty(TruncatedSpheroidItem::P_HFC, sample->getHeightFlattening());
    m_levelToParent[getLevel()] = particleItem;
}


void GUIObjectBuilder::visit(const InterferenceFunction1DParaCrystal *sample)
{
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem("InterferenceFunction1DParaCrystal", m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);
    item->setRegisteredProperty(InterferenceFunction1DParaCrystalItem::P_PEAK_DISTANCE, sample->getPeakDistance());
    item->setRegisteredProperty(InterferenceFunction1DParaCrystalItem::P_CORR_LENGTH, sample->getDampingLength());
    m_levelToParent[getLevel()] = item;
}


void GUIObjectBuilder::visit(const InterferenceFunction2DParaCrystal *sample)
{
    ParameterizedItem *parent = m_levelToParent[getLevel()-1];
    Q_ASSERT(parent);
    ParameterizedItem *item = m_sampleModel->insertNewItem("InterferenceFunction2DParaCrystal", m_sampleModel->indexOfItem(parent));
    Q_ASSERT(item);    
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParent[getLevel()] = item;
}


void GUIObjectBuilder::visit(const InterferenceFunctionNone *)
{
    qDebug() << "GUIObjectBuilder::visit(const InterferenceFunctionNone *)" << getLevel();

}


void GUIObjectBuilder::visit(const LayerRoughness *)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerRoughness *)" << getLevel();

}


MaterialProperty GUIObjectBuilder::createMaterialFromDomain(const IMaterial *material)
{
    QString materialName = m_topSampleName + QString("_") + QString(material->getName().c_str());

    MaterialProperty materialProperty = MaterialEditor::getMaterialProperty(materialName);
    if(materialProperty.isDefined()) return materialProperty;

    MaterialModel *model = MaterialEditor::getMaterialModel();

    if(material->isScalarMaterial()) {
      MaterialItem *materialItem  = model->addMaterial(materialName, MaterialItem::HomogeneousMaterial);
      complex_t rindex = material->getRefractiveIndex();
      materialItem->setRefractiveIndex(1-rindex.real(),rindex.imag());
      return MaterialUtils::getMaterialProperty(materialItem);
    }

    return MaterialProperty();
}


