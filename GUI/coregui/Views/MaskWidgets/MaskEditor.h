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

#ifndef MASKEDITOR_H
#define MASKEDITOR_H

//class ParameterizedItem;
//class AwesomePropertyEditor;
class GraphicsView;
class GraphicsScene;
class GraphicsProxyWidget;
class MaskModel;

class MaskEditor : public QWidget
{
    Q_OBJECT
public:
    MaskEditor(QWidget *parent = 0);
    // FIXME an empty line is necessary before constructor and function
    // FIXME constructor, destructor, empty line, all the rest
    void setModel(MaskModel *maskModel);
    // FIXME it is better to have brackets on the same line {} of destructor
    virtual ~MaskEditor()
    {
    }
    // FIXME there must be an empty line before private, protected etc
private slots:
    //! creates a rectangle on button press event
    void rectangleButtonPressed();
    // FIXME it is better to have an empty line between previous function and comments of next function
    //! creates a ellipse on button press event
    void ellipseButtonPressed();
    //! creates a polygon on button press event
    void polygonButtonPressed();
    //! switch on pan mode
    void panMode();
    //! delete selected item
    void deleteSelectedItem();
    //! bring current selected item to the top
    void bringToFrontClicked();
    //! send current selected item to the bottom
    void sendToBackClicked();
    //! create include item
    void includeClicked();
    //! create exclude item
    void excludeClicked();
    //! change from drawing mode to selection mode
    void changeToSelectionMode();
    //!change from selection mode to drawing mode
    void changeToDrawingMode();

private:
    GraphicsScene *m_scene;
    GraphicsView *m_view;
    // FIXME bad variable name, rename to m_proxyWidget
    GraphicsProxyWidget *m_widget;
    // FIXME this layout is not needed here
    QVBoxLayout *m_buttonLayout;
};

#endif
