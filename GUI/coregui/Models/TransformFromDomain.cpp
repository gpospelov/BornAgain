#include "TransformFromDomain.h"
#include "ParameterizedItem.h"
#include "InterferenceFunctions.h"
#include "ParaCrystalItems.h"
#include "FTDistributions.h"
#include "FTDistributionItems.h"
#include "LatticeTypeItems.h"
#include "Numeric.h"
#include "Units.h"
#include "GUIHelpers.h"
#include <QString>
#include <QDebug>
#include <vector>


void TransformFromDomain::setItemFromSample(ParameterizedItem *item, const InterferenceFunction2DParaCrystal *sample)
{

    ParameterizedItem *latticeTypeItem(0);
    if( TransformFromDomain::isSquareLattice(sample)) {
        latticeTypeItem = item->setGroupProperty(InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE, "Square");
        latticeTypeItem->setRegisteredProperty(SquareLatticeTypeItem::P_LATTICE_LENGTH, sample->getLatticeLengths()[0]);
    }
    else if( TransformFromDomain::isHexagonalLattice(sample)) {
        latticeTypeItem = item->setGroupProperty(InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE, "Hexagonal");
        latticeTypeItem->setRegisteredProperty(HexagonalLatticeTypeItem::P_LATTICE_LENGTH, sample->getLatticeLengths()[0]);
    }
    else {
        latticeTypeItem = item->setGroupProperty(InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE, "Basic");
        latticeTypeItem->setRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH1, sample->getLatticeLengths()[0]);
        latticeTypeItem->setRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH2, sample->getLatticeLengths()[1]);
        latticeTypeItem->setRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_ANGLE, Units::rad2deg(sample->getAlphaLattice()));
    }

    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE, Units::rad2deg(sample->getLatticeOrientation()));
    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH, sample->getDampingLength());
    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1, sample->getDomainSizes()[0]);
    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2, sample->getDomainSizes()[1]);
    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, sample->getIntegrationOverXi());

    std::vector<const IFTDistribution2D *> pdfs = sample->getPropabilityDistributions();

    QStringList group_names;
    group_names << InterferenceFunction2DParaCrystalItem::P_PDF1 << InterferenceFunction2DParaCrystalItem::P_PDF2;

    for(size_t i=0; i<pdfs.size(); ++i) {
        qDebug() << "    group_name" << group_names[i];
        if(const FTDistribution2DCauchy *pdf = dynamic_cast<const FTDistribution2DCauchy *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i], "Cauchy 2D");
            pdfItem->setRegisteredProperty(FTDistribution2DCauchyItem::P_CORR_LENGTH_X, pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(FTDistribution2DCauchyItem::P_CORR_LENGTH_Y, pdf->getCoherenceLengthY());
        }
        else if(const FTDistribution2DGauss *pdf = dynamic_cast<const FTDistribution2DGauss *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i], "Gauss 2D");
            pdfItem->setRegisteredProperty(FTDistribution2DGaussItem::P_CORR_LENGTH_X, pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(FTDistribution2DGaussItem::P_CORR_LENGTH_Y, pdf->getCoherenceLengthY());
        }
        else if(const FTDistribution2DVoigt *pdf = dynamic_cast<const FTDistribution2DVoigt *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->setGroupProperty(group_names[i], "Gauss 2D");
            pdfItem->setRegisteredProperty(FTDistribution2DVoigtItem::P_CORR_LENGTH_X, pdf->getCoherenceLengthX());
            pdfItem->setRegisteredProperty(FTDistribution2DVoigtItem::P_CORR_LENGTH_Y, pdf->getCoherenceLengthY());
            pdfItem->setRegisteredProperty(FTDistribution2DVoigtItem::P_ETA, pdf->getEta());
        }
        else {
            throw GUIHelpers::Error("TransformFromDomain::setItemFromSample(ParameterizedItem *item, const InterferenceFunction2DParaCrystal *sample) -> Error");
        }

    }
}


bool TransformFromDomain::isSquareLattice(const InterferenceFunction2DParaCrystal *sample)
{
    std::vector<double> lengths = sample->getLatticeLengths();
    double angle = sample->getAlphaLattice();
    if(lengths[0] == lengths[1] && Numeric::areAlmostEqual(angle, M_PI/2.0)) return true;
    return false;
}


bool TransformFromDomain::isHexagonalLattice(const InterferenceFunction2DParaCrystal *sample)
{
    std::vector<double> lengths = sample->getLatticeLengths();
    double angle = sample->getAlphaLattice();
    if(lengths[0] == lengths[1] && Numeric::areAlmostEqual(angle, 2*M_PI/3.0)) return true;
    return false;
}
