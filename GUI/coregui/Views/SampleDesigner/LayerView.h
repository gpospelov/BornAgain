// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/LayerView.h
//! @brief     Declares class LayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include "ILayerView.h"

//! Class that represents view of Layer
class BA_CORE_API_ LayerView : public ILayerView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::LAYER };

    LayerView(QGraphicsItem *parent = 0);
    virtual ~LayerView() { }

    virtual int type() const { return TYPE; }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void addView(IView *childView, int row = 0); // to add ParticleLayout
};

#endif // LAYERVIEW_H
