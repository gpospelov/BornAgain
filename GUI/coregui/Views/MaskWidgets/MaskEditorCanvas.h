// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorCanvas.h
//! @brief     Defines class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORCANVAS_H
#define MASKEDITORCANVAS_H

#include <QWidget>

class MaskGraphicsScene;
class MaskGraphicsView;
class MaskGraphicsProxy;

//! Painting widget for MaskEditor

class MaskEditorCanvas : public QWidget
{
    Q_OBJECT
public:
    MaskEditorCanvas(QWidget *parent = 0);


private:
    void init_widget();

    MaskGraphicsScene *m_scene;
    MaskGraphicsView *m_view;
    MaskGraphicsProxy *m_graphicsProxy;
};


#endif
