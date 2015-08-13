#ifndef MASKEDITOR_H
#define MASKEDITOR_H

class MaskGraphicsView;
class MaskGraphicsScene;
class GraphicsProxyWidget;
class MaskModel;
class MaskToolBar;
class QListView;
class QVBoxLayout;
class QAction;

class MaskEditor : public QWidget
{
    Q_OBJECT
public:
    MaskEditor(QWidget *parent = 0);

    virtual ~MaskEditor()
    {
    }

    //! set Model
    //! param mask model that caries model for masking
    void setModel(MaskModel *maskModel);

private slots:

    //! creates a rectangle on button press event
    void rectangleButtonPressed();

    //! creates a ellipse on button press event
    void ellipseButtonPressed();

    //! creates a polygon on button press event
    void polygonButtonPressed();

    //! switch on pan mode
    void panMode(bool active);

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

    //!change back to selecton mode if item is drawn
    void onItemIsDrawn();

private:
    MaskGraphicsScene *m_scene; //!< scene contains all items
    MaskGraphicsView *m_view; //!< view renders all items and show them item in the scene on display
    GraphicsProxyWidget *m_proxyWidget; //!< color map (detector)
    QListView *m_listView;              //!< list wiht currently created items as a list
    MaskToolBar *m_toolBar;             //!< tool bar
    QAction *m_deleteAction;            //!< delete action for the list view
    void init_connections(); //!< initialie all connections between scene, view and toolbar

signals:
    //! emittes this signal to toolbar if item is drawn
    void itemIsDrawn();

    //! signal is emitted when someone want to delete item
    void deleteSelectedItems();

protected:
    //! event that manages key press events
    void keyPressEvent(QKeyEvent *event);
};

#endif
