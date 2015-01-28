// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/ParticleLayoutView.h
//! @brief     Defines class ParticleLayoutView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTVIEW_H
#define PARTICLELAYOUTVIEW_H

#include "ConnectableView.h"

class BA_CORE_API_ ParticleLayoutView : public ConnectableView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )

public:
    enum { TYPE = DesignerHelper::PARTICLE_LAYOUT };

    ParticleLayoutView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void addView(IView *childView, int row = 0); // to add Particle
};


#endif // PARTICLELAYOUTVIEW_H

