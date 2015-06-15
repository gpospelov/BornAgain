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
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "DistributionEditor.h"
#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainterPath>

#ifndef TESTVIEW_H
#define TESTVIEW_H

//class ParameterizedItem;
//class AwesomePropertyEditor;
class GraphicsView;
class GraphicsScene;

class TestView : public QWidget
{
    Q_OBJECT
public:
    TestView(QWidget *parent = 0);

    // enum Activity {SELECT, CREATE_POLYGON, NONE}

    virtual ~TestView()
    {
    }
private slots:
    //! creates a rectangle on button press event
    void rectangleButtonPressed();
    //! creates a ellipse on button press event
    void ellipseButtonPressed();
    //! creates a polygon on button press event
    void polygonButtonPressed();
    //! switch on/off pan mode
    void panMode();
    //! delete selected item
    void deleteSelectedItem();
    //! bring current selected item to the top
    void bringToFrontClicked();
    //! send current selected item to the bottom
    void sendToBackClicked();

private:
    GraphicsScene *m_scene;
    GraphicsView *m_view;
    QPushButton *m_rectangleButton;
    QPushButton*m_ellipseButton;
    QPushButton *m_polygonButton;
    QPushButton *m_panButton;
};

#endif
