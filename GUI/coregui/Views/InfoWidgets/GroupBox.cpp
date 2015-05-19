// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/GroupBox.cpp
//! @brief     Implements class GroupBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GroupBox.h"

#include <QMouseEvent>
#include <QStyleOptionGroupBox>
#include <QStylePainter>
#include <QPushButton>
#include <iostream>
#include <QPainter>
#include <QPixmap>
#include <QApplication>
#include <QToolTip>

namespace
{
    int imageWidth = 16;
    int imageheigth = 16;
    int offset_of_tooltip_position = 20;
}

GroupBox::GroupBox( QWidget *parent ): QGroupBox( parent )
  , m_collapsed( false ) {}

GroupBox::GroupBox( const QString &title
                    , QWidget *parent ): QGroupBox( title, parent )
  , m_collapsed( false ), m_title(title)
{
    QGroupBox::setTitle("");
    setMouseTracking(true);
}

bool GroupBox::isCollapsed() { return m_collapsed; }

void GroupBox::mousePressEvent( QMouseEvent *e )
{
    if( e->button() == Qt::LeftButton )
    {
        QStyleOptionGroupBox option;
        initStyleOption( &option );
        QRect buttonArea( m_xImage, m_yImage, imageWidth , imageheigth );
        if( buttonArea.contains( e->pos() ) ) {
            emit clicked(true);
        }
    }
}
void GroupBox::mouseMoveEvent(QMouseEvent *event)
{
    QRect buttonArea(m_xImage, m_yImage, imageWidth ,imageheigth);

    if (buttonArea.contains(event->pos()))
    {
        QToolTip::showText(this->mapToGlobal(QPoint(m_xImage + offset_of_tooltip_position , m_yImage)), "show plot");
    }
}

void GroupBox::paintEvent( QPaintEvent * )
{
    QStylePainter paint(this);
    QStyleOptionGroupBox option;
    initStyleOption(&option);
    paint.drawComplexControl(QStyle::CC_GroupBox, option);
    paint.end();
    QPixmap pix = mergeSideBySide(
        QPixmap(":/images/expand_arrow.png").scaled(imageWidth , imageheigth, Qt::KeepAspectRatio));
    paint.drawItemPixmap(option.rect.adjusted(0, 0, -10, 0), Qt::AlignTop | Qt::AlignLeft, pix);
    paint.end();
}

void GroupBox::setCollapse( bool collapse )
{
    m_collapsed = collapse;
    foreach( QWidget *widget, findChildren<QWidget*>() )
        widget->setHidden( collapse );
}

QPixmap GroupBox::mergeSideBySide( const QPixmap& pix)
{
    QPainter p(this);
    int strWidth = p.fontMetrics().width(m_title);
    int strHeight = p.fontMetrics().height();
    int pixWidth = pix.width();
//    int pixHeight = pix.height();
    QPixmap res( strWidth + 3 + pixWidth, strHeight);
    res.fill(Qt::transparent);
    p.begin( &res );
    p.drawPixmap(strWidth,0, pix );
    p.drawText( QRect(0, 0, strWidth, strHeight), 0, m_title);
    p.end();

    m_xImage = strWidth;
    m_yImage = 0;
    return res;

}

