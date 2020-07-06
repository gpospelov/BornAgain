// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleDistributionView.h
//! @brief     Defines class ParticleDistributionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONVIEW_H
#define PARTICLEDISTRIBUTIONVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"

//! Class representing view of distributed particle item
class BA_CORE_API_ ParticleDistributionView : public ConnectableView
{
    Q_OBJECT

public:
    ParticleDistributionView(QGraphicsItem* parent = 0);

    int type() const { return ViewTypes::PARTICLE; }

    void addView(IView* childView, int row = 0);
};

#endif // PARTICLEDISTRIBUTIONVIEW_H
