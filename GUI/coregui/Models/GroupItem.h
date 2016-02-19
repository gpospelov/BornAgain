// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.h
//! @brief     Defines class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GROUPITEM_H
#define GROUPITEM_H

#include "ParameterizedItem.h"
#include "GroupProperty.h"

class BA_CORE_API_ GroupItem : public ParameterizedItem
{
    Q_OBJECT
public:
    GroupItem();
    void setGroup(GroupProperty_t group);
    GroupProperty_t group();
private:
    GroupProperty_t m_group;
};

#endif

