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
    IInterferenceFunction *result(0);

    if(item.modelType() == "InterferenceFunction1DParaCrystal") {
        result = new InterferenceFunction1DParaCrystal(
                    item.property("PeakDistance").toDouble(),
                    item.property("Width").toDouble(),
                    item.property("CorrLength").toDouble()
                    );
    }

    return result;
}


