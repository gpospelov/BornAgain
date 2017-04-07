// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTranslators.cpp
//! @brief     Implements subclasses of IParameterTranslator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterTranslators.h"
#include "BornAgainNamespace.h"
#include "ParticleItem.h"
#include "VectorItem.h"
#include "GUIHelpers.h"

namespace {
const QStringList expectedRoughnessPars = QStringList() << QString::fromStdString(BornAgain::Sigma)
    << QString::fromStdString(BornAgain::Hurst)
    << QString::fromStdString(BornAgain::CorrelationLength);
}

QStringList PositionTranslator::translate(const QStringList& list) const
{
    if(list.back() != ParticleItem::P_POSITION)
        return list;

    Q_ASSERT(list.size() == 2);

    QStringList result;
    if (list.front() == VectorItem::P_X) {
        result << QString::fromStdString(BornAgain::PositionX);
    } else if (list.front() == VectorItem::P_Y) {
        result << QString::fromStdString(BornAgain::PositionY);
    } else if (list.front() == VectorItem::P_Z) {
        result << QString::fromStdString(BornAgain::PositionZ);
    } else {
        GUIHelpers::Error("NewPositionTranslator::translate() -> Unexpected list structure");
    }

    return result;
}

QStringList RotationTranslator::translate(const QStringList& list) const
{
    if(list.back() != Constants::TransformationType)
        return list;

    Q_ASSERT(list.size() == 3);
    QStringList result = list;
    result.removeLast();
    return result;
}

QStringList DistributionNoneTranslator::translate(const QStringList& list) const
{
    if(list.back() != Constants::DistributionNoneType)
        return list;

    Q_UNUSED(list);
    return QStringList(); // removing "DistributionNone/Value"
}

//! Converts "/Layer1/LayerBasicRoughness/Sigma" into "/LayerInterface0/LayerBasicRoughness/Sigma"

QStringList RoughnessTranslator::translate(const QStringList& list) const
{
    if (!list.back().contains(Constants::LayerType)
        || !expectedRoughnessPars.contains(list.front()))
        return list;

    QStringList result = list;

    QString layerName = result.takeLast();
    int layerIndex = getLayerIndex(layerName);

    result.push_back(QString::fromStdString(BornAgain::LayerInterfaceType)
                     + QString::number(layerIndex - 1));
    return result;
}

//! Extract layer index from the string "Layer11"

int RoughnessTranslator::getLayerIndex(QString layerName) const
{
    layerName.remove(Constants::LayerType);
    bool ok(true);
    int layerIndex = layerName.toInt(&ok);
    if(!ok)
        throw GUIHelpers::Error("RoughnessTranslator::getLayerIndex() -> Error. Can't parse.");
    return layerIndex;
}
