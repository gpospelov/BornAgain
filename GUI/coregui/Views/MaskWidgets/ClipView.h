// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/ClipView.h
//! @brief     Defines ClipView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CLIPVIEW_H
#define CLIPVIEW_H

#include "IMaskView.h"
#include "SizeHandleElement.h"
#include <QMap>

//! The ClipView class hides all masks on scene if they are going outside of ColorMapPlot
//! viewport. It is just transparent rectangle which covers ColorMapPlot on graphics scene with
//! the size matching curent axes zoom level. All MaskViews are added to it as children.

class BA_CORE_API_ ClipView : public IMaskView
{
    Q_OBJECT
public:
    ClipView();

public slots:
    void update_view();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif
