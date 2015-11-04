// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsView.h
//! @brief     Defines class MaskGraphicsView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKGRAPHICSVIEW_H
#define MASKGRAPHICSVIEW_H

#include <QGraphicsView>

class QWheelEvent;
class MaskGraphicsProxy;

//! Graphics view for MaskEditorCanvas

class MaskGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MaskGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    QSize sizeHint() const { return QSize(512, 512); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    void setColorMapProxy(MaskGraphicsProxy *colorMapProxy);

protected:
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    bool controlButtonIsPressed(QWheelEvent *event);

    MaskGraphicsProxy *m_colorMapProxy;
};


#endif
