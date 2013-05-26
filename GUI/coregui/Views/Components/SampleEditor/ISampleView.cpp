#include "ISampleView.h"
#include "DesignerHelper.h"
#include "qneport.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QGraphicsDropShadowEffect>

ISampleRectView::ISampleRectView(QGraphicsItem *parent, QRect rect)
    : ISampleView(parent)
    , m_name("Unnamed")
    , m_color(Qt::gray)
    , m_rect(rect)
    , m_roundpar(3)
    , m_label_vspace(35)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}


void ISampleRectView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    double height = m_label_vspace - yoffset;
    QFont serifFont("Monospace", 12, QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect( getRectangle().x() + (getRectangle().width()-width)/2., getRectangle().y() + yoffset, width, height );
    painter->drawText(textRect, Qt::AlignCenter, m_label);
}


// adding port to the sample
QNEPort* ISampleRectView::addPort(const QString &name, QNEPort::PortDirection direction, QNEPort::PortType port_type)
{
    QNEPort *port = new QNEPort(this, name, direction, port_type);
    port->setNEBlock(this);
    setPortCoordinates();
    return port;

}


// calculation right y-pos for ports
void ISampleRectView::setPortCoordinates()
{
    if(!getNumberOfPorts()) return;

    // without main label ports will occupy all vertical space
    int hspace = getRectangle().height();
    if( !getLabel().isEmpty() ) hspace -= m_label_vspace;

    int nintervals = getNumberOfPorts() + 2;

    int dy = hspace / double(nintervals);
    int ypos = getRectangle().height() - hspace + dy;

    if(getNumberOfPorts() == 1) {
        ypos = getRectangle().height() - hspace + hspace/2;
    }

    int nOutPorts = getNumberOfOutputPorts();
    int nport(0);
    foreach(QGraphicsItem *item, childItems()) {
        QNEPort *port = dynamic_cast<QNEPort *>(item);
        if( !port ) continue;
        if (port->isOutput()) {
            port->setPos(getRectangle().width(), ypos);
        }else{
            if(nport == nOutPorts && nOutPorts!=0) ypos +=dy; // additional margin between output and input ports
            port->setPos(0.0, ypos);
        }
        ypos += dy;
        nport++;
    }
}


void ISampleRectView::setLabel(const QString &name)
{
    m_label = name;
    setPortCoordinates();
}


int ISampleRectView::getNumberOfPorts()
{
    int result(0);
    foreach(QGraphicsItem *item, childItems()) {
        QNEPort *port = dynamic_cast<QNEPort *>(item);
        if (port) result++;
    }
    return result;
}


int ISampleRectView::getNumberOfOutputPorts()
{
    int result(0);
    foreach(QGraphicsItem *item, childItems()) {
        QNEPort *port = dynamic_cast<QNEPort *>(item);
        if (port && port->isOutput()) result++;
    }
    return result;
}


int ISampleRectView::getNumberOfInputPorts()
{
    return getNumberOfPorts()- getNumberOfOutputPorts();
}
