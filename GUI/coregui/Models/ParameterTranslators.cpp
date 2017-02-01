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
#include "RotationItems.h"
#include "VectorItem.h"
#include "InterferenceFunctionItems.h"
#include "Lattice2DItems.h"
#include "GUIHelpers.h"
#include "MultiLayerItem.h"
#include <QDebug>

namespace {
const QStringList expectedRoughnessPars = QStringList() << QString::fromStdString(BornAgain::Sigma)
    << QString::fromStdString(BornAgain::Hurst)
    << QString::fromStdString(BornAgain::CorrelationLength);
}

QStringList IParameterTranslator::split(const QString &par_name) const
{
    QStringList result;

    std::string translated_name = translate(par_name);
    if (!translated_name.empty())
        result << par_name;

    return result;
}

std::string PositionTranslator::translate(const QString& name) const
{
    QStringList name_list = name.split("/");
    if (name_list.size() > 2) return {};
    if (name_list.size() > 1 && name_list[0] == ParticleItem::P_POSITION) {
        if (name_list[1] == VectorItem::P_X) {
            return BornAgain::PositionX;
        }
        if (name_list[1] == VectorItem::P_Y) {
            return BornAgain::PositionY;
        }
        if (name_list[1] == VectorItem::P_Z) {
            return BornAgain::PositionZ;
        }
    }
    return {};
}

std::string RotationTranslator::translate(const QString& name) const
{
    QStringList name_list = name.split("/");
    std::string separator {"/"};
    if (name_list.size() > 3) return {};
    if (name_list.size() == 3 && name_list[0] == Constants::TransformationType) {
        if (name_list[1] == Constants::XRotationType) {
            return BornAgain::XRotationType + separator + BornAgain::Angle;
        }
        if (name_list[1] == Constants::YRotationType) {
            return BornAgain::YRotationType + separator + BornAgain::Angle;
        }
        if (name_list[1] == Constants::ZRotationType) {
            return BornAgain::ZRotationType + separator + BornAgain::Angle;
        }
        if (name_list[1] == Constants::EulerRotationType) {
            if (name_list[2] == EulerRotationItem::P_ALPHA) {
                return BornAgain::EulerRotationType + separator + BornAgain::Alpha;
            } else if (name_list[2] == EulerRotationItem::P_BETA) {
                return BornAgain::EulerRotationType + separator + BornAgain::Beta;
            } else if (name_list[2] == EulerRotationItem::P_GAMMA) {
                return BornAgain::EulerRotationType + separator + BornAgain::Gamma;
            }
        }
    }
    return {};
}

QStringList NewPositionTranslator::translate(const QStringList& list) const
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

QStringList NewRotationTranslator::translate(const QStringList& list) const
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
