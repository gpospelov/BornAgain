// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/InstrumentWidgets/GroupBox.cpp
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

GroupBox::GroupBox( QWidget *parent ): QGroupBox( parent ), m_collapsed( false ) {} GroupBox::GroupBox( const QString &title, QWidget *parent ): QGroupBox( title, parent ), m_collapsed( false ) {}

bool GroupBox::isCollapsed() { return m_collapsed; }

void GroupBox::mousePressEvent( QMouseEvent *e )
{
    if( e->button() == Qt::LeftButton )
    {
        QStyleOptionGroupBox option;
        initStyleOption( &option );
        QRect buttonArea( 0, 0, 24, 24 );
        buttonArea.moveTopRight( option.rect.adjusted( 0, 0, -10, 0 ).topRight() );
        if( buttonArea.contains( e->pos() ) )
        {
            clickPos = e->pos();
            return;
        }
    }
    QGroupBox::mousePressEvent( e );
}

void GroupBox::mouseReleaseEvent( QMouseEvent *e )
{
    if( e->button() == Qt::LeftButton && clickPos == e->pos() )
        setCollapse( !isCollapsed() );
}

void GroupBox::paintEvent( QPaintEvent * )
{
    QStylePainter paint( this );
    QStyleOptionGroupBox option;
    initStyleOption( &option );
    paint.drawComplexControl( QStyle::CC_GroupBox, option );
    paint.drawItemPixmap(
                option.rect.adjusted( 0, 0, -10, 0 ),
                Qt::AlignTop | Qt::AlignRight,
                QPixmap( m_collapsed ?
                             ":/images/expand_arrow.png" :
                             ":/images/collapse_arrow.png" ).scaled(16, 16, Qt::KeepAspectRatio) );
}

void GroupBox::setCollapse( bool collapse )
{
    m_collapsed = collapse;
    foreach( QWidget *widget, findChildren<QWidget*>() )
        widget->setHidden( collapse );
}
