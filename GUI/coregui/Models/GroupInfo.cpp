// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfo.h
//! @brief     Defines class GroupInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GroupInfo.h"
#include "GUIHelpers.h"

GroupInfo::GroupInfo(const QString& groupName, bool is_sorted)
    : m_groupName(groupName), is_sorted(is_sorted)
{
}

void GroupInfo::add(const QString& modelType, const QString& label)
{
    if (groupName().isEmpty())
        throw GUIHelpers::Error("GroupInfo::add() -> Error. Empty group name");

    if (containsType(modelType))
        throw GUIHelpers::Error("GroupInfo::add() -> Error. "
                                "Model type '"  + modelType + "' already exists.");

    m_info.push_back({modelType, label});

    if (is_sorted)
        std::sort(m_info.begin(), m_info.end(),
                  [](TypeAndLabel a, TypeAndLabel b) { return a.m_modelType < b.m_modelType; });
}

void GroupInfo::setDefaultType(const QString& modelType)
{
    if (!containsType(modelType))
        throw GUIHelpers::Error("GroupInfo::add() -> Error. No such type '" + modelType + "'");

    m_defaultType = modelType;
}

QString GroupInfo::groupName() const { return m_groupName; }

bool GroupInfo::containsType(const QString& modelType) const
{
    for (auto& pair : m_info)
        if (modelType == pair.m_modelType)
            return true;

    return false;
}
