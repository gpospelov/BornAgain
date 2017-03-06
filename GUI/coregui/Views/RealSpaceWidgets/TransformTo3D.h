// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.h
//! @brief     Defines namespace TransformTo3D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMTO3D_H
#define TRANSFORMTO3D_H

#include "WinDllMacros.h"
#include <ba3d/model/layer.h>
#include <ba3d/model/particles.h>
#include <Vectors3D.h>
#include <memory>

class SessionItem;

//! Collection of utility functions to build 3D objects from session items.

namespace TransformTo3D
{

BA_CORE_API_
std::unique_ptr<ba3d::Layer> createLayer(const SessionItem& layerItem,
                                         const QVector3D& origin = QVector3D());

BA_CORE_API_
std::unique_ptr<ba3d::particle::Particle> createParticle(const SessionItem& particleItem);

}

#endif
