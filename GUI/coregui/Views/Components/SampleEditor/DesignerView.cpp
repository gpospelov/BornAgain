#include "DesignerView.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QShortcut>

#include "LayerView.h"
#include "LayerView.h"

#include <cmath>
#include <iostream>

#include "DesignerMimeData.h"
#include "DesignerWidgetFactory.h"

DesignerView::DesignerView(QWidget *parent, QGraphicsScene *scene)
    : QWidget(parent)
    , m_graphicsView(0)
//    , m_graphicsScene(scene)
    , m_widgetFactory(new DesignerWidgetFactory())
{
//    setMinimumSize(128, 128);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   setAcceptDrops(false);

    QVBoxLayout *layout = new QVBoxLayout;
    m_graphicsView = new QGraphicsView(scene);
    m_graphicsView->setAcceptDrops(true);

    layout->addWidget(m_graphicsView);
    setLayout(layout);

    m_graphicsView->setRenderHint(QPainter::Antialiasing);

//   QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
//   connect(shortcut, SIGNAL(activated()), this, SLOT(deleteItem()));

}

DesignerView::~DesignerView()
{
    delete m_widgetFactory;
}


//void SampleEditorView::wheelEvent(QWheelEvent *event)
//{
//    scaleView(std::pow((double)2, -event->delta() / 240.0));
//}


void DesignerView::scaleView(qreal scaleFactor)
{
    qreal factor = m_graphicsView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    m_graphicsView->scale(scaleFactor, scaleFactor);
}


void DesignerView::deleteItem()
{
    std::cout << "SampleEditorView::deleteItem() -> " << std::endl;
    QList<QGraphicsItem*> selected = m_graphicsView->scene()->selectedItems();
    for(int i=0; i<selected.size(); ++i) {
        m_graphicsView->scene()->removeItem(selected[i]);
        delete selected[i];
    }
    m_graphicsView->scene()->update();
}


void DesignerView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Space:
        break;
    case Qt::Key_Delete:
        deleteItem();
        break;
    case Qt::Key_Backspace:
        deleteItem();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}




//void SampleEditorView::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
//        event->acceptProposedAction();
//}


//void SampleEditorView::dropEvent(QDropEvent *event)
//{
//    if (event->mimeData()->hasFormat("image/x-puzzle-piece") ){

//        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
//        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

//        QString name;
//        QString xml;
//        QPoint global_mouse_pos;

//        dataStream >> name >> xml >> global_mouse_pos;

//        //LayerView *layer = new LayerView();
//        HomogeneousLayerView *layer = new HomogeneousLayerView();
//        m_graphicsScene->addItem(layer);
//        layer->setPos(event->pos());
//        layer->setBrush(QColor(0, 0, 255, 127));

//    }
//}


//void DesignerView::dragEnterEvent(QDragEnterEvent *event)
//{
//    std::cout << "DesignerView::dragEnterEvent() ->" << std::endl;
////        event->acceptProposedAction();
//    event->accept();
//    QWidget::dragEnterEvent(event);
//}


//void DesignerView::dragMoveEvent(QDragMoveEvent *event)
//{
////    event->acceptProposedAction();
//    std::cout << "DesignerView::dragMoveEvent() -> " << event->pos().x() << " " << event->pos().y() << std::endl;
//    event->accept();
//    QWidget::dragMoveEvent(event);
//}


//void DesignerView::dragLeaveEvent(QDragLeaveEvent *event)
//{
//    std::cout << "DesignerView::dragLeaveEvent() ->" << std::endl;
//    QWidget::dragLeaveEvent(event);
//}


//void DesignerView::dropEvent(QDropEvent *event)
//{
//    std::cout << "SampleEditorScene::dropEvent() -> " << std::endl;
//        const DesignerMimeData *mimeData = checkDragEvent(event);
//        if (mimeData) {
//            std::cout << "DesignerView::dropEvent() -> yes " << mimeData->getClassName().toStdString() << std::endl;

//            ISampleView *view = m_widgetFactory->create( mimeData->getClassName() );
//            m_graphicsView->scene()->addItem(view);
//            view->setPos(event->pos().x()-view->boundingRect().width()/2, event->pos().y()-view->boundingRect().height()/2);
//        }
//}


void DesignerView::mouseMoveEvent(QMouseEvent *event)
{
    //std::cout << "DesignerView::mouseMoveEvent() -> " << event->pos().x() << " " << event->pos().y() << std::endl;
    QWidget::mouseMoveEvent(event);
}


//const DesignerMimeData *DesignerView::checkDragEvent(QDropEvent * event)
//{
//    std::cout << "DesignerView::checkDragEvent()" << std::endl;
//    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
//    if (!mimeData) {
//        event->ignore();
//        return 0;
//    }

//    if(mimeData->hasFormat("bornagain/widget") ) {
//        std::cout << "DesignerView::checkDragEvent() yes" << std::endl;
//        event->setAccepted(true);
//    } else {
//        std::cout << "DesignerView::checkDragEvent() no" << std::endl;
//        event->setAccepted(false);
//    }

//    return mimeData;
//}
