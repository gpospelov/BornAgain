// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/ColorMapSceneAdaptor.h
//! @brief     Defines class ColorMapSceneAdaptor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPSCENEADAPTOR_H
#define COLORMAPSCENEADAPTOR_H

#include "ISceneAdaptor.h"

class ColorMapPlot;

//! Performs conversion of MaskItems coordinates between ColorMapPlot and GraphicsScene

class ColorMapSceneAdaptor : public ISceneAdaptor
{
    Q_OBJECT

public:
    ColorMapSceneAdaptor();

    qreal toSceneX(qreal mask_x) const;
    qreal toSceneY(qreal mask_y) const;
    qreal fromSceneX(qreal scene_x) const;
    qreal fromSceneY(qreal scene_y) const;

    void setColorMapPlot(ColorMapPlot *plot);

    bool eventFilter(QObject *object, QEvent *event);

    //! returns ColorMapPlot axes rectangle (at current zoom level) in scene coordinates
    const QRectF& getViewportRectangle() const;

private:
    ColorMapPlot *m_plot;
};


#endif
