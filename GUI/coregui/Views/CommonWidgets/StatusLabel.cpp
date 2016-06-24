// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/StatusLabel.cpp
//! @brief     Implements class StatusLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "StatusLabel.h"
#include <QPainter>
#include <QColor>
#include <QFont>
#include <QDebug>

namespace {
const int default_label_height = 20;
const int default_text_size = 12;
}

StatusLabel::StatusLabel(QWidget *parent)
    : QFrame(parent)
    , m_font("Monospace", default_text_size, QFont::Normal, false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(default_label_height);
}

void StatusLabel::setText(const QString &text)
{
    m_text = text;
    update();
}

void StatusLabel::setFont(const QFont &font)
{
    m_font = font;
    update();
}

void StatusLabel::setPointSize(int pointSize)
{
    m_font.setPointSize(pointSize);
    update();
}

void StatusLabel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(QColor(Qt::black));
    painter.setPen(QColor(Qt::black));
    painter.setFont(m_font);

    QRect textRect(0, 0, geometry().width(), geometry().height());
    painter.fillRect(textRect, QColor(Qt::white));
    painter.drawText(textRect, Qt::AlignVCenter| Qt::AlignLeft, m_text);
}
