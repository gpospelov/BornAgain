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
#include "ParticleItem.h"
#include "VectorItem.h"
#include "RotationItems.h"
#include "BornAgainNamespace.h"


PositionTranslator::PositionTranslator()
{
}

PositionTranslator *PositionTranslator::clone() const
{
    return new PositionTranslator();
}

QStringList PositionTranslator::split(const QString &par_name) const
{
    QStringList result;
    auto position_name = translate(par_name);
    if (!position_name.empty()) {
        result << par_name;
    }
    return result;
}

std::string PositionTranslator::translate(const QString &name) const
{
    auto name_list = name.split(QString("/"));
    if (name_list.size() > 2) return "";
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
    return "";
}

RotationTranslator::RotationTranslator()
{
}

RotationTranslator *RotationTranslator::clone() const
{
    return new RotationTranslator();
}

QStringList RotationTranslator::split(const QString &par_name) const
{
    QStringList result;
    auto rotation_name = translate(par_name);
    if (!rotation_name.empty()) {
        result << par_name;
    }
    return result;
}

std::string RotationTranslator::translate(const QString &name) const
{
    auto name_list = name.split(QString("/"));
    if (name_list.size() > 3) return "";
    if (name_list.size() == 3 && name_list[0] == Constants::TransformationType) {
        if (name_list[1] == Constants::XRotationType) {
            return BornAgain::XRotationType + std::string("/") + BornAgain::Angle;
        }
        if (name_list[1] == Constants::YRotationType) {
            return BornAgain::YRotationType + std::string("/") + BornAgain::Angle;
        }
        if (name_list[1] == Constants::ZRotationType) {
            return BornAgain::ZRotationType + std::string("/") + BornAgain::Angle;
        }
        if (name_list[1] == Constants::EulerRotationType) {
            if (name_list[2] == EulerRotationItem::P_ALPHA) {
                return BornAgain::EulerRotationType + std::string("/") + BornAgain::Alpha;
            } else if (name_list[2] == EulerRotationItem::P_BETA) {
                return BornAgain::EulerRotationType + std::string("/") + BornAgain::Beta;
            } else if (name_list[2] == EulerRotationItem::P_GAMMA) {
                return BornAgain::EulerRotationType + std::string("/") + BornAgain::Gamma;
            }
        }
    }
    return "";
}
