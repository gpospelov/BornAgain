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
const int default_height = 20;
}

StatusLabel::StatusLabel(QWidget *parent)
    : QFrame(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(default_height);
}

void StatusLabel::setText(const QString &text)
{
    m_text = text;
    update();
}

void StatusLabel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(QColor(Qt::black));
    painter.setPen(QColor(Qt::black));
    QFont serifFont("Monospace", 12, QFont::Normal, false);
    painter.setFont(serifFont);

    QRect textRect(0, 0, geometry().width(), geometry().height());
    painter.fillRect(textRect, QColor(Qt::white));
    painter.drawText(textRect, Qt::AlignVCenter| Qt::AlignLeft, m_text);
}
