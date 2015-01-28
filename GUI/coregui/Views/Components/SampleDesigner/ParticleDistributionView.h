// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/ParticleDistributionView.h
//! @brief     Defines class ParticleDistributionView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONVIEW_H
#define PARTICLEDISTRIBUTIONVIEW_H

#include "ConnectableView.h"

//! Class representing view of distributed particle item
class BA_CORE_API_ ParticleDistributionView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::PARTICLE };

    ParticleDistributionView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void addView(IView *childView, int row = 0);

};


#endif

