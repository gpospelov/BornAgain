#include "ParticleView.h"
#include "GroupProperty.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QDebug>


ParticleView::ParticleView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("Particle");
    setLabel("Particle");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultParticleWidth(), DesignerHelper::getDefaultParticleHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::FormFactor);
    addPort("rotation", NodeEditorPort::Input, NodeEditorPort::GeometryTransformation);
    m_roundpar = 5;
    m_label_vspace = 45;
}


void ParticleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getDecorationGradient(m_color, getRectangle() ) );
    painter->drawRoundedRect(getRectangle(), m_roundpar, m_roundpar);

    if ( m_label.isEmpty() ) return;

    painter->setPen(Qt::black);
    double width = getRectangle().width()*0.9;
    double yoffset = 5; // space above the label
    //double height = m_label_vspace - yoffset;
    double height = 20;
    QFont serifFont("Monospace", DesignerHelper::getLabelFontSize(), QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect( getRectangle().x() + (getRectangle().width()-width)/2., getRectangle().y() + yoffset, width, height );
    painter->drawText(textRect, Qt::AlignCenter, m_label);

    QRect target(getRectangle().width()/2 - 16, 25, 32, 32);
    painter->drawPixmap(target, m_pixmap);
}


void ParticleView::setParameterizedItem(ParameterizedItem *item)
{
    ConnectableView::setParameterizedItem(item);
    onPropertyChange("Form Factor");
}


void ParticleView::onPropertyChange(QString propertyName)
{
    Q_ASSERT(m_item);
    if(propertyName == "Form Factor") {
        GroupProperty mp = getParameterizedItem()->property("Form Factor").value<GroupProperty>();
        QString filename = QString(":/SampleDesigner/images/ff_%1_32.png").arg(mp.getValue());
        m_pixmap = QPixmap(filename);
        update();
    } else {
        IView::onPropertyChange(propertyName);
    }
}
