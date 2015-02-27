// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformToDomain.cpp
//! @brief     Implements class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TransformToDomain.h"
#include "MaterialUtils.h"
#include "GUIHelpers.h"
#include "FormFactorItems.h"
#include "InterferenceFunctionItems.h"
#include "ParticleItem.h"
#include "LayerItem.h"
#include "BeamItem.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "AxesItems.h"
#include "MultiLayerItem.h"
#include "LatticeTypeItems.h"
#include "FTDistributionItems.h"
#include "ParticleCoreShellItem.h"
#include "ParticleCoreShell.h"
#include "LayerRoughnessItems.h"
#include "VectorItem.h"
#include "MaterialUtils.h"
#include "MaterialProperty.h"
#include "AngleProperty.h"
#include "FixedBinAxis.h"
#include "ConstKBinAxis.h"
#include "ParticleLayoutItem.h"
#include "DistributionItem.h"
#include "BeamDistributionItem.h"
#include <QDebug>

#include <boost/scoped_ptr.hpp>


IMaterial *TransformToDomain::createDomainMaterial(const ParameterizedItem &item)
{
    MaterialProperty material_property;
    if(item.modelType() == Constants::ParticleType) {
        material_property = item.getRegisteredProperty(ParticleItem::P_MATERIAL).value<MaterialProperty>();
    }
    else if(item.modelType() == Constants::LayerType) {
        material_property = item.getRegisteredProperty(LayerItem::P_MATERIAL).value<MaterialProperty>();
    }
    if(!material_property.isDefined())
        throw GUIHelpers::Error("TransformToDomain::createDomainMaterial() -> Error. Unknown item to create material");

    return MaterialUtils::createDomainMaterial(material_property);
}

MultiLayer *TransformToDomain::createMultiLayer(const ParameterizedItem &item)
{
    MultiLayer *result = new MultiLayer();
    double cross_corr_length =
            item.getRegisteredProperty(
                MultiLayerItem::P_CROSS_CORR_LENGTH).toDouble();
    if(cross_corr_length>0) result->setCrossCorrLength(cross_corr_length);
    result->setName(item.itemName().toUtf8().constData());
    return result;
}

Layer *TransformToDomain::createLayer(const ParameterizedItem &item)
{
    Layer *result = new Layer();
    double thickness =
            item.getRegisteredProperty(LayerItem::P_THICKNESS).toDouble();
    result->setThickness(thickness);

    boost::scoped_ptr<IMaterial> material(createDomainMaterial(item));
    result->setMaterial(*material.get());
    result->setName(item.itemName().toUtf8().constData());

    return result;
}

ParticleLayout *TransformToDomain::createParticleLayout(
        const ParameterizedItem &item)
{
    (void)item;
    ParticleLayout *result = new ParticleLayout();
    QVariant var = item.getRegisteredProperty(ParticleLayoutItem::P_APPROX);
    ComboProperty prop = var.value<ComboProperty>();
    QString approximation = prop.getValue();
    if (approximation == QString("Decoupling Approximation")) {
        result->setApproximation(ILayout::DA);
    }
    else if (approximation == QString("Size Space Coupling Approximation")) {
        result->setApproximation(ILayout::SSCA);
    }
    return result;
}

Particle *TransformToDomain::createParticle(const ParameterizedItem &item,
                                            double &depth, double &abundance)
{
    boost::scoped_ptr<IMaterial> material(createDomainMaterial(item));
    Particle *result = new Particle(*material);
    depth = item.getRegisteredProperty(ParticleItem::P_DEPTH).toDouble();
    abundance = item.getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    result->setName(item.itemName().toStdString());

    ParameterizedItem *ffItem = item.getSubItems()[ParticleItem::P_FORM_FACTOR];
    Q_ASSERT(ffItem);

    boost::scoped_ptr<IFormFactor> P_ff(createFormFactor(*ffItem));
    result->setFormFactor(*P_ff);

    return result;
}

IFormFactor *TransformToDomain::createFormFactor(const ParameterizedItem &item)
{
    const FormFactorItem *ffItem = dynamic_cast<const FormFactorItem *>(&item);
    Q_ASSERT(ffItem);
    return ffItem->createFormFactor();
}

IDistribution1D *TransformToDomain::createDistribution(
        const ParameterizedItem &item)
{
    const DistributionItem *distr_item =
            dynamic_cast<const DistributionItem *>(&item);
    Q_ASSERT(distr_item);
    return distr_item->createDistribution();
}

IInterferenceFunction *TransformToDomain::createInterferenceFunction(
        const ParameterizedItem &item)
{
    if(item.modelType() == Constants::InterferenceFunctionRadialParaCrystalType) {
        double peak_distance = item.getRegisteredProperty(
                    InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE)
                .toDouble();
        double damping_length = item.getRegisteredProperty(
                    InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH)
                .toDouble();
        double domain_size = item.getRegisteredProperty(
                    InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE)
                .toDouble();
        double kappa = item.getRegisteredProperty(
                    InterferenceFunctionRadialParaCrystalItem::P_KAPPA)
                .toDouble();

        InterferenceFunctionRadialParaCrystal *result =
                new InterferenceFunctionRadialParaCrystal(peak_distance,
                                                      damping_length);
        result->setDomainSize(domain_size);
        result->setKappa(kappa);
        ParameterizedItem *pdfItem = item.getSubItems()[
                InterferenceFunctionRadialParaCrystalItem::P_PDF];

        Q_ASSERT(pdfItem);
        boost::scoped_ptr<IFTDistribution1D> pdf(
                    dynamic_cast<FTDistribution1DItem *>(pdfItem)
                    ->createFTDistribution());
        Q_ASSERT(pdf.get());

        result->setProbabilityDistribution(*pdf);
        return result;
    }
    else if(item.modelType() == Constants::InterferenceFunction2DParaCrystalType) {

        ParameterizedItem *latticeItem = item.getSubItems()
                [InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE];
        Q_ASSERT(latticeItem);

        double length_1(0), length_2(0), alpha_lattice(0.0);
        if(latticeItem->modelType() == Constants::BasicLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                        BasicLatticeTypeItem::P_LATTICE_LENGTH1).toDouble();
            length_2 = latticeItem->getRegisteredProperty(
                        BasicLatticeTypeItem::P_LATTICE_LENGTH2).toDouble();
            alpha_lattice = Units::deg2rad(latticeItem->getRegisteredProperty(
                        BasicLatticeTypeItem::P_LATTICE_ANGLE).toDouble());
        }
        else if(latticeItem->modelType() == Constants::SquareLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                        SquareLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            alpha_lattice = M_PI/2.0;
        }
        else if(latticeItem->modelType() == Constants::HexagonalLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                        HexagonalLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            alpha_lattice = 2*M_PI/3.0;
        }
        else {
            throw GUIHelpers::Error("TransformToDomain::createInterferenceFunction() -> Error");
        }

        InterferenceFunction2DParaCrystal *result = new InterferenceFunction2DParaCrystal(
                    length_1,
                    length_2,
                    alpha_lattice,
                    Units::deg2rad(item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE).toDouble()),
                    item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH).toDouble());
        result->setDomainSizes(
                    item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1).toDouble(),
                    item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2).toDouble()
                    );

        result->setIntegrationOverXi(item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION).toBool());

        ParameterizedItem *pdf1Item = item.getSubItems()[InterferenceFunction2DParaCrystalItem::P_PDF1];
        Q_ASSERT(pdf1Item);
        boost::scoped_ptr<IFTDistribution2D> pdf1(dynamic_cast<FTDistribution2DItem *>(pdf1Item)->createFTDistribution());
        Q_ASSERT(pdf1.get());

        ParameterizedItem *pdf2Item = item.getSubItems()[InterferenceFunction2DParaCrystalItem::P_PDF2];
        Q_ASSERT(pdf2Item);
        boost::scoped_ptr<IFTDistribution2D> pdf2(dynamic_cast<FTDistribution2DItem *>(pdf2Item)->createFTDistribution());
        Q_ASSERT(pdf2.get());

        result->setProbabilityDistributions(*pdf1, *pdf2);
        return result;
    }
    else if(item.modelType() == Constants::InterferenceFunction2DLatticeType) {

        ParameterizedItem *latticeItem = item.getSubItems()
                [InterferenceFunction2DLatticeItem::P_LATTICE_TYPE];
        Q_ASSERT(latticeItem);

        double length_1, length_2, angle;
        if(latticeItem->modelType() == Constants::BasicLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                        BasicLatticeTypeItem::P_LATTICE_LENGTH1).toDouble();
            length_2 = latticeItem->getRegisteredProperty(
                        BasicLatticeTypeItem::P_LATTICE_LENGTH2).toDouble();
            angle = Units::deg2rad(latticeItem->getRegisteredProperty(
                        BasicLatticeTypeItem::P_LATTICE_ANGLE).toDouble());
        }
        else if(latticeItem->modelType() == Constants::SquareLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                        SquareLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            angle = M_PI/2.0;
        }
        else if(latticeItem->modelType() == Constants::HexagonalLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                        HexagonalLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            angle = 2*M_PI/3.0;
        }
        else {
            throw GUIHelpers::Error("TransformToDomain::createInterferenceFunction() -> Error");
        }
        double xi = Units::deg2rad(item.getRegisteredProperty(
            InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE).toDouble());

        InterferenceFunction2DLattice *result =
                new InterferenceFunction2DLattice(length_1, length_2, angle, xi);

        ParameterizedItem *pdfItem = item.getSubItems()
                [InterferenceFunction2DLatticeItem::P_PDF];
        Q_ASSERT(pdfItem);
        boost::scoped_ptr<IFTDistribution2D> pdf(
             dynamic_cast<FTDistribution2DItem *>(pdfItem)
                    ->createFTDistribution());
        Q_ASSERT(pdf.get());

        result->setProbabilityDistribution(*pdf);
        return result;
    }

    return 0;
}

Instrument *TransformToDomain::createInstrument(const ParameterizedItem &item)
{
//    qDebug() << "TransformToDomain::createInstrument";
    Instrument *result = new Instrument();
    result->setName(item.itemName().toUtf8().constData());
    return result;
}

Beam *TransformToDomain::createBeam(const ParameterizedItem &item)
{
//    qDebug() << "TransformToDomain::createBeam";
    Beam *result = new Beam();
    result->setName(item.itemName().toUtf8().constData());

    const BeamItem *beamItem = dynamic_cast<const BeamItem *>(&item);

    result->setIntensity(beamItem->getIntensity());
    double lambda = beamItem->getWavelength();
    double inclination_angle = Units::deg2rad(beamItem->getInclinationAngle());
    double azimuthal_angle = Units::deg2rad(beamItem->getAzimuthalAngle());
    result->setCentralK( lambda, inclination_angle, azimuthal_angle);

//    AngleProperty inclination_angle = item.getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).value<AngleProperty>();
//    AngleProperty azimuthal_angle = item.getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).value<AngleProperty>();
//    result->setCentralK( lambda, inclination_angle.getValueInRadians(), azimuthal_angle.getValueInRadians());
    return result;
}

void TransformToDomain::initInstrumentFromDetectorItem(const ParameterizedItem &item, Instrument *instrument)
{
//    qDebug() << "TransformToDomain::initInstrumentWithDetectorItem()" << item.modelType();
//    item.print();

    ParameterizedItem *subDetector = item.getSubItems()[DetectorItem::P_DETECTOR];
    Q_ASSERT(subDetector);

//    qDebug() << "   TransformToDomain::initInstrumentWithDetectorItem()" << subDetector->modelType();
    if (subDetector->modelType() == Constants::PhiAlphaDetectorType) {

        BasicAxisItem *phiAxis = dynamic_cast<BasicAxisItem *>(subDetector->getSubItems()[PhiAlphaDetectorItem::P_PHI_AXIS]);
        Q_ASSERT(phiAxis);
        int nphi = phiAxis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
        double phi_min = Units::deg2rad(phiAxis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
        double phi_max = Units::deg2rad(phiAxis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

        BasicAxisItem *alphaAxis = dynamic_cast<BasicAxisItem *>(subDetector->getSubItems()[PhiAlphaDetectorItem::P_ALPHA_AXIS]);
        Q_ASSERT(alphaAxis);
        int nalpha = alphaAxis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
        double alpha_min = Units::deg2rad(alphaAxis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
        double alpha_max = Units::deg2rad(alphaAxis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

        ComboProperty binning = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_BINNING).value<ComboProperty>();

        if(binning.getValue() == Constants::AXIS_CONSTK_BINNING) {
            instrument->setDetectorAxes(ConstKBinAxis("phi_x",nphi, phi_min, phi_max), ConstKBinAxis("alpha_x", nalpha, alpha_min, alpha_max));
        }else if(binning.getValue() == Constants::AXIS_FIXED_BINNING) {
            instrument->setDetectorAxes(FixedBinAxis("phi_x",nphi, phi_min, phi_max), FixedBinAxis("alpha_x", nalpha, alpha_min, alpha_max));
        } else {
            throw GUIHelpers::Error("TransformToDomain::initInstrumentFromDetectorItem() -> Unknown axes");
        }

    }
    else {
        throw GUIHelpers::Error("TransformToDomain::initInstrumentWithDetectorItem() -> Error. Unknown model type "+subDetector->modelType());
    }

}


ParticleCoreShell *TransformToDomain::createParticleCoreShell(const ParameterizedItem &item, const Particle &core, const Particle &shell, double &depth, double &abundance)
{
    depth = item.getRegisteredProperty(ParticleItem::P_DEPTH).toDouble();
    abundance = item.getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    ParameterizedItem *vectorItem = item.getSubItems()[ParticleCoreShellItem::P_CORE_POS];
    Q_ASSERT(vectorItem);

    kvector_t pos;
    pos.setX(vectorItem->getRegisteredProperty(VectorItem::P_X).toDouble());
    pos.setY(vectorItem->getRegisteredProperty(VectorItem::P_Y).toDouble());
    pos.setZ(vectorItem->getRegisteredProperty(VectorItem::P_Z).toDouble());
    ParticleCoreShell *result = new ParticleCoreShell(shell, core, pos);
    result->setName(item.itemName().toStdString());
    return result;
}


LayerRoughness *TransformToDomain::createLayerRoughness(const ParameterizedItem &roughnessItem)
{
    if(roughnessItem.modelType() == Constants::LayerZeroRoughnessType) {
        return 0;
    }
    else if(roughnessItem.modelType() == Constants::LayerBasicRoughnessType) {
        LayerRoughness *result = new LayerRoughness(
                    roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_SIGMA).toDouble(),
                    roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_HURST).toDouble(),
                    roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble()
                    );
        return result;
    }
    else {
        throw GUIHelpers::Error("TransformToDomain::createLayerROughness() -> Error.");
    }

}

//! adds DistributionParameters to the Simulation
void TransformToDomain::addDistributionParametersToSimulation(const ParameterizedItem &beam_item, Simulation *simulation)
{
    if(beam_item.modelType() == Constants::BeamType) {

        if(BeamDistributionItem *beamWavelength = dynamic_cast<BeamDistributionItem *>(beam_item.getSubItems()[BeamItem::P_WAVELENGTH])) {
            ParameterDistribution *distr = beamWavelength->getParameterDistributionForName("*/Beam/wavelength");
            if(distr) simulation->addParameterDistribution(*distr);
            delete distr;
        }

        if(BeamDistributionItem *inclinationAngle = dynamic_cast<BeamDistributionItem *>(beam_item.getSubItems()[BeamItem::P_INCLINATION_ANGLE])) {
            ParameterDistribution *distr = inclinationAngle->getParameterDistributionForName("*/Beam/alpha", BeamDistributionItem::MAKE_DISTRIBUTION_NEGATIVE);
            if(distr) simulation->addParameterDistribution(*distr);
            delete distr;
        }

        if(BeamDistributionItem *azimuthalAngle = dynamic_cast<BeamDistributionItem *>(beam_item.getSubItems()[BeamItem::P_AZIMUTHAL_ANGLE])) {
            ParameterDistribution *distr = azimuthalAngle->getParameterDistributionForName("*/Beam/phi");
            if(distr) simulation->addParameterDistribution(*distr);
            delete distr;
        }


    }

}
