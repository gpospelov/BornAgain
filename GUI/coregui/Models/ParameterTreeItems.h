// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterTreeItems.h
//! @brief     Defines classes for ParameterTreeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERTREEITEMS_H
#define PARAMETERTREEITEMS_H

#include "SessionItem.h"

class BA_CORE_API_ ParameterLabelItem : public SessionItem
{
public:
    ParameterLabelItem();
};

class BA_CORE_API_ ParameterItem : public SessionItem
{
public:
    static const QString P_LINK;
    static const QString P_BACKUP;
    ParameterItem();
    void propagateValueLink(bool backup = false);
    SessionItem *getLinkedItem();
};

#endif
