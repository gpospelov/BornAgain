#include "TransformFromDomain.h"
#include "ParameterizedItem.h"
#include "InterferenceFunctions.h"
#include "ParaCrystalItems.h"
#include "FTDistributions.h"
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
        latticeTypeItem = item->registerGroupProperty(InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE, "Square");
        latticeTypeItem->setProperty("Lattice_length", sample->getLatticeLengths()[0]);
    } else if( TransformFromDomain::isHexagonalLattice(sample)) {
        latticeTypeItem = item->registerGroupProperty(InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE, "Hexagonal");
        latticeTypeItem->setProperty("Lattice_length", sample->getLatticeLengths()[0]);
    } else {
        latticeTypeItem = item->registerGroupProperty(InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE, "Basic");
        latticeTypeItem->setProperty("Lattice_length_1", sample->getLatticeLengths()[0]);
        latticeTypeItem->setProperty("Lattice_length_2", sample->getLatticeLengths()[1]);
        latticeTypeItem->setProperty("Lattice_angle", Units::rad2deg(sample->getAlphaLattice()));
    }

    item->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE, Units::rad2deg(sample->getLatticeOrientation()));
    item->setProperty("Damping_length", sample->getDampingLength());
    item->setProperty("Domain_size_1", sample->getDomainSizes()[0]);
    item->setProperty("Domain_size_2", sample->getDomainSizes()[1]);
    item->setProperty("IntegrationOverXi", sample->getIntegrationOverXi());

    std::vector<const IFTDistribution2D *> pdfs = sample->getPropabilityDistributions();
    for(size_t i=0; i<pdfs.size(); ++i) {
        QString group_name = QString("PDF #%1").arg(QString::number(i+1));
        qDebug() << "    group_name" << group_name;
        if(const FTDistribution2DCauchy *pdf = dynamic_cast<const FTDistribution2DCauchy *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->registerGroupProperty(group_name.toAscii().data(), "Cauchy 2D");
            pdfItem->setProperty("Corr_length_x", pdf->getCoherenceLengthX());
            pdfItem->setProperty("Corr_length_y", pdf->getCoherenceLengthY());
        }
        else if(const FTDistribution2DGauss *pdf = dynamic_cast<const FTDistribution2DGauss *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->registerGroupProperty(group_name.toAscii().data(), "Gauss 2D");
            pdfItem->setProperty("Corr_length_x", pdf->getCoherenceLengthX());
            pdfItem->setProperty("Corr_length_y", pdf->getCoherenceLengthY());
        }
        else if(const FTDistribution2DVoigt *pdf = dynamic_cast<const FTDistribution2DVoigt *>(pdfs[i])) {
            ParameterizedItem *pdfItem = item->registerGroupProperty(group_name.toAscii().data(), "Gauss 2D");
            pdfItem->setProperty("Corr_length_x", pdf->getCoherenceLengthX());
            pdfItem->setProperty("Corr_length_y", pdf->getCoherenceLengthY());
            pdfItem->setProperty("Eta", pdf->getEta());
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
