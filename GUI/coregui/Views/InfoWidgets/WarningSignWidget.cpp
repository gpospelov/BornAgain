// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/WarningSignWidget.cpp
//! @brief     Implements class WarningSignWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "WarningSignWidget.h"
#include <QPainter>
#include <QRect>
#include <QMessageBox>

WarningSignWidget::WarningSignWidget(QWidget * parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_NoSystemBackground);
    //setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pixmap = QPixmap(":/images/warning@2x.png");
    setToolTip(QString(
        "Generation of Python Script failed. Code is not complete.\n"
        "Sometimes it happens if sample on canvas requires further\n"
        "assembling. Click to see details."
                   ));
}

void WarningSignWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect target(m_pixmap.rect());
    painter.drawPixmap(target, m_pixmap);
}

void WarningSignWidget::mousePressEvent(QMouseEvent *event)
{
    QMessageBox::warning(this, tr("Generation failed"),
        QString("Generation of Python Script failed with the following error message\n\n%1")
                         .arg(m_warning_message));

}

//! set geometry of widget around center point
void WarningSignWidget::setPosition(int x, int y)
{
    setGeometry(x, y, m_pixmap.width(), m_pixmap.height());
}
