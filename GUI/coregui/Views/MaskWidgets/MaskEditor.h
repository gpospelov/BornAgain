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

    virtual ~MaskEditor() {}

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
    MaskGraphicsScene *m_scene;
    MaskGraphicsView *m_view;
    GraphicsProxyWidget *m_proxyWidget;
    QListView *m_listView;
    MaskToolBar *m_toolBar;
    QAction *m_deleteAction;
    void init_connections();

signals:
    void itemIsDrawn();
    void deleteSelectedItems();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif
