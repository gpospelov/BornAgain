#ifndef DESIGNERSCENE_H
#define DESIGNERSCENE_H

#include <QGraphicsScene>


class QGraphicsSceneDragDropEvent;
class DesignerMimeData;
class DesignerWidgetFactory;
class QGraphicsDropShadowEffect;

//! base class for sample designer scene
class DesignerSceneInterface : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DesignerSceneInterface(QObject *parent = 0) : QGraphicsScene(parent){}
    virtual ~DesignerSceneInterface(){}


};


//! sample designer scene
class DesignerScene : public DesignerSceneInterface
{
    Q_OBJECT

public:
    explicit DesignerScene(QObject *parent = 0);
    virtual ~DesignerScene(){}

protected:
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);

private:
    void createSample();
    void createLayerDock();

    int m_xmin;
    int m_xmax;
    int m_ymin;
    int m_ymax;
//    QGraphicsDropShadowEffect *m_shadow_effect;
};

#endif // DESIGNERSCENE_H
