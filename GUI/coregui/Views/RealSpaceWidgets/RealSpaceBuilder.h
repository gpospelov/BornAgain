// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h
//! @brief     Defines RealSpaceBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACEBUILDER_H
#define REALSPACEBUILDER_H

#include "WinDllMacros.h"
#include <QVector3D>

class SessionItem;
class RealSpaceModel;
class Shape3D;

namespace RealSpaceBuilder
{

BA_CORE_API_ void populate(RealSpaceModel* model, const SessionItem& item);

BA_CORE_API_ void populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                                     const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                                const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                                 const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateParticle(RealSpaceModel* model, const SessionItem& particleItem,
                                   const QVector3D& origin = QVector3D());
}

#endif // REALSPACEBUILDER_H
