// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/IntensityDataView.h
//! @brief     Declares IntensityDataView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATDAVIEW_H
#define INTENSITYDATDAVIEW_H

#include "IMaskView.h"
#include "SizeHandleElement.h"
#include <QMap>

//! The IntensityDataView is nothing move than just transparent rectangle to cover axes area
//! of ColorMapPlot inside MaskGraphicsScene. The goal of this rectangle is to hide all MaskViews
//! if they are going outside of ColorMapPlot.
//!
//! The size of the rectangle always matches axes viewport at any zoom level.
//! All MasksViews are added to IntensityDataView as children.

class BA_CORE_API_ IntensityDataView : public IMaskView
{
    Q_OBJECT
public:
    IntensityDataView();

public slots:
    void update_view();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif