// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleView.cpp
//! @brief     Implements class ParticleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParticleView.h"
#include "GUIHelpers.h"
#include "GroupItem.h"
#include "GroupProperty.h"
#include "ParticleItem.h"
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

ParticleView::ParticleView(QGraphicsItem *parent) : ConnectableView(parent)
{
    setName(Constants::ParticleType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(
        DesignerHelper::getDefaultBoundingRect(Constants::ParticleType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR);
    addPort("transformation", NodeEditorPort::INPUT,
            NodeEditorPort::TRANSFORMATION);
    m_roundpar = 5;
    m_label_vspace = 45;
}

void ParticleView::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(
        DesignerHelper::getDecorationGradient(m_color, getRectangle()));
    painter->drawRoundedRect(getRectangle(), m_roundpar, m_roundpar);

    if (m_label.isEmpty())
        return;

    painter->setPen(Qt::black);
    double width = getRectangle().width() * 0.9;
    double yoffset = 5; // space above the label
    // double height = m_label_vspace - yoffset;
    double height = 20;
    QFont serifFont("Monospace", DesignerHelper::getLabelFontSize(),
                    QFont::Normal);
    painter->setFont(serifFont);
    QRect textRect(getRectangle().x() + (getRectangle().width() - width) / 2.,
                   getRectangle().y() + yoffset, width, height);
    painter->drawText(textRect, Qt::AlignCenter, m_label);

    QRect target(getRectangle().width() / 2 - 16, 25, 32, 32);
    painter->drawPixmap(target, m_pixmap);
}

void ParticleView::onPropertyChange(const QString &propertyName)
{
    if (propertyName == ParticleItem::P_FORM_FACTOR) {
//        updatePixmap();
        update_appearance();
    }

    IView::onPropertyChange(propertyName);
}

void ParticleView::addView(IView *childView, int /*row*/)
{
    if (childView->type() == DesignerHelper::TRANSFORMATION) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 0);
    } else {
        throw GUIHelpers::Error(
            "ParticleView::addView() -> Error. Unknown view");
    }
}

void ParticleView::update_appearance()
{
    updatePixmap();
    ConnectableView::update_appearance();
}

void ParticleView::updatePixmap()
{
    GroupProperty_t group_property
        = dynamic_cast<GroupItem *>(
              getItem()->getItem(ParticleItem::P_FORM_FACTOR))
              ->group();
    QString current_ff_type = group_property->getCurrentType();
    QString filename
        = QString(":/widgetbox/images/ff_%1_32.png").arg(current_ff_type);
    m_pixmap = QPixmap(filename);
}
