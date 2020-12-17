//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/mainwindow/fancytab.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/mainwindow/fancytab.h"
#include "mvvm/widgets/widgetutils.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

namespace {
QColor defaultColor() {
    static QWidget tmpWidget;
    return tmpWidget.palette().color(QPalette::Window);
}
} // namespace

namespace gui2 {

FancyTab::FancyTab(const QString& title, QWidget* parent)
    : QWidget(parent), m_label(new QLabel(title)) {
    ModelView::Utils::ScaleLabelFont(m_label, 1.25);
    setFixedHeight(ModelView::Utils::HeightOfLetterM() * 2.5);

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(m_label, 0, Qt::AlignCenter);
    setMouseTracking(true);
}

void FancyTab::setSelected(bool value) {
    m_isSelected = value;
    update();
}

void FancyTab::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    if (m_widgetColor.isValid())
        painter.fillRect(0, 0, size().width(), size().height(), m_widgetColor);

    if (m_isSelected && isEnabled())
        painter.fillRect(
            QRectF(QPointF(0, size().height() - 2), QPointF(size().width(), size().height())),
            QColor("#0d4283"));
}

void FancyTab::mousePressEvent(QMouseEvent* event) {
    if (isEnabled() && event->button() == Qt::LeftButton)
        clicked();
}

void FancyTab::enterEvent(QEvent*) {
    if (isEnabled())
        m_widgetColor = QColor(Qt::lightGray);
    update();
}

void FancyTab::leaveEvent(QEvent*) {
    if (isEnabled())
        m_widgetColor = defaultColor();
    update();
}

} // namespace gui2
