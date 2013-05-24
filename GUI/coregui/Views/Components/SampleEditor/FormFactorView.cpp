#include "FormFactorView.h"
#include "DesignerHelper.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>


FormFactorView::FormFactorView(QGraphicsItem *parent)
    : ISampleRectView(parent)
{
    setName("FormFactorView");
    setColor(DesignerHelper::getDefaultFormFactorColor());
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultFormFactorWidth(), DesignerHelper::getDefaultFormFactorHeight()) );
    addPort("out", QNEPort::Output, QNEPort::FormFactor);
    addPort("transformation", QNEPort::Input, QNEPort::GeometryTransformation);
}


void FormFactorView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getDecorationGradient(m_color, getRectangle() ) );
    painter->drawRoundedRect(getRectangle(), 5, 5);

    if ( m_label.isEmpty() ) return;

    painter->setPen(Qt::black);
    double width = getRectangle().width()*0.9;
    double height = m_label_vspace;
    double yoffset = getRectangle().height()*0.05;
    QFont serifFont("Monospace", 12, QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect( getRectangle().x() + (getRectangle().width()-width)/2., getRectangle().y() + yoffset, width, height );
    painter->drawText(textRect, Qt::AlignCenter, m_label);
}


