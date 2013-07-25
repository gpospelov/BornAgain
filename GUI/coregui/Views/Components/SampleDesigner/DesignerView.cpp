#include "DesignerView.h"
#include "DesignerMimeData.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QShortcut>

#include "LayerView.h"
#include "LayerView.h"

#include "styledbar.h"

#include <cmath>
#include <iostream>


DesignerView::DesignerView(QWidget *parent, QGraphicsScene *scene)
    : QWidget(parent)
    , m_graphicsView(0)
{
//    setMinimumSize(128, 128);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   setAcceptDrops(false);

//   Manhattan::StyledBar *bar = new Manhattan::StyledBar;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
//    layout->addWidget(bar);
    m_graphicsView = new QGraphicsView(scene);
    m_graphicsView->setAcceptDrops(true);

    layout->addWidget(m_graphicsView);
    setLayout(layout);

    m_graphicsView->setRenderHint(QPainter::Antialiasing);

//   QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
//   connect(shortcut, SIGNAL(activated()), this, SLOT(deleteItem()));

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


void DesignerView::zoomIn()
{
    scaleView(1.1);
}


void DesignerView::zoomOut()
{
    scaleView(0.9);
}

//! zoom view to show all items
void DesignerView::zoomFit()
{
    m_graphicsView->fitInView(m_graphicsView->scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
}


void DesignerView::clearAll()
{
    m_graphicsView->scene()->clear();
}


void DesignerView::deleteItem()
{
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
