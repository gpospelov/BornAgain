#include "DesignerScene.h"
#include "LayerView.h"
#include "LayerView.h"
#include "InterfaceView.h"
#include "DesignerWidgetFactory.h"
#include "MultiLayerView.h"
#include "DesignerMimeData.h"
#include "DesignerHelper.h"
#include "LayerDockView.h"
#include "NodeEditor.h"
#include "ISampleToScene.h"
#include "SampleBuilderFactory.h"
#include "SamplePrintVisitor.h"
#include "ISampleViewLayoutVisitor.h"


#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsDropShadowEffect>

DesignerScene::DesignerScene(QObject *parent)
    : DesignerSceneInterface(parent)
    , m_xmin(-300)
    , m_xmax(300)
    , m_ymin(-100)
    , m_ymax(500)
    , m_dock(0)
{

    setSceneRect(QRectF(-300, -100, 600, 600));
    setBackgroundBrush(DesignerHelper::getSceneBackground());
    //setAcceptDrops(true);

    //setFlag(QGraphicsItem::ItemSendsGeometryChanges);
//    m_dock = MultiLayerView::createTopMultiLayer();
//    addItem(m_dock);

    NodeEditor *nodeEditor = new NodeEditor(parent);
    nodeEditor->install(this);


    createSample();

}



void DesignerScene::createSample()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs01");

//    SamplePrintVisitor print_visitor;
//    sample->accept(&print_visitor);

    ISampleToScene visitor;
    sample->accept(&visitor);
    QList<QGraphicsItem *> items = visitor.getItems();

    foreach(QGraphicsItem *item, items) {
                std::cout << "item "  << " " << item->type() << std::endl;
                addItem(item);
    }


//    foreach (QGraphicsItem *item, items()) {
//        std::cout << "item "  << " " << item->type() << std::endl;
//    }




    ISampleViewLayoutVisitor layout;
    layout.makeLayout(visitor.getMultiLayerView());

}


void DesignerScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "DesignerScene::dragEnterEvent() ->" << std::endl;
//    event->acceptProposedAction();
//    event->accept();
    QGraphicsScene::dragEnterEvent(event);
}


void DesignerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "DesignerScene::dragMoveEvent() -> " << event->scenePos().x() << " " << event->scenePos().y() << std::endl;
    const DesignerMimeData *mimeData = checkDragEvent(event);
//    if (mimeData) {
//        std::cout << "DesignerScene::dragMoveEvent() ->  yes" << event->scenePos().x() << " " << event->scenePos().y() << std::endl;
//    } else {
//        std::cout << "DesignerScene::dragMoveEvent() ->  no" << event->scenePos().x() << " " << event->scenePos().y() << std::endl;
//        event->acceptProposedAction();
//        QGraphicsScene::dragMoveEvent(event);
//    }
    if(mimeData) {
        if(mimeData->getClassName() == QString("Layer") || mimeData->getClassName() == QString("MultiLayer") ) {
            QGraphicsScene::dragMoveEvent(event);
        }
    }

}


void DesignerScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "DesignerScene::dragLeaveEvent() ->" << std::endl;
        QGraphicsScene::dragLeaveEvent(event);
//        event->acceptProposedAction();
}




void DesignerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "DesignerScene::dropEvent() -> " << std::endl;
    //event->acceptProposedAction();
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        if(mimeData->getClassName() == QString("Layer") || mimeData->getClassName() == QString("MultiLayer") ) {
            QGraphicsScene::dropEvent(event);
        } else {
            ISampleView *view = DesignerWidgetFactory::createView( mimeData->getClassName() );
            addItem(view);

//            QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect;
//            shadow_effect->setBlurRadius(8);
//            shadow_effect->setOffset(2,2);
//            view->setGraphicsEffect(shadow_effect);

            view->setPos(event->scenePos().x()-view->boundingRect().width()/2, event->scenePos().y()-view->boundingRect().height()/2);

        }

        std::cout << "SampleEditorScene::dropEvent() -> yes " << mimeData->getClassName().toStdString() << std::endl;

    }
    //QGraphicsScene::dropEvent(event);
}


void DesignerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    std::cout << "DesignerScene::mouseMoveEvent() -> " << event->scenePos().x() << " " << event->scenePos().y() << std::endl;
    QGraphicsScene::mouseMoveEvent(event);
}



const DesignerMimeData *DesignerScene::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    std::cout << "DesignerScene::checkDragEvent -> "  << std::endl;
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }

    if(mimeData->hasFormat("bornagain/widget") ) {
//            && (mimeData->getClassName() != QString("Layer") )
//         && (mimeData->getClassName() != QString("MultiLayer") ) ) {

        std::cout << "DesignerScene::checkDragEvent -> yes"  << std::endl;
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
    return mimeData;
}



