// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/TransformationView.h
//! @brief     Defines class TransformationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
