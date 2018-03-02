// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/OverlayLabelWidget.cpp
//! @brief     Implements class OverlayLabelWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "OverlayLabelWidget.h"
#include "DesignerHelper.h"
#include <QColor>
#include <QFont>
#include <QPainter>

OverlayLabelWidget::OverlayLabelWidget(QWidget *parent)
    : QWidget(parent)
    , m_bounding_rect(QRect(0,0,10,10))
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void OverlayLabelWidget::setRectangle(const QRect &rect)
{
    m_bounding_rect = rect;
}

void OverlayLabelWidget::setPosition(int x, int y)
{
    setGeometry(x, y, m_bounding_rect.width(), m_bounding_rect.height());
}

void OverlayLabelWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(QColor(Qt::lightGray));
    QFont serifFont("Monospace", DesignerHelper::getHeaderFontSize(),
                    QFont::Normal, true);
    painter.setFont(serifFont);
//    painter.drawRect(m_bounding_rect);
    painter.drawText(m_bounding_rect, Qt::AlignCenter, m_text);
}
