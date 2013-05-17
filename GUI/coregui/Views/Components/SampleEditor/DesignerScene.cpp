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

    LayerDockView *ml = new LayerDockView();
    //    LayerView * layer = new LayerView();
    ml->addLayer(new LayerView());
    ml->addLayer(new LayerView());


    ml->setPos(-ml->rect().width()/2, 100.0);
    addItem(ml);
}


DesignerScene::~DesignerScene()
{
    delete m_widgetFactory;
}


void DesignerScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "SampleEditorScene::dragEnterEvent() ->" << std::endl;
        event->acceptProposedAction();
}


void DesignerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "SampleEditorScene::dragMoveEvent() ->" << std::endl;
        event->acceptProposedAction();
}


void DesignerScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "SampleEditorScene::dragLeaveEvent() ->" << std::endl;
        event->acceptProposedAction();
}


void DesignerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "SampleEditorScene::dropEvent() -> " << std::endl;
        const DesignerMimeData *mimeData = checkDragEvent(event);
        if (mimeData) {
            std::cout << "SampleEditorScene::dropEvent() -> yes " << mimeData->getClassName().toStdString() << std::endl;

            ISampleView *view = m_widgetFactory->create( mimeData->getClassName() );
//            MultiLayerView *layer = new MultiLayerView();
            std::cout << "XXX 2.1 " << view << std::endl;
            addItem(view);
            std::cout << "XXX 2.2" << std::endl;
            view->setPos(event->pos());
            std::cout << "XXX 2.3" << std::endl;
//            addItem(new LayerView());
            //addLayer(new LayerView(), event->pos());
            update();
        }
}


const DesignerMimeData *DesignerScene::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }

    if(mimeData->hasFormat("widgetbox") ) {
        std::cout << "SampleEditorScene::checkDragEvent() yes" << std::endl;
        event->setAccepted(true);
    } else {
        std::cout << "SampleEditorScene::checkDragEvent() no" << std::endl;
        event->setAccepted(false);
    }
    return mimeData;
}


