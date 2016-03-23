// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ParticleLayoutView.h
//! @brief     Defines class ParticleLayoutView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTVIEW_H
#define PARTICLELAYOUTVIEW_H

#include "ConnectableView.h"

class BA_CORE_API_ ParticleLayoutView : public ConnectableView
{
public:
    enum { TYPE = DesignerHelper::PARTICLE_LAYOUT };

    ParticleLayoutView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void addView(IView *childView, int row = 0); // to add Particle
};

#endif // PARTICLELAYOUTVIEW_H
