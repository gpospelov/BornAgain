// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformFromDomain.cpp
//! @brief     Implements class TransformFromDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TransformFromDomain.h"
#include "ParameterizedItem.h"
#include "InterferenceFunctions.h"
#include "InterferenceFunctionItems.h"
#include "FTDistributions.h"
#include "FTDistributionItems.h"
#include "LatticeTypeItems.h"
#include "Numeric.h"
#include "Units.h"
#include "LayerItem.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "GUIHelpers.h"
#include "FormFactors.h"
#include "FormFactorItems.h"
#include "LayerRoughness.h"
#include "LayerRoughnessItems.h"
#include "ConstKBinAxis.h"
#include "FixedBinAxis.h"
#include "CustomBinAxis.h"
#include "Detector.h"
#include "ParticleDistributionItem.h"
#include "ParticleDistribution.h"
#include "Distributions.h"
#include "DistributionItem.h"
#include "DetectorItems.h"
#include "BeamItem.h"
#include "ComboProperty.h"
#include "AxesItems.h"
#include <QString>
#include <QDebug>
#include <vector>
#include <boost/scoped_ptr.hpp>


void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                              const InterferenceFunctionRadialParaCrystal *sample)
{
    item->setRegisteredProperty(
                InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE,
                sample->getPeakDistance() );
    item->setRegisteredProperty(
                InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH,
                sample->getDampingLength() );
    item->setRegisteredProperty(
                InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE,
                sample->getDomainSize() );
    item->setRegisteredProperty(
                InterferenceFunctionRadialParaCrystalItem::P_KAPPA,
                sample->getKappa() );

    const IFTDistribution1D *ipdf = sample->getPropabilityDistribution();

    QString group_name = InterferenceFunctionRadialParaCrystalItem::P_PDF;

    qDebug() << "    group_name" << group_name;
    if(const FTDistribution1DCauchy *pdf =
            dynamic_cast<const FTDistribution1DCauchy *>(ipdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::FTDistribution1DCauchyType);
        pdfItem->setRegisteredProperty(
                    FTDistribution1DCauchyItem::P_CORR_LENGTH,
                    pdf->getOmega());
    }
    else if(const FTDistribution1DGauss *pdf =
            dynamic_cast<const FTDistribution1DGauss *>(ipdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::FTDistribution1DGaussType);
        pdfItem->setRegisteredProperty(
                    FTDistribution1DGaussItem::P_CORR_LENGTH,
                    pdf->getOmega());
    }
    else if(const FTDistribution1DGate *pdf =
            dynamic_cast<const FTDistribution1DGate *>(ipdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::FTDistribution1DGateType);
        pdfItem->setRegisteredProperty(
                    FTDistribution1DGateItem::P_CORR_LENGTH,
                    pdf->getOmega());
    }
    else if(const FTDistribution1DTriangle *pdf =
            dynamic_cast<const FTDistribution1DTriangle *>(ipdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::FTDistribution1DTriangleType);
        pdfItem->setRegisteredProperty(
                    FTDistribution1DTriangleItem::P_CORR_LENGTH,
                    pdf->getOmega());
    }
    else if(const FTDistribution1DCosine *pdf =
            dynamic_cast<const FTDistribution1DCosine *>(ipdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::FTDistribution1DCosineType);
        pdfItem->setRegisteredProperty(
                    FTDistribution1DCosineItem::P_CORR_LENGTH,
                    pdf->getOmega());
    }
    else if(const FTDistribution1DVoigt *pdf =
            dynamic_cast<const FTDistribution1DVoigt *>(ipdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::FTDistribution1DVoigtType);
        pdfItem->setRegisteredProperty(
                    FTDistribution1DVoigtItem::P_CORR_LENGTH,
                    pdf->getOmega());
        pdfItem->setRegisteredProperty(
                    FTDistribution1DVoigtItem::P_ETA,
                    pdf->getEta());
    }
    else {
        throw GUIHelpers::Error("TransformFromDomain::"
            "setItemFromSample(ParameterizedItem *item, const "
            "InterferenceFunction2DParaCrystal *sample) -> Error");
    }
}

void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                              const InterferenceFunction2DParaCrystal *sample)
{
    ParameterizedItem *latticeTypeItem(0);
    std::vector<double> lengths = sample->getLatticeLengths();
    double angle = sample->getAlphaLattice();
    if( TransformFromDomain::isSquareLattice(lengths[0], lengths[1], angle)) {
        latticeTypeItem = item->setGroupProperty(
            InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE,
                    Constants::SquareLatticeType);
        latticeTypeItem->setRegisteredProperty(
            SquareLatticeTypeItem::P_LATTICE_LENGTH,
            sample->getLatticeLengths()[0]);
    }
    else if( TransformFromDomain::isHexagonalLattice(lengths[0], lengths[1],
                                                     angle)) {
        latticeTypeItem = item->setGroupProperty(
            InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE,
                    Constants::HexagonalLatticeType);
        latticeTypeItem->setRegisteredProperty(
            HexagonalLatticeTypeItem::P_LATTICE_LENGTH,
            sample->getLatticeLengths()[0]);
    }
    else {
        latticeTypeItem = item->setGroupProperty(
            InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE,
                    Constants::BasicLatticeType);
        latticeTypeItem->setRegisteredProperty(
            BasicLatticeTypeItem::P_LATTICE_LENGTH1,
            sample->getLatticeLengths()[0]);
        latticeTypeItem->setRegisteredProperty(
            BasicLatticeTypeItem::P_LATTICE_LENGTH2,
            sample->getLatticeLengths()[1]);
        latticeTypeItem->setRegisteredProperty(
            BasicLatticeTypeItem::P_LATTICE_ANGLE,
            Units::rad2deg(sample->getAlphaLattice()));
    }

    item->setRegisteredProperty(
                InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE,
                Units::rad2deg(sample->getLatticeOrientation()));
    item->setRegisteredProperty(
                InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH,
                sample->getDampingLength());
    item->setRegisteredProperty(
                InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1,
                sample->getDomainSizes()[0]);
    item->setRegisteredProperty(
                InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2,
                sample->getDomainSizes()[1]);
    item->setRegisteredProperty(
                InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION,
                sample->getIntegrationOverXi());

    std::vector<const IFTDistribution2D *> pdfs =
            sample->getProbabilityDistributions();

    QStringList group_names;
    group_names << InterferenceFunction2DParaCrystalItem::P_PDF1
                << InterferenceFunction2DParaCrystalItem::P_PDF2;

    for(size_t i=0; i<pdfs.size(); ++i) {
        qDebug() << "    group_name" << group_names[i];
        if(const FTDistribution2DCauchy *pdf =
                dynamic_cast<const FTDistribution2DCauchy *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i],
                                      Constants::FTDistribution2DCauchyType);
            pdfItem->setRegisteredProperty(
                        FTDistribution2DCauchyItem::P_CORR_LENGTH_X,
                        pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DCauchyItem::P_CORR_LENGTH_Y,
                        pdf->getCoherenceLengthY());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DCauchyItem::P_GAMMA,
                        Units::rad2deg(pdf->getGamma()) );
        }
        else if(const FTDistribution2DGauss *pdf =
                dynamic_cast<const FTDistribution2DGauss *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i],
                                      Constants::FTDistribution2DGaussType);
            pdfItem->setRegisteredProperty(
                        FTDistribution2DGaussItem::P_CORR_LENGTH_X,
                        pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DGaussItem::P_CORR_LENGTH_Y,
                        pdf->getCoherenceLengthY());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DGaussItem::P_GAMMA,
                        Units::rad2deg(pdf->getGamma()) );
        }
        else if(const FTDistribution2DGate *pdf =
                dynamic_cast<const FTDistribution2DGate *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i],
                                      Constants::FTDistribution2DGateType);
            pdfItem->setRegisteredProperty(
                        FTDistribution2DGateItem::P_CORR_LENGTH_X,
                        pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DGateItem::P_CORR_LENGTH_Y,
                        pdf->getCoherenceLengthY());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DGateItem::P_GAMMA,
                        Units::rad2deg(pdf->getGamma()) );
        }
        else if(const FTDistribution2DCone *pdf =
                dynamic_cast<const FTDistribution2DCone *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i],
                                      Constants::FTDistribution2DConeType);
            pdfItem->setRegisteredProperty(
                        FTDistribution2DConeItem::P_CORR_LENGTH_X,
                        pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DConeItem::P_CORR_LENGTH_Y,
                        pdf->getCoherenceLengthY());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DConeItem::P_GAMMA,
                        Units::rad2deg(pdf->getGamma()) );
        }
        else if(const FTDistribution2DVoigt *pdf =
                dynamic_cast<const FTDistribution2DVoigt *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i],
                                      Constants::FTDistribution2DVoigtType);
            pdfItem->setRegisteredProperty(
                        FTDistribution2DVoigtItem::P_CORR_LENGTH_X,
                        pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DVoigtItem::P_CORR_LENGTH_Y,
                        pdf->getCoherenceLengthY());
            pdfItem->setRegisteredProperty(
                        FTDistribution2DVoigtItem::P_GAMMA,
                        Units::rad2deg(pdf->getGamma()) );
            pdfItem->setRegisteredProperty(
                        FTDistribution2DVoigtItem::P_ETA, pdf->getEta());
        }
        else {
            throw GUIHelpers::Error("TransformFromDomain::"
                "setItemFromSample(ParameterizedItem *item, const "
                "InterferenceFunction2DParaCrystal *sample) -> Error");
        }

    }
}

void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                              const InterferenceFunction2DLattice *sample)
{
    ParameterizedItem *latticeTypeItem(0);
    Lattice2DIFParameters lattice_params = sample->getLatticeParameters();
    if( TransformFromDomain::isSquareLattice(lattice_params.m_length_1,
            lattice_params.m_length_2, lattice_params.m_angle)) {
        latticeTypeItem = item->setGroupProperty(
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                    Constants::SquareLatticeType);
        latticeTypeItem->setRegisteredProperty(
            SquareLatticeTypeItem::P_LATTICE_LENGTH,
            lattice_params.m_length_1);
    }
    else if( TransformFromDomain::isHexagonalLattice(lattice_params.m_length_1,
            lattice_params.m_length_2, lattice_params.m_angle)) {
        latticeTypeItem = item->setGroupProperty(
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                    Constants::HexagonalLatticeType);
        latticeTypeItem->setRegisteredProperty(
            HexagonalLatticeTypeItem::P_LATTICE_LENGTH,
            lattice_params.m_length_1);
    }
    else {
        latticeTypeItem = item->setGroupProperty(
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                    Constants::BasicLatticeType);
        latticeTypeItem->setRegisteredProperty(
            BasicLatticeTypeItem::P_LATTICE_LENGTH1,
            lattice_params.m_length_1);
        latticeTypeItem->setRegisteredProperty(
            BasicLatticeTypeItem::P_LATTICE_LENGTH2,
            lattice_params.m_length_2);
        latticeTypeItem->setRegisteredProperty(
            BasicLatticeTypeItem::P_LATTICE_ANGLE,
            Units::rad2deg(lattice_params.m_angle));
    }

    item->setRegisteredProperty(
                InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE,
                Units::rad2deg(lattice_params.m_xi));

    const IFTDistribution2D *p_pdf = sample->getProbabilityDistribution();

    QString group_name = InterferenceFunction2DLatticeItem::P_PDF;

    qDebug() << "    group_name" << group_name;
    if(const FTDistribution2DCauchy *pdf =
            dynamic_cast<const FTDistribution2DCauchy *>(p_pdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                  Constants::FTDistribution2DCauchyType);
        pdfItem->setRegisteredProperty(
                    FTDistribution2DCauchyItem::P_CORR_LENGTH_X,
                    pdf->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DCauchyItem::P_CORR_LENGTH_Y,
                    pdf->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DCauchyItem::P_GAMMA,
                    Units::rad2deg(pdf->getGamma()) );
    }
    else if(const FTDistribution2DGauss *pdf =
            dynamic_cast<const FTDistribution2DGauss *>(p_pdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                  Constants::FTDistribution2DGaussType);
        pdfItem->setRegisteredProperty(
                    FTDistribution2DGaussItem::P_CORR_LENGTH_X,
                    pdf->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DGaussItem::P_CORR_LENGTH_Y,
                    pdf->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DGaussItem::P_GAMMA,
                    Units::rad2deg(pdf->getGamma()) );
    }
    else if(const FTDistribution2DGate *pdf =
            dynamic_cast<const FTDistribution2DGate *>(p_pdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                  Constants::FTDistribution2DGateType);
        pdfItem->setRegisteredProperty(
                    FTDistribution2DGateItem::P_CORR_LENGTH_X,
                    pdf->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DGateItem::P_CORR_LENGTH_Y,
                    pdf->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DGateItem::P_GAMMA,
                    Units::rad2deg(pdf->getGamma()) );
    }
    else if(const FTDistribution2DCone *pdf =
            dynamic_cast<const FTDistribution2DCone *>(p_pdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                  Constants::FTDistribution2DConeType);
        pdfItem->setRegisteredProperty(
                    FTDistribution2DConeItem::P_CORR_LENGTH_X,
                    pdf->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DConeItem::P_CORR_LENGTH_Y,
                    pdf->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DConeItem::P_GAMMA,
                    Units::rad2deg(pdf->getGamma()) );
    }
    else if(const FTDistribution2DVoigt *pdf =
            dynamic_cast<const FTDistribution2DVoigt *>(p_pdf)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                  Constants::FTDistribution2DVoigtType);
        pdfItem->setRegisteredProperty(
                    FTDistribution2DVoigtItem::P_CORR_LENGTH_X,
                    pdf->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DVoigtItem::P_CORR_LENGTH_Y,
                    pdf->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(
                    FTDistribution2DVoigtItem::P_GAMMA,
                    Units::rad2deg(pdf->getGamma()) );
        pdfItem->setRegisteredProperty(
                    FTDistribution2DVoigtItem::P_ETA, pdf->getEta());
    }
    else {
        throw GUIHelpers::Error("TransformFromDomain::"
            "setItemFromSample(ParameterizedItem *item, const "
            "InterferenceFunction2DLattice *sample) -> Error");
    }
}


void TransformFromDomain::setItemFromSample(ParameterizedItem *layerItem,
                     const Layer *layer, const LayerInterface *top_interface)
{
    layerItem->setItemName(layer->getName().c_str());
    layerItem->setRegisteredProperty(LayerItem::P_THICKNESS,
                                     layer->getThickness());
    layerItem->setGroupProperty(LayerItem::P_ROUGHNESS,
                                Constants::LayerZeroRoughnessType);

    if(top_interface) {
        const LayerRoughness *roughness = top_interface->getRoughness();
        if(TransformFromDomain::isValidRoughness(roughness)) {
            ParameterizedItem *roughnessItem =
                    layerItem->setGroupProperty(LayerItem::P_ROUGHNESS,
                                       Constants::LayerBasicRoughnessType);
            TransformFromDomain::setItemFromSample(roughnessItem, roughness);
        }
    }
}


void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                                            const LayerRoughness *sample)
{
    item->setRegisteredProperty(LayerBasicRoughnessItem::P_SIGMA,
                                sample->getSigma());
    item->setRegisteredProperty(LayerBasicRoughnessItem::P_HURST,
                                sample->getHurstParameter());
    item->setRegisteredProperty(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH,
                                sample->getLatteralCorrLength());
}


void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                                            const ParticleDistribution *sample)
{
    ParameterDistribution par_distr = sample->getParameterDistribution();
    item->setRegisteredProperty(
        ParticleDistributionItem::P_DISTRIBUTED_PARAMETER,
                QString::fromStdString(par_distr.getMainParameterName()) );
    item->setRegisteredProperty(
        ParticleDistributionItem::P_SAMPLE_NUMBER, (int)par_distr.getNbrSamples());
    item->setRegisteredProperty(
        ParticleDistributionItem::P_SIGMA_FACTOR, par_distr.getSigmaFactor());

    const IDistribution1D *p_distribution = par_distr.getDistribution();

    QString group_name = ParticleDistributionItem::P_DISTRIBUTION;

    if(const DistributionGate *distr =
            dynamic_cast<const DistributionGate *>(p_distribution)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::DistributionGateType);
        pdfItem->setRegisteredProperty(
                    DistributionGateItem::P_MIN, distr->getMin());
        pdfItem->setRegisteredProperty(
                    DistributionGateItem::P_MAX, distr->getMax());
    }
    else if(const DistributionLorentz *distr =
            dynamic_cast<const DistributionLorentz *>(p_distribution)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::DistributionLorentzType);
        pdfItem->setRegisteredProperty(
                    DistributionLorentzItem::P_MEAN, distr->getMean());
        pdfItem->setRegisteredProperty(
                    DistributionLorentzItem::P_HWHM, distr->getHWHM());
    }
    else if(const DistributionGaussian *distr =
            dynamic_cast<const DistributionGaussian *>(p_distribution)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::DistributionGaussianType);
        pdfItem->setRegisteredProperty(
                    DistributionGaussianItem::P_MEAN, distr->getMean());
        pdfItem->setRegisteredProperty(
                    DistributionGaussianItem::P_STD_DEV, distr->getStdDev());
    }
    else if(const DistributionLogNormal *distr =
            dynamic_cast<const DistributionLogNormal *>(p_distribution)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::DistributionLogNormalType);
        pdfItem->setRegisteredProperty(
                  DistributionLogNormalItem::P_MEDIAN, distr->getMedian());
        pdfItem->setRegisteredProperty(
                  DistributionLogNormalItem::P_SCALE_PAR, distr->getScalePar());
    }
    else if(const DistributionCosine *distr =
            dynamic_cast<const DistributionCosine *>(p_distribution)) {
        ParameterizedItem *pdfItem = item->setGroupProperty(group_name,
                                      Constants::DistributionCosineType);
        pdfItem->setRegisteredProperty(
                  DistributionCosineItem::P_MEAN, distr->getMean());
        pdfItem->setRegisteredProperty(
                  DistributionCosineItem::P_SIGMA, distr->getSigma());
    }
}


//! Returns true if given roughness is non-zero roughness
bool TransformFromDomain::isValidRoughness(const LayerRoughness *roughness)
{
    if(!roughness) return false;
    if(roughness->getSigma() == 0  && roughness->getHurstParameter() == 0.0
            && roughness->getLatteralCorrLength() == 0.0) return false;
    return true;
}


bool TransformFromDomain::isSquareLattice(double length1, double length2,
                                          double angle)
{
    if(length1 == length2 && Numeric::areAlmostEqual(angle, M_PI/2.0)) {
        return true;
    }
    return false;
}


bool TransformFromDomain::isHexagonalLattice(double length1, double length2,
                                             double angle)
{
    if(length1 == length2 && Numeric::areAlmostEqual(angle, 2*M_PI/3.0)) {
        return true;
    }
    return false;
}


//! FIXME Remove hardcoded strings
QString TransformFromDomain::getDetectorBinning(const Detector *detector)
{
    boost::scoped_ptr<IAxis> phi_axis(detector->getAxis(0).clone());
    boost::scoped_ptr<IAxis> alpha_axis(detector->getAxis(1).clone());

    if( dynamic_cast<ConstKBinAxis *>(phi_axis.get())
            && dynamic_cast<ConstKBinAxis *>(alpha_axis.get())) {
        return Constants::AXIS_CONSTK_BINNING;
    }
    else if( dynamic_cast<FixedBinAxis *>(phi_axis.get())
             && dynamic_cast<FixedBinAxis *>(alpha_axis.get())) {
        return Constants::AXIS_FIXED_BINNING;
    }
    else {
        throw GUIHelpers::Error("TransformFromDomain::getDetectorBinning()"
                                " -> Error. Can't determine detector binning");
    }
}


void TransformFromDomain::setItemFromSample(BeamItem *beamItem, const Beam &beam)
{
    Q_ASSERT(beamItem);
    beamItem->setIntensity(beam.getIntensity());
    beamItem->setWavelength(beam.getWavelength());
    beamItem->setInclinationAngle(Units::rad2deg(-1.0*beam.getAlpha()));
    beamItem->setAzimuthalAngle(Units::rad2deg(-1.0*beam.getPhi()));
}



void TransformFromDomain::setItemFromSample(PhiAlphaDetectorItem *detectorItem, const Detector &detector)
{
    Q_ASSERT(detectorItem);
    const IAxis &phi_axis = detector.getAxis(0);
    const IAxis &alpha_axis = detector.getAxis(1);

    ComboProperty binning_property = detectorItem->getRegisteredProperty(
        PhiAlphaDetectorItem::P_BINNING).value<ComboProperty>();
    binning_property.setValue(TransformFromDomain::getDetectorBinning(&detector));
    detectorItem->setRegisteredProperty(
        PhiAlphaDetectorItem::P_BINNING, binning_property.getVariant());

    BasicAxisItem *phiAxisItem = dynamic_cast<BasicAxisItem *>(detectorItem->getSubItems()[PhiAlphaDetectorItem::P_PHI_AXIS]);
    Q_ASSERT(phiAxisItem);
    phiAxisItem->setRegisteredProperty(BasicAxisItem::P_NBINS, (int)phi_axis.getSize());
    phiAxisItem->setRegisteredProperty(BasicAxisItem::P_MIN, Units::rad2deg(phi_axis.getMin()));
    phiAxisItem->setRegisteredProperty(BasicAxisItem::P_MAX, Units::rad2deg(phi_axis.getMax()));

    BasicAxisItem *alphaAxisItem = dynamic_cast<BasicAxisItem *>(detectorItem->getSubItems()[PhiAlphaDetectorItem::P_ALPHA_AXIS]);
    Q_ASSERT(alphaAxisItem);
    alphaAxisItem->setRegisteredProperty(BasicAxisItem::P_NBINS, (int)alpha_axis.getSize());
    alphaAxisItem->setRegisteredProperty(BasicAxisItem::P_MIN, Units::rad2deg(alpha_axis.getMin()));
    alphaAxisItem->setRegisteredProperty(BasicAxisItem::P_MAX, Units::rad2deg(alpha_axis.getMax()));

}
