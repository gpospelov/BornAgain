// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.cpp
//! @brief     Implements RealSpaceBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "SessionItem.h"
#include <ba3d/model/layer.h>

static ba3d::flt const sz = 100; // half sz

void RealSpaceBuilder::populate(RealSpaceModel* model, const SessionItem& item)
{
    if(item.modelType() != Constants::MultiLayerType)
        return;

    model->defEye = ba3d::xyz(-10, -140, 20);
    model->defCtr = ba3d::xyz(0, 0, -30);
    model->defUp  = ba3d::xyz::_z;

    auto layer = [&](int z1, int z2, QColor color) {
      ba3d::flt s2 = sz /2;
      auto l = new ba3d::Layer(ba3d::dxyz(ba3d::dr(-s2,+s2), ba3d::dr(-s2,+s2), ba3d::dr(z1, z2)));
      color.setAlphaF(.3);
      l->color = color;

      model->addBlend(l);
    };

    layer(  0, -10, Qt::blue);
    layer(-10, -30, Qt::green);
    layer(-30, -45, Qt::red);
    layer(-45, -55, Qt::gray);
}
