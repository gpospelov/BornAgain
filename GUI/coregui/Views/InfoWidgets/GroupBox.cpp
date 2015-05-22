// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/GroupBox.cpp
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
#include "hostosinfo.h"
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
    int offset_of_icon_position = 24;
}

GroupBox::GroupBox( QWidget *parent ): QGroupBox( parent )
{
    setMouseTracking(true);
}

GroupBox::GroupBox( const QString &title, QWidget *parent )
    : QGroupBox( title, parent ), m_title(title)
{
    setMouseTracking(true);
}

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
    QRect buttonArea(m_xImage, m_yImage, imageWidth, imageheigth);

    if (buttonArea.contains(event->pos())) {
        QToolTip::showText(
            this->mapToGlobal(QPoint(m_xImage + offset_of_tooltip_position, m_yImage)),
            "Gives access to the extended distribution viewer.");
    }
}

void GroupBox::paintEvent(QPaintEvent *)
{
    QStylePainter paint(this);
    QStyleOptionGroupBox option;
    initStyleOption(&option);
    paint.drawComplexControl(QStyle::CC_GroupBox, option);

    m_xImage = this->geometry().topRight().x() - offset_of_icon_position;
    m_yImage = 0;

    // draw groupbox 
	int shift(1);
	if(Utils::HostOsInfo::isLinuxHost()) shift = 3;

    paint.drawItemPixmap(option.rect.adjusted(0, shift, 0, 0), Qt::AlignTop | Qt::AlignRight,
                         QPixmap(":/images/magnifier.png"));
}



