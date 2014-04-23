#include "LayerView.h"
#include "ParticleLayoutView.h"
#include "ParameterizedItem.h"
#include "MaterialProperty.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>



LayerView::LayerView(QGraphicsItem *parent)
    : ILayerView(parent)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setRectangle(QRect(0, 0, DesignerHelper::getDefaultLayerWidth(), DesignerHelper::getDefaultLayerHeight()));
    setName(QString("Layer"));
    setToolTip(QString("%1\n%2").arg("Layer").arg("A layer with thickness and material.\nCan be connected with ParticleLayout."));
    setAcceptDrops(false);
    addPort(" ", NodeEditorPort::Input, NodeEditorPort::ParticleFactory);
}


void LayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

//    if(ParameterizedItem *item = getParameterizedItem()) {
//        qDebug() << "XXX " << item;
//        QVariant v = item->property("Material");
//        Q_ASSERT(v.isValid());
//        MaterialProperty mat = v.value<MaterialProperty>();
//        m_color = mat.getColor();
//    }

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}


void LayerView::addView(IView *childView, int /* row */)
{
    qDebug() << "LayerView::addView() " << m_item->itemName() << childView->getParameterizedItem()->itemName();
    ParticleLayoutView *layout = dynamic_cast<ParticleLayoutView *>(childView);
    Q_ASSERT(layout);
    connectInputPort(layout);
}

