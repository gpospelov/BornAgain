#include "DesignerScene.h"
#include "LayerView.h"
#include "LayerView.h"
#include "InterfaceView.h"
#include "DesignerWidgetFactory.h"
#include "MultiLayerView.h"
#include "DesignerMimeData.h"
#include "DesignerHelper.h"
#include "LayerDockView.h"

#include <QGraphicsSceneDragDropEvent>

DesignerScene::DesignerScene(QObject *parent)
    : IDesignerScene(parent)
    , m_xmin(-300)
    , m_xmax(300)
    , m_ymin(-100)
    , m_ymax(500)
    , m_widgetFactory(new DesignerWidgetFactory())
{
    setSceneRect(QRectF(-300, -100, 600, 600));
    setBackgroundBrush(DesignerHelper::getSceneBackground());
    //setAcceptDrops(true);

    //setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    createLayerDock();

}


DesignerScene::~DesignerScene()
{
    delete m_widgetFactory;
}

// create layer dock which will hold Layer and MultiLayer objects
void DesignerScene::createLayerDock()
{
    MultiLayerView *ml = new MultiLayerView();
    ml->setColor(Qt::lightGray);
    ml->allowDropType(QString("MultiLayerX"));
    ml->addLayer(new LayerView());
    ml->addLayer(new LayerView());
    ml->setToolTip(QString("LayerDock"));
    ml->setFlag(QGraphicsItem::ItemIsSelectable, false);
    ml->setPos(-ml->rect().width()/2, 100.0);
    addItem(ml);
}


//void DesignerScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
//{
//    std::cout << "DesignerScene::dragEnterEvent() ->" << std::endl;
//        event->acceptProposedAction();
//}


//void DesignerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
//{
//    event->acceptProposedAction();
//    std::cout << "DesignerScene::dragMoveEvent() -> " << event->pos().x() << " " << event->pos().y() << std::endl;
//}


//void DesignerScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
//{
//    std::cout << "DesignerScene::dragLeaveEvent() ->" << std::endl;
//        event->acceptProposedAction();
//}


//void DesignerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
//{
//    std::cout << "DesignerScene::dropEvent() -> " << std::endl;
//        const DesignerMimeData *mimeData = checkDragEvent(event);
//        if (mimeData) {
//            std::cout << "SampleEditorScene::dropEvent() -> yes " << mimeData->getClassName().toStdString() << std::endl;

//            ISampleView *view = m_widgetFactory->create( mimeData->getClassName() );
//            addItem(view);
//            view->setPos(event->scenePos().x()-view->boundingRect().width()/2, event->scenePos().y()-view->boundingRect().height()/2);
//        }
//}


//void DesignerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    std::cout << "DesignerScene::mouseMoveEvent() -> " << event->scenePos().x() << " " << event->scenePos().y() << std::endl;
//    QGraphicsScene::mouseMoveEvent(event);
//}


//const DesignerMimeData *DesignerScene::checkDragEvent(QGraphicsSceneDragDropEvent * event)
//{
//    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
//    if (!mimeData) {
//        event->ignore();
//        return 0;
//    }

//    if(mimeData->hasFormat("bornagain/widget") ) {
//        std::cout << "DesignerScene::checkDragEvent() yes" << std::endl;
//        event->setAccepted(true);
//    } else {
//        std::cout << "DesignerScene::checkDragEvent() no" << std::endl;
//        event->setAccepted(false);
//    }

//    return mimeData;
//}


