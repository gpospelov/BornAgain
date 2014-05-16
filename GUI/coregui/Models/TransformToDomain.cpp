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
#include "FTDistributionItems.h"
#include <QDebug>

#include <boost/scoped_ptr.hpp>


IMaterial *TransformToDomain::createDomainMaterial(const ParameterizedItem &item)
{
    QVariant v = item.property("Material");
    if( !v.isValid() )
        throw GUIHelpers::Error("TransformToDomain::createDomainMaterial() -> No material property");

    MaterialProperty materialProperty = v.value<MaterialProperty>();
    return MaterialUtils::createDomainMaterial(materialProperty.getName());
}


MultiLayer *TransformToDomain::createMultiLayer(const ParameterizedItem &item)
{
    MultiLayer *result = new MultiLayer();
    bool ok = false;
    double cross_corr_length =
            item.property("Cross Correlation Length").toDouble(&ok);
    if (ok) {
        if(cross_corr_length>0) result->setCrossCorrLength(cross_corr_length);
    }
    result->setName(item.itemName().toAscii().data());
    return result;
}


Layer *TransformToDomain::createLayer(const ParameterizedItem &item)
{
    Layer *result = new Layer();
    bool ok = false;
    double thickness =
            item.property("Thickness").toDouble(&ok);
    if (ok) {
        result->setThickness(thickness);
    }

    boost::scoped_ptr<IMaterial> material(createDomainMaterial(item));
    result->setMaterial(*material.get());
    result->setName(item.itemName().toAscii().data());

    return result;
}


ParticleLayout *TransformToDomain::createParticleLayout(
        const ParameterizedItem &item)
{
    (void)item;
    ParticleLayout *result = new ParticleLayout();
    return result;
}


Particle *TransformToDomain::createParticle(const ParameterizedItem &item, double &depth, double &abundance)
{
    boost::scoped_ptr<IMaterial> material(createDomainMaterial(item));
    Particle *result = new Particle(*material);
    Q_ASSERT(item.property("Depth").isValid());
    Q_ASSERT(item.property("Abundance").isValid());
    depth = item.property("Depth").toDouble();
    abundance = item.property("Abundance").toDouble();

    ParameterizedItem *ffItem = item.getSubItems()["Form Factor"];
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


IInterferenceFunction *TransformToDomain::createInterferenceFunction(const ParameterizedItem &item)
{
    if(item.modelType() == "InterferenceFunction1DParaCrystal") {
        InterferenceFunction1DParaCrystal *result = new InterferenceFunction1DParaCrystal(
                    item.property("PeakDistance").toDouble(),
                    item.property("Width").toDouble(),
                    item.property("CorrLength").toDouble()
                    );
        return result;
    }
    else if(item.modelType() == "InterferenceFunction2DParaCrystal") {

        ParameterizedItem *latticeItem = item.getSubItems()["Lattice type"];
        Q_ASSERT(latticeItem);

        double length_1(0), length_2(0), alpha_lattice(0.0);
        if(latticeItem->modelType() == "BasicLatticeType") {
            length_1 = latticeItem->property("Lattice_length_1").toDouble();
            length_2 = latticeItem->property("Lattice_length_2").toDouble();
            alpha_lattice = Units::deg2rad(item.property("Lattice_angle").toDouble());
        }
        else if(latticeItem->modelType() == "SquareLatticeType") {
            length_1 = latticeItem->property("Lattice_length").toDouble();
            length_2 = length_1;
            alpha_lattice = M_PI/2.0;
        }
        else if(latticeItem->modelType() == "HexagonalLatticeType") {
            length_1 = latticeItem->property("Lattice_length").toDouble();
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
                    Units::deg2rad(item.property("Rotation_angle").toDouble()),
                    item.property("Damping_length").toDouble());
        result->setDomainSizes(
                    item.property("Domain_size_1").toDouble(),
                    item.property("Domain_size_2").toDouble()
                    );

        result->setIntegrationOverXi(item.property("IntegrationOverXi").toBool());

        ParameterizedItem *pdf1Item = item.getSubItems()["PDF #1"];
        Q_ASSERT(pdf1Item);
        boost::scoped_ptr<IFTDistribution2D> pdf1(dynamic_cast<FTDistribution2DItem *>(pdf1Item)->createFTDistribution());
        Q_ASSERT(pdf1.get());

        ParameterizedItem *pdf2Item = item.getSubItems()["PDF #2"];
        Q_ASSERT(pdf2Item);
        boost::scoped_ptr<IFTDistribution2D> pdf2(dynamic_cast<FTDistribution2DItem *>(pdf2Item)->createFTDistribution());
        Q_ASSERT(pdf2.get());

        result->setProbabilityDistributions(*pdf1, *pdf2);
        return result;
    }

    return 0;
}



