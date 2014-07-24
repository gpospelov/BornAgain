// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/TransformToDomain.cpp
//! @brief     Implements functions to transform items to domain objects.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TransformToDomain.h"
#include "MaterialUtils.h"
#include "GUIHelpers.h"
#include "FormFactorItems.h"
#include "ParaCrystalItems.h"
#include "ParticleItem.h"
#include "LayerItem.h"
#include "BeamItem.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "MultiLayerItem.h"
#include "LatticeTypeItems.h"
#include "FTDistributionItems.h"
#include "ParticleCoreShellItem.h"
#include "ParticleCoreShell.h"
#include "LayerRoughnessItems.h"
#include "VectorItem.h"
#include "MaterialUtils.h"
#include "MaterialProperty.h"
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

    IFormFactor *ff = createFormFactor(*ffItem);
    result->setSimpleFormFactor(ff);

    return result;
}

IFormFactor *TransformToDomain::createFormFactor(const ParameterizedItem &item)
{
    const FormFactorItem *ffItem = dynamic_cast<const FormFactorItem *>(&item);
    Q_ASSERT(ffItem);
    return ffItem->createFormFactor();
}

IInterferenceFunction *TransformToDomain::createInterferenceFunction(
        const ParameterizedItem &item)
{
    if(item.modelType() == Constants::InterferenceFunction1DParaCrystalType) {
        double peak_distance = item.getRegisteredProperty(
                    InterferenceFunction1DParaCrystalItem::P_PEAK_DISTANCE)
                .toDouble();
        double damping_length = item.getRegisteredProperty(
                    InterferenceFunction1DParaCrystalItem::P_DAMPING_LENGTH)
                .toDouble();
        double domain_size = item.getRegisteredProperty(
                    InterferenceFunction1DParaCrystalItem::P_DOMAIN_SIZE)
                .toDouble();
        double kappa = item.getRegisteredProperty(
                    InterferenceFunction1DParaCrystalItem::P_KAPPA)
                .toDouble();

        InterferenceFunction1DParaCrystal *result =
                new InterferenceFunction1DParaCrystal(peak_distance,
                                                      damping_length);
        result->setDomainSize(domain_size);
        result->setKappa(kappa);
        ParameterizedItem *pdfItem = item.getSubItems()[
                InterferenceFunction1DParaCrystalItem::P_PDF];

        Q_ASSERT(pdfItem);
        boost::scoped_ptr<IFTDistribution1D> pdf(
                    dynamic_cast<FTDistribution1DItem *>(pdfItem)
                    ->createFTDistribution());
        Q_ASSERT(pdf.get());

        result->setProbabilityDistribution(*pdf);
        return result;
    }
    else if(item.modelType() == Constants::InterferenceFunction2DParaCrystalType) {

        ParameterizedItem *latticeItem = item.getSubItems()[InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE];
        Q_ASSERT(latticeItem);

        double length_1(0), length_2(0), alpha_lattice(0.0);
        if(latticeItem->modelType() == Constants::BasicLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH1).toDouble();
            length_2 = latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH2).toDouble();
            alpha_lattice = Units::deg2rad(item.getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_ANGLE).toDouble());
        }
        else if(latticeItem->modelType() == Constants::SquareLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(SquareLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            alpha_lattice = M_PI/2.0;
        }
        else if(latticeItem->modelType() == Constants::HexagonalLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(HexagonalLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
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

    return 0;
}

Instrument *TransformToDomain::createInstrument(const ParameterizedItem &item)
{
    qDebug() << "TransformToDomain::createInstrument";
    Instrument *result = new Instrument();
    result->setName(item.itemName().toUtf8().constData());
    return result;
}

Beam *TransformToDomain::createBeam(const ParameterizedItem &item)
{
    qDebug() << "TransformToDomain::createBeam";
    Beam *result = new Beam();
    result->setName(item.itemName().toUtf8().constData());
    result->setIntensity(item.getRegisteredProperty(BeamItem::P_INTENSITY).toDouble());
    double lambda = item.getRegisteredProperty(BeamItem::P_WAVELENGTH).toDouble();
    double alpha_i = item.getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).toDouble();
    double phi_i = item.getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).toDouble();
    result->setCentralK( lambda, Units::deg2rad(alpha_i), Units::deg2rad(phi_i));
    return result;
}

void TransformToDomain::initInstrumentFromDetectorItem(const ParameterizedItem &item, Instrument *instrument)
{
    qDebug() << "TransformToDomain::initInstrumentWithDetectorItem()" << item.modelType();
    item.print();

    ParameterizedItem *subDetector = item.getSubItems()[DetectorItem::P_DETECTOR];
    Q_ASSERT(subDetector);

    qDebug() << "   TransformToDomain::initInstrumentWithDetectorItem()" << subDetector->modelType();
    if (subDetector->modelType() == Constants::ThetaPhiDetectorType) {
        int nphi = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_NPHI).toInt();
        double phi_min = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MIN).toDouble();
        double phi_max = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MAX).toDouble();
        int nalpha = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_NALPHA).toInt();
        double alpha_min = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MIN).toDouble();
        double alpha_max = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MAX).toDouble();
        bool isgisaxs_style(true);

        ComboProperty binning = subDetector->getRegisteredProperty(DetectorItem::P_BINNING).value<ComboProperty>();
        if(binning.getValue() == QStringLiteral("Flat")) isgisaxs_style = false;

        ComboProperty units = subDetector->getRegisteredProperty(DetectorItem::P_AXES_UNITS).value<ComboProperty>();
        if(units.getValue() == QStringLiteral("Degrees")) {
            phi_min = Units::deg2rad(phi_min);
            phi_max = Units::deg2rad(phi_max);
            alpha_min = Units::deg2rad(alpha_min);
            alpha_max = Units::deg2rad(alpha_max);
        }

        instrument->setDetectorParameters(nphi, phi_min, phi_max, nalpha, alpha_min, alpha_max, isgisaxs_style);
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
