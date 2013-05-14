#include "SampleEditorView.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QShortcut>

#include "LayerView.h"
#include "HomogeneousLayerView.h"

#include <cmath>
#include <iostream>

SampleEditorView::SampleEditorView(QWidget *parent, QGraphicsScene *scene)
    : QWidget(parent)
    , m_graphicsView(0)
    , m_graphicsScene(scene)
{
//    setMinimumSize(128, 128);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setAcceptDrops(false);

    QVBoxLayout *layout = new QVBoxLayout;
    m_graphicsView = new QGraphicsView(scene);
//    m_graphicsView->setAcceptDrops(false);

    layout->addWidget(m_graphicsView);
    setLayout(layout);

//   QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
//   connect(shortcut, SIGNAL(activated()), this, SLOT(deleteItem()));

}


//void SampleEditorView::wheelEvent(QWheelEvent *event)
//{
//    scaleView(std::pow((double)2, -event->delta() / 240.0));
//}


void SampleEditorView::scaleView(qreal scaleFactor)
{
    qreal factor = m_graphicsView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    m_graphicsView->scale(scaleFactor, scaleFactor);
}


void SampleEditorView::deleteItem()
{
    std::cout << "SampleEditorView::deleteItem() -> " << std::endl;
    QList<QGraphicsItem*> selected = m_graphicsScene->selectedItems();
    for(int i=0; i<selected.size(); ++i) m_graphicsScene->removeItem(selected[i]);
    m_graphicsScene->update();
}


void SampleEditorView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        std::cout << "XXX left" << std::endl;
        break;
    case Qt::Key_Space:
        std::cout << "XXX space" << std::endl;
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




void SampleEditorView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->acceptProposedAction();
}


void SampleEditorView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece") ){

        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

        QString name;
        QString xml;
        QPoint global_mouse_pos;

        dataStream >> name >> xml >> global_mouse_pos;

        //LayerView *layer = new LayerView();
//        HomogeneousLayerView *layer = new HomogeneousLayerView();
//        m_graphicsScene->addItem(layer);
//        layer->setPos(event->pos());
//        layer->setBrush(QColor(0, 0, 255, 127));

    }
}
