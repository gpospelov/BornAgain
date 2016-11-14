// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskGraphicsView.h
//! @brief     Defines class MaskGraphicsView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKGRAPHICSVIEW_H
#define MASKGRAPHICSVIEW_H

#include "MaskEditorFlags.h"
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

public slots:
    void onResetViewRequest();

    void updateSize(const QSize &newSize);

signals:
    void changeActivityRequest(MaskEditorFlags::Activity);

protected:
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    bool isControlButtonIsPressed(QWheelEvent *event);
    void cancelCurrentDrawing();

    void setZoomValue(double zoom_value);
    void decreazeZoomValue();
    void increazeZoomValue();

    double m_current_zoom_value;
};


#endif // MASKGRAPHICSVIEW_H
