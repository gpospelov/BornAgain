#ifndef DESIGNERSCENE_H
#define DESIGNERSCENE_H

#include <QGraphicsScene>


class QGraphicsSceneDragDropEvent;
class DesignerMimeData;
class DesignerWidgetFactory;

//! base class for sample designer scene
class IDesignerScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit IDesignerScene(QObject *parent = 0) : QGraphicsScene(parent){}
    virtual ~IDesignerScene(){}


};


//! sample designer scene
class DesignerScene : public IDesignerScene
{
    Q_OBJECT

public:
    explicit DesignerScene(QObject *parent = 0);
    virtual ~DesignerScene();



protected:
//    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);

    int m_xmin;
    int m_xmax;
    int m_ymin;
    int m_ymax;

    DesignerWidgetFactory *m_widgetFactory;

};

#endif // DESIGNERSCENE_H
