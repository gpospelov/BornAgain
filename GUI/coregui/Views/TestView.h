// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.h
//! @brief     Defines class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "DistributionEditor.h"
#include <QGraphicsView>
#include <QPainterPath>
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"

#ifndef TESTVIEW_H
#define TESTVIEW_H

//class ParameterizedItem;
//class AwesomePropertyEditor;

class TestView : public QWidget
{
    Q_OBJECT
public:
    TestView(QWidget *parent = 0);
    virtual ~TestView()
    {
    }
private slots:
    //! creates a rectangle on button click event
    void rectangleButtonClicked();
    //! creates a ellipse on button click event
    void ellipseButtonClicked();
    //! creates a polygon on button click event
    void polygonButtonClicked();

private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    Rectangle *m_rectangle;
    Ellipse *m_ellipse;
    Polygon *m_polygon;
};

#endif
