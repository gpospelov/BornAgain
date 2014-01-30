#ifndef DESIGNERSCENE_H
#define DESIGNERSCENE_H

#include <QGraphicsScene>


class QGraphicsSceneDragDropEvent;
class DesignerMimeData;
class DesignerWidgetFactory;
class QGraphicsDropShadowEffect;
class MultiLayerView;

//! base class for sample designer scene
class DesignerSceneInterface : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DesignerSceneInterface(QObject *parent = 0) : QGraphicsScene(parent){}
    virtual ~DesignerSceneInterface(){}


};


//! Sample designer scene. Main class to hold all graphics items (ISampleView objects).
//! Handles drag and drop. Initialises NodeEditor.
//!
//! Belongs to SampleDesigner
class DesignerScene : public DesignerSceneInterface
{
    Q_OBJECT

public:
    explicit DesignerScene(QObject *parent = 0);
    virtual ~DesignerScene(){}

//    MultiLayerView *getTopMultiLayer() { return m_dock; }
    MultiLayerView *getMultiLayerView();
    QList<MultiLayerView *> getMultiLayerViewList();

protected:
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);

    void addItems(const QList<QGraphicsItem *> &items);


private:
    // create some sample to start with non-empty scene
    void createSample();

//    QGraphicsDropShadowEffect *m_shadow_effect;
};

#endif // DESIGNERSCENE_H
