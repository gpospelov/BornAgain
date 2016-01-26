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
#include "SphericalDetector.h"
#include "ParticleItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleDistribution.h"
#include "Distributions.h"
#include "DistributionItem.h"
#include "DetectorItems.h"
#include "BeamItem.h"
#include "ComboProperty.h"
#include "DistributionHandler.h"
#include "ParameterDistribution.h"
#include "BeamDistributionItem.h"
#include "BeamAngleItems.h"
#include "AxesItems.h"
#include "ResolutionFunction2DGaussian.h"
#include "ResolutionFunctionItems.h"
#include "ConvolutionDetectorResolution.h"
#include "DetectorMask.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Line.h"
#include "InfinitePlane.h"
#include "MaskItems.h"
#include "BornAgainNamespace.h"

#include <QString>
#include <QDebug>
#include <vector>

using namespace BornAgain;

void SetPDF1D(ParameterizedItem *item, const IFTDistribution1D *pdf, QString group_name);
void setPDF2D(ParameterizedItem *item, const IFTDistribution2D *pdf, QString group_name);
void set2DLatticeParameters(ParameterizedItem *item, Lattice2DParameters lattice_params,
                            ParameterizedItem *lattice_item);
void setDistribution(ParameterizedItem *item, ParameterDistribution par_distr,
                     QString group_name, double factor = 1.0);

void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                                            const InterferenceFunctionRadialParaCrystal *sample)
{
    item->setRegisteredProperty(InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE,
                                sample->getPeakDistance());
    item->setRegisteredProperty(InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH,
                                sample->getDampingLength());
    item->setRegisteredProperty(InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE,
                                sample->getDomainSize());
    item->setRegisteredProperty(InterferenceFunctionRadialParaCrystalItem::P_KAPPA,
                                sample->getKappa());

    const IFTDistribution1D *ipdf = sample->getProbabilityDistribution();
    QString group_name = InterferenceFunctionRadialParaCrystalItem::P_PDF;
    qDebug() << "    group_name" << group_name;
    SetPDF1D(item, ipdf, group_name);
}

void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                                            const InterferenceFunction2DParaCrystal *sample)
{
    ParameterizedItem *lattice_item(0);
    Lattice2DParameters lattice_params = sample->getLatticeParameters();
    set2DLatticeParameters(item, lattice_params, lattice_item);

    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH,
                                sample->getDampingLength());
    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1,
                                sample->getDomainSizes()[0]);
    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2,
                                sample->getDomainSizes()[1]);
    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION,
                                sample->getIntegrationOverXi());

    std::vector<const IFTDistribution2D *> pdfs = sample->getProbabilityDistributions();
    QStringList group_names;
    group_names << InterferenceFunction2DParaCrystalItem::P_PDF1
                << InterferenceFunction2DParaCrystalItem::P_PDF2;
    for (size_t i = 0; i < pdfs.size(); ++i) {
        qDebug() << "    group_name" << group_names[i];
        setPDF2D(item, pdfs[i], group_names[i]);
    }
}

void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                                            const InterferenceFunction1DLattice *sample)
{
    Lattice1DParameters lattice_params = sample->getLatticeParameters();

    item->setRegisteredProperty(InterferenceFunction1DLatticeItem::P_LENGTH,
                                lattice_params.m_length);
    item->setRegisteredProperty(InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE,
                                Units::rad2deg(lattice_params.m_xi));

    const IFTDistribution1D *pdf = sample->getProbabilityDistribution();
    QString group_name = InterferenceFunction1DLatticeItem::P_PDF;
    qDebug() << "    group_name" << group_name;
    SetPDF1D(item, pdf, group_name);
}

void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                                            const InterferenceFunction2DLattice *sample)
{
    ParameterizedItem *lattice_item(0);
    Lattice2DParameters lattice_params = sample->getLatticeParameters();
    set2DLatticeParameters(item, lattice_params, lattice_item);

    const IFTDistribution2D *p_pdf = sample->getProbabilityDistribution();
    QString group_name = InterferenceFunction2DLatticeItem::P_PDF;
    qDebug() << "    group_name" << group_name;
    setPDF2D(item, p_pdf, group_name);
}

void TransformFromDomain::setItemFromSample(ParameterizedItem *layerItem, const Layer *layer,
                                            const LayerInterface *top_interface)
{
    layerItem->setRegisteredProperty(LayerItem::P_THICKNESS, layer->getThickness());
    layerItem->setGroupProperty(LayerItem::P_ROUGHNESS, Constants::LayerZeroRoughnessType);

    if (top_interface) {
        const LayerRoughness *roughness = top_interface->getRoughness();
        if (TransformFromDomain::isValidRoughness(roughness)) {
            ParameterizedItem *roughnessItem = layerItem->setGroupProperty(
                LayerItem::P_ROUGHNESS, Constants::LayerBasicRoughnessType);
            TransformFromDomain::setItemFromSample(roughnessItem, roughness);
        }
    }
}

void TransformFromDomain::setItemFromSample(ParameterizedItem *item, const LayerRoughness *sample)
{
    item->setRegisteredProperty(LayerBasicRoughnessItem::P_SIGMA, sample->getSigma());
    item->setRegisteredProperty(LayerBasicRoughnessItem::P_HURST, sample->getHurstParameter());
    item->setRegisteredProperty(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH,
                                sample->getLatteralCorrLength());
}

//! Initialization of ParticleDistributionItem
void TransformFromDomain::setItemFromSample(ParameterizedItem *item,
                                            const ParticleDistribution *sample)
{
    item->setRegisteredProperty(ParticleItem::P_ABUNDANCE, sample->getAbundance());

    ParameterDistribution par_distr = sample->getParameterDistribution();
    QString main_distr_par_name = QString::fromStdString(par_distr.getMainParameterName());
    ComboProperty combo_property
        = item->getRegisteredProperty(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
              .value<ComboProperty>();
    combo_property.setCachedValue(main_distr_par_name);
    combo_property.setCacheContainsGUIFlag(false);
    item->setRegisteredProperty(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER,
                                combo_property.getVariant());

    QString group_name = ParticleDistributionItem::P_DISTRIBUTION;
    setDistribution(item, par_distr, group_name);
}

//! Returns true if given roughness is non-zero roughness
bool TransformFromDomain::isValidRoughness(const LayerRoughness *roughness)
{
    if (!roughness)
        return false;
    if (roughness->getSigma() == 0 && roughness->getHurstParameter() == 0.0
        && roughness->getLatteralCorrLength() == 0.0)
        return false;
    return true;
}

bool TransformFromDomain::isSquareLattice(double length1, double length2, double angle)
{
    if (length1 == length2 && Numeric::areAlmostEqual(angle, Units::PI / 2.0)) {
        return true;
    }
    return false;
}

bool TransformFromDomain::isHexagonalLattice(double length1, double length2, double angle)
{
    if (length1 == length2 && Numeric::areAlmostEqual(angle, 2 * Units::PI / 3.0)) {
        return true;
    }
    return false;
}

void TransformFromDomain::setItemFromSample(BeamItem *beamItem, const GISASSimulation &simulation)
{
    Q_ASSERT(beamItem);
    Beam beam = simulation.getInstrument().getBeam();

    beamItem->setIntensity(beam.getIntensity());
    beamItem->setWavelength(beam.getWavelength());
    beamItem->setInclinationAngle(Units::rad2deg(beam.getAlpha()));
    beamItem->setAzimuthalAngle(Units::rad2deg(beam.getPhi()));

    // distribution parameters
    const DistributionHandler::Distributions_t distributions
        = simulation.getDistributionHandler().getDistributions();
    for (size_t i = 0; i < distributions.size(); ++i) {
        ParameterPattern pattern_wavelength;
        pattern_wavelength.beginsWith("*").add(BeamType).add(Wavelength);
        ParameterPattern pattern_alpha;
        pattern_alpha.beginsWith("*").add(BeamType).add(Alpha);
        ParameterPattern pattern_phi;
        pattern_phi.beginsWith("*").add(BeamType).add(Phi);
        std::string mainParameterName = distributions[i].getMainParameterName();
        if (mainParameterName == pattern_wavelength.toStdString()) {
            BeamDistributionItem *beamWavelength = dynamic_cast<BeamDistributionItem *>(
                beamItem->getSubItems()[BeamItem::P_WAVELENGTH]);
            setItemFromSample(beamWavelength, distributions[i]);
        } else if (mainParameterName == pattern_alpha.toStdString()) {
            BeamDistributionItem *inclinationAngle = dynamic_cast<BeamDistributionItem *>(
                beamItem->getSubItems()[BeamItem::P_INCLINATION_ANGLE]);
            setItemFromSample(inclinationAngle, distributions[i]);
        } else if (mainParameterName == pattern_phi.toStdString()) {
            BeamDistributionItem *azimuthalAngle = dynamic_cast<BeamDistributionItem *>(
                beamItem->getSubItems()[BeamItem::P_AZIMUTHAL_ANGLE]);
            setItemFromSample(azimuthalAngle, distributions[i]);
        }
    }
}

void TransformFromDomain::setItemFromSample(PhiAlphaDetectorItem *detectorItem,
                                            const GISASSimulation &simulation)
{
    Q_ASSERT(detectorItem);
    const IDetector2D *detector = simulation.getInstrument().getDetector();

    // Axes
    const IAxis &phi_axis = detector->getAxis(0);
    const IAxis &alpha_axis = detector->getAxis(1);

    BasicAxisItem *phiAxisItem = dynamic_cast<BasicAxisItem *>(
        detectorItem->getSubItems()[PhiAlphaDetectorItem::P_PHI_AXIS]);
    Q_ASSERT(phiAxisItem);
    phiAxisItem->setRegisteredProperty(BasicAxisItem::P_NBINS, (int)phi_axis.getSize());
    phiAxisItem->setRegisteredProperty(BasicAxisItem::P_MIN, Units::rad2deg(phi_axis.getMin()));
    phiAxisItem->setRegisteredProperty(BasicAxisItem::P_MAX, Units::rad2deg(phi_axis.getMax()));

    BasicAxisItem *alphaAxisItem = dynamic_cast<BasicAxisItem *>(
        detectorItem->getSubItems()[PhiAlphaDetectorItem::P_ALPHA_AXIS]);
    Q_ASSERT(alphaAxisItem);
    alphaAxisItem->setRegisteredProperty(BasicAxisItem::P_NBINS, (int)alpha_axis.getSize());
    alphaAxisItem->setRegisteredProperty(BasicAxisItem::P_MIN, Units::rad2deg(alpha_axis.getMin()));
    alphaAxisItem->setRegisteredProperty(BasicAxisItem::P_MAX, Units::rad2deg(alpha_axis.getMax()));

    // detector resolution
    if (const IDetectorResolution *p_resfunc = detector->getDetectorResolutionFunction()) {
        if (const ConvolutionDetectorResolution *p_convfunc
            = dynamic_cast<const ConvolutionDetectorResolution *>(p_resfunc)) {
            if (const ResolutionFunction2DGaussian *resfunc
                = dynamic_cast<const ResolutionFunction2DGaussian *>(
                    p_convfunc->getResolutionFunction2D())) {
                ParameterizedItem *item
                    = detectorItem->setGroupProperty(PhiAlphaDetectorItem::P_RESOLUTION_FUNCTION,
                                                     Constants::ResolutionFunction2DGaussianType);
                item->setRegisteredProperty(ResolutionFunction2DGaussianItem::P_SIGMA_X,
                                            Units::rad2deg(resfunc->getSigmaX()));
                item->setRegisteredProperty(ResolutionFunction2DGaussianItem::P_SIGMA_Y,
                                            Units::rad2deg(resfunc->getSigmaY()));
            } else {
                throw GUIHelpers::Error("TransformFromDomain::setItemFromSample("
                                        "PhiAlphaDetectorItem *detectorItem, const GISASSimulation "
                                        "&simulation) -> Error, unknown detector resolution "
                                        "function");
            }
        } else {
            throw GUIHelpers::Error(
                "TransformFromDomain::setItemFromSample(PhiAlphaDetectorItem "
                "*detectorItem, const GISASSimulation &simulation) -> Error, not a "
                "ConvolutionDetectorResolution function");
        }
    }
}


void TransformFromDomain::setDetectorMasks(DetectorItem *detectorItem, const GISASSimulation &simulation)
{
    Q_ASSERT(detectorItem);

    const IDetector2D *detector = simulation.getInstrument().getDetector();
    const DetectorMask *detectorMask = detector->getDetectorMask();
    if(detectorMask && detectorMask->getNumberOfMasks()) {
        MaskContainerItem *containerItem = new MaskContainerItem();
        detectorItem->insertChildItem(-1, containerItem);
        for(size_t i_mask=0; i_mask<detectorMask->getNumberOfMasks(); ++i_mask) {
            bool mask_value(false);
            const Geometry::IShape2D *shape = detectorMask->getMaskShape(i_mask, mask_value);
            if(const Geometry::Ellipse *ellipse = dynamic_cast<const Geometry::Ellipse *>(shape)) {
                EllipseItem *ellipseItem = new EllipseItem();
                ellipseItem->setRegisteredProperty(EllipseItem::P_XCENTER, Units::rad2deg(ellipse->getCenterX()));
                ellipseItem->setRegisteredProperty(EllipseItem::P_YCENTER, Units::rad2deg(ellipse->getCenterY()));
                ellipseItem->setRegisteredProperty(EllipseItem::P_XRADIUS, Units::rad2deg(ellipse->getRadiusX()));
                ellipseItem->setRegisteredProperty(EllipseItem::P_YRADIUS, Units::rad2deg(ellipse->getRadiusY()));
                ellipseItem->setRegisteredProperty(EllipseItem::P_ANGLE, Units::rad2deg(ellipse->getTheta()));
                ellipseItem->setRegisteredProperty(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertChildItem(0, ellipseItem);

            }
            else if(const Geometry::Rectangle *rectangle = dynamic_cast<const Geometry::Rectangle *>(shape)) {
                RectangleItem *rectangleItem = new RectangleItem();
                rectangleItem->setRegisteredProperty(RectangleItem::P_XLOW, Units::rad2deg(rectangle->getXlow()));
                rectangleItem->setRegisteredProperty(RectangleItem::P_YLOW, Units::rad2deg(rectangle->getYlow()));
                rectangleItem->setRegisteredProperty(RectangleItem::P_XUP, Units::rad2deg(rectangle->getXup()));
                rectangleItem->setRegisteredProperty(RectangleItem::P_YUP, Units::rad2deg(rectangle->getYup()));
                rectangleItem->setRegisteredProperty(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertChildItem(0, rectangleItem);

            }
            else if(const Geometry::Polygon *polygon = dynamic_cast<const Geometry::Polygon *>(shape)) {
                PolygonItem *polygonItem = new PolygonItem();
                std::vector<double> xpos, ypos;
                polygon->getPoints(xpos, ypos);
                for(size_t i_point=0; i_point<xpos.size(); ++i_point) {
                    PolygonPointItem *pointItem = new PolygonPointItem();
                    pointItem->setRegisteredProperty(PolygonPointItem::P_POSX, Units::rad2deg(xpos[i_point]));
                    pointItem->setRegisteredProperty(PolygonPointItem::P_POSY, Units::rad2deg(ypos[i_point]));
                    polygonItem->insertChildItem(-1, pointItem);
                }

                polygonItem->setRegisteredProperty(MaskItem::P_MASK_VALUE, mask_value);
                polygonItem->setRegisteredProperty(PolygonItem::P_ISCLOSED, true);

                containerItem->insertChildItem(0, polygonItem);
            }
            else if(const Geometry::VerticalLine *vline = dynamic_cast<const Geometry::VerticalLine *>(shape)) {
                VerticalLineItem *lineItem = new VerticalLineItem();
                lineItem->setRegisteredProperty(VerticalLineItem::P_POSX, Units::rad2deg(vline->getXpos()));
                lineItem->setRegisteredProperty(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertChildItem(0, lineItem);
            }
            else if(const Geometry::HorizontalLine *hline = dynamic_cast<const Geometry::HorizontalLine *>(shape)) {
                HorizontalLineItem *lineItem = new HorizontalLineItem();
                lineItem->setRegisteredProperty(HorizontalLineItem::P_POSY, Units::rad2deg(hline->getYpos()));
                lineItem->setRegisteredProperty(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertChildItem(0, lineItem);
            }
            else if(const Geometry::InfinitePlane *plane = dynamic_cast<const Geometry::InfinitePlane *>(shape)) {
                Q_UNUSED(plane);
                MaskAllItem *planeItem = new MaskAllItem();
                planeItem->setRegisteredProperty(MaskItem::P_MASK_VALUE, mask_value);
                containerItem->insertChildItem(-1, planeItem);
            }
            else {
                throw GUIHelpers::Error("TransformFromDomain::setDetectorMasks() -> Error. "
                                        "Unknown shape");
            }
        }
    }
}

void TransformFromDomain::setItemFromSample(BeamDistributionItem *beamDistributionItem,
                                            const ParameterDistribution &parameterDistribution)
{
    Q_ASSERT(beamDistributionItem);

    if (parameterDistribution.getMinValue() < parameterDistribution.getMaxValue()) {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(BeamDistributionItem *beamDistributionItem,"
            "const ParameterDistribution &parameterDistribution) -> Error. ParameterDistribution "
            "with defined min,max are not yet implemented in GUI");
    }

    double unit_factor(1.0);
    if (beamDistributionItem->modelType() == Constants::BeamAzimuthalAngleType
        || beamDistributionItem->modelType() == Constants::BeamInclinationAngleType) {
        unit_factor = 1. / Units::degree;
    }
    QString group_name = BeamDistributionItem::P_DISTRIBUTION;
    setDistribution(beamDistributionItem, parameterDistribution, group_name, unit_factor);
}

QString TransformFromDomain::translateParameterNameToGUI(ParameterizedItem *item,
                                                         const QString &par_name)
{
    auto gui_par_list = item->getParameterTreeList();
    for (auto gui_par_name : gui_par_list) {
        auto domain_par_name = QString::fromStdString(item->translateParameterName(gui_par_name));
        if (domain_par_name == par_name) {
            return gui_par_name;
        }
    }
    return QString();
}

void SetPDF1D(ParameterizedItem *item, const IFTDistribution1D *ipdf, QString group_name)
{
    if (const FTDistribution1DCauchy *pdf = dynamic_cast<const FTDistribution1DCauchy *>(ipdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DCauchyType);
        pdfItem->setRegisteredProperty(FTDistribution1DCauchyItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DGauss *pdf
               = dynamic_cast<const FTDistribution1DGauss *>(ipdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DGaussType);
        pdfItem->setRegisteredProperty(FTDistribution1DGaussItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DGate *pdf = dynamic_cast<const FTDistribution1DGate *>(ipdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DGateType);
        pdfItem->setRegisteredProperty(FTDistribution1DGateItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DTriangle *pdf
               = dynamic_cast<const FTDistribution1DTriangle *>(ipdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DTriangleType);
        pdfItem->setRegisteredProperty(FTDistribution1DTriangleItem::P_CORR_LENGTH,
                                       pdf->getOmega());
    } else if (const FTDistribution1DCosine *pdf
               = dynamic_cast<const FTDistribution1DCosine *>(ipdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DCosineType);
        pdfItem->setRegisteredProperty(FTDistribution1DCosineItem::P_CORR_LENGTH, pdf->getOmega());
    } else if (const FTDistribution1DVoigt *pdf
               = dynamic_cast<const FTDistribution1DVoigt *>(ipdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DVoigtType);
        pdfItem->setRegisteredProperty(FTDistribution1DVoigtItem::P_CORR_LENGTH, pdf->getOmega());
        pdfItem->setRegisteredProperty(FTDistribution1DVoigtItem::P_ETA, pdf->getEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::"
                                "setItemFromSample(ParameterizedItem *item, const "
                                "InterferenceFunction2DParaCrystal *sample) -> Error");
    }
}

void setPDF2D(ParameterizedItem *item, const IFTDistribution2D *pdf, QString group_name)
{
    if (const FTDistribution2DCauchy *pdf_cauchy
        = dynamic_cast<const FTDistribution2DCauchy *>(pdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DCauchyType);
        pdfItem->setRegisteredProperty(FTDistribution2DCauchyItem::P_CORR_LENGTH_X,
                                       pdf_cauchy->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(FTDistribution2DCauchyItem::P_CORR_LENGTH_Y,
                                       pdf_cauchy->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(FTDistribution2DCauchyItem::P_GAMMA,
                                       Units::rad2deg(pdf_cauchy->getGamma()));
    } else if (const FTDistribution2DGauss *pdf_gauss
               = dynamic_cast<const FTDistribution2DGauss *>(pdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DGaussType);
        pdfItem->setRegisteredProperty(FTDistribution2DGaussItem::P_CORR_LENGTH_X,
                                       pdf_gauss->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(FTDistribution2DGaussItem::P_CORR_LENGTH_Y,
                                       pdf_gauss->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(FTDistribution2DGaussItem::P_GAMMA,
                                       Units::rad2deg(pdf_gauss->getGamma()));
    } else if (const FTDistribution2DGate *pdf_gate
               = dynamic_cast<const FTDistribution2DGate *>(pdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DGateType);
        pdfItem->setRegisteredProperty(FTDistribution2DGateItem::P_CORR_LENGTH_X,
                                       pdf_gate->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(FTDistribution2DGateItem::P_CORR_LENGTH_Y,
                                       pdf_gate->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(FTDistribution2DGateItem::P_GAMMA,
                                       Units::rad2deg(pdf_gate->getGamma()));
    } else if (const FTDistribution2DCone *pdf_cone
               = dynamic_cast<const FTDistribution2DCone *>(pdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DConeType);
        pdfItem->setRegisteredProperty(FTDistribution2DConeItem::P_CORR_LENGTH_X,
                                       pdf_cone->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(FTDistribution2DConeItem::P_CORR_LENGTH_Y,
                                       pdf_cone->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(FTDistribution2DConeItem::P_GAMMA,
                                       Units::rad2deg(pdf_cone->getGamma()));
    } else if (const FTDistribution2DVoigt *pdf_voigt
               = dynamic_cast<const FTDistribution2DVoigt *>(pdf)) {
        ParameterizedItem *pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DVoigtType);
        pdfItem->setRegisteredProperty(FTDistribution2DVoigtItem::P_CORR_LENGTH_X,
                                       pdf_voigt->getCoherenceLengthX());
        pdfItem->setRegisteredProperty(FTDistribution2DVoigtItem::P_CORR_LENGTH_Y,
                                       pdf_voigt->getCoherenceLengthY());
        pdfItem->setRegisteredProperty(FTDistribution2DVoigtItem::P_GAMMA,
                                       Units::rad2deg(pdf_voigt->getGamma()));
        pdfItem->setRegisteredProperty(FTDistribution2DVoigtItem::P_ETA, pdf_voigt->getEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setPDF2D: -> Error");
    }
}

void set2DLatticeParameters(ParameterizedItem *item, Lattice2DParameters lattice_params,
                            ParameterizedItem *lattice_item)
{
    if (TransformFromDomain::isSquareLattice(lattice_params.m_length_1, lattice_params.m_length_2,
                                             lattice_params.m_angle)) {
        lattice_item = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                                 Constants::SquareLatticeType);
        lattice_item->setRegisteredProperty(SquareLatticeTypeItem::P_LATTICE_LENGTH,
                                               lattice_params.m_length_1);
    } else if (TransformFromDomain::isHexagonalLattice(
                   lattice_params.m_length_1, lattice_params.m_length_2, lattice_params.m_angle)) {
        lattice_item = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                                 Constants::HexagonalLatticeType);
        lattice_item->setRegisteredProperty(HexagonalLatticeTypeItem::P_LATTICE_LENGTH,
                                               lattice_params.m_length_1);
    } else {
        lattice_item = item->setGroupProperty(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE,
                                                 Constants::BasicLatticeType);
        lattice_item->setRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH1,
                                               lattice_params.m_length_1);
        lattice_item->setRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH2,
                                               lattice_params.m_length_2);
        lattice_item->setRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_ANGLE,
                                               Units::rad2deg(lattice_params.m_angle));
    }
    item->setRegisteredProperty(InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE,
                                Units::rad2deg(lattice_params.m_xi));
}

void setDistribution(ParameterizedItem *item, ParameterDistribution par_distr,
                     QString group_name, double factor)
{
    const IDistribution1D *p_distribution = par_distr.getDistribution();
    ParameterizedItem *pdfItem = 0;
    if (const DistributionGate *distr = dynamic_cast<const DistributionGate *>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionGateType);
        pdfItem->setRegisteredProperty(DistributionGateItem::P_MIN, factor*distr->getMin());
        pdfItem->setRegisteredProperty(DistributionGateItem::P_MAX, factor*distr->getMax());
    } else if (const DistributionLorentz *distr
               = dynamic_cast<const DistributionLorentz *>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionLorentzType);
        pdfItem->setRegisteredProperty(DistributionLorentzItem::P_MEAN, factor*distr->getMean());
        pdfItem->setRegisteredProperty(DistributionLorentzItem::P_HWHM, factor*distr->getHWHM());
    } else if (const DistributionGaussian *distr
               = dynamic_cast<const DistributionGaussian *>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionGaussianType);
        pdfItem->setRegisteredProperty(DistributionGaussianItem::P_MEAN, factor*distr->getMean());
        pdfItem->setRegisteredProperty(DistributionGaussianItem::P_STD_DEV, factor*distr->getStdDev());
    } else if (const DistributionLogNormal *distr
               = dynamic_cast<const DistributionLogNormal *>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionLogNormalType);
        pdfItem->setRegisteredProperty(DistributionLogNormalItem::P_MEDIAN, factor*distr->getMedian());
        pdfItem->setRegisteredProperty(DistributionLogNormalItem::P_SCALE_PAR,
                                       distr->getScalePar());
    } else if (const DistributionCosine *distr
               = dynamic_cast<const DistributionCosine *>(p_distribution)) {
        pdfItem = item->setGroupProperty(group_name, Constants::DistributionCosineType);
        pdfItem->setRegisteredProperty(DistributionCosineItem::P_MEAN, factor*distr->getMean());
        pdfItem->setRegisteredProperty(DistributionCosineItem::P_SIGMA, factor*distr->getSigma());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setDistribution: -> unknown distribution");
    }
    if (pdfItem) {
        pdfItem->setRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES,
                                       (int)par_distr.getNbrSamples());
        pdfItem->setRegisteredProperty(DistributionItem::P_SIGMA_FACTOR,
                                       par_distr.getSigmaFactor());
    }
}
