// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/TransformationView.h
//! @brief     Defines class TransformationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMATIONVIEW_H
#define TRANSFORMATIONVIEW_H


#include "ConnectableView.h"

class TransformationView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::TRANSFORMATION };

    TransformationView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};

#endif // TRANSFORMATIONVIEW_H
