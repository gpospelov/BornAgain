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
#include "ISampleViewAligner.h"


#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsDropShadowEffect>

DesignerScene::DesignerScene(QObject *parent)
    : DesignerSceneInterface(parent)
{

    setSceneRect(QRectF(-500, -200, 800, 800));
    setBackgroundBrush(DesignerHelper::getSceneBackground());
    //setAcceptDrops(true);

    //setFlag(QGraphicsItem::ItemSendsGeometryChanges);
//    m_dock = MultiLayerView::createTopMultiLayer();
//    addItem(m_dock);

    NodeEditor *nodeEditor = new NodeEditor(parent);
    nodeEditor->install(this);


    createSample();

}


MultiLayerView *DesignerScene::getMultiLayerView()
{
    QList<MultiLayerView *> multiLayers = getMultiLayerViewList();
    return (multiLayers.size() ? multiLayers.at(0) : 0);
}


QList<MultiLayerView *> DesignerScene::getMultiLayerViewList()
{
    QList<MultiLayerView *> result;
    foreach(QGraphicsItem *item, items()) {
        if(item->type() == MultiLayerView::Type) {
            MultiLayerView *view = dynamic_cast<MultiLayerView *>(item);
            Q_ASSERT(view);
            result.append(view);
        }
    }
    return result;
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
        addItem(item);
    }

    ISampleViewAligner layout;
    layout.makeAlign(visitor.getMultiLayerView());
}


void DesignerScene::addItems(const QList<QGraphicsItem *> &items)
{
    foreach(QGraphicsItem *item, items) {
                std::cout << "item "  << " " << item->type() << std::endl;
                addItem(item);
    }
    //            QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect;
    //            shadow_effect->setBlurRadius(8);
    //            shadow_effect->setOffset(2,2);
    //            view->setGraphicsEffect(shadow_effect);


//    view->setPos(event->scenePos().x()-view->boundingRect().width()/2, event->scenePos().y()-view->boundingRect().height()/2);

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
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        if(mimeData->getClassName() == QString("Layer") || mimeData->getClassName() == QString("MultiLayer") ) {
            QGraphicsScene::dropEvent(event);
        } else {
            //ISampleView *view = DesignerWidgetFactory::createViews( mimeData->getClassName() );
//            addItems( DesignerWidgetFactory::createViews(mimeData->getClassName()) );

            // TODO - refactor this together with DesignerWidgetFactory: how to create single View or Whole bunch of views
            QList<QGraphicsItem *> items = DesignerWidgetFactory::createViews(mimeData->getClassName());
            if(items.size()) {
                foreach(QGraphicsItem *view, items) {
                    std::cout << "item "  << " " << view->type() << std::endl;
                    addItem(view);
                    view->setPos(event->scenePos().x()-view->boundingRect().width()/2, event->scenePos().y()-view->boundingRect().height()/2);
                }
            } else {
                if(items.empty()) {
                    SampleBuilderFactory factory;
                    ISample *sample(0);
                    try {
                        sample = factory.createSample(mimeData->getClassName().toStdString());
                    } catch (std::runtime_error& e) {}
                    if(sample) {
                        ISampleToScene visitor;
                        sample->accept(&visitor);
                        visitor.getItems();
                        QGraphicsItem *view = visitor.getMultiLayerView();
                        view->setPos(event->scenePos().x()-view->boundingRect().width()/2, event->scenePos().y()-view->boundingRect().height()/2);

                        foreach(QGraphicsItem *view, visitor.getItems()) {
                            addItem(view);
                        }

                        ISampleViewAligner layout;
                        layout.makeAlign(visitor.getMultiLayerView());


                    }
                }

            }






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



