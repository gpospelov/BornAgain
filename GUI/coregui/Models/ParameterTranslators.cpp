// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterTranslators.cpp
//! @brief     Implements subclasses of IParameterTranslator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterTranslators.h"
#include "ParticleItem.h"
#include "VectorItem.h"
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
