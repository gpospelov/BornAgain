// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ProjectionItems.h
//! @brief     Defines items related to projections over color map.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONITEMS_H
#define PROJECTIONITEMS_H

#include "SessionItem.h"

//! A container to hold ProjectionItems, intended to store projections of color map on X, Y axes.

class BA_CORE_API_  ProjectionContainerItem : public SessionItem
{
public:
    ProjectionContainerItem();
};

//! Projection of a 2D histogram into 1D histogram along X.

class BA_CORE_API_  ProjectionXItem : public SessionItem
{
public:
    ProjectionXItem();
};

//! Projection of a 2D histogram into 1D histogram along Y.

class BA_CORE_API_  ProjectionYItem : public SessionItem
{
public:
    ProjectionYItem();
};

#endif
