// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoLabelWidget.cpp
//! @brief     Implements class InfoLabelWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InfoLabelWidget.h"
#include <QPainter>

InfoLabelWidget::InfoLabelWidget(QWidget *parent)
    : QWidget(parent)
    , m_text("xxx")
{
    m_bounding_rect.setWidth(200);
    m_bounding_rect.setHeight(30);
}

void InfoLabelWidget::setPosition(int x, int y)
{
    setGeometry(x, y, m_bounding_rect.width(), m_bounding_rect.height());
}

void InfoLabelWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawText(m_bounding_rect, Qt::AlignCenter, tr("Qt\nProject"));
}
