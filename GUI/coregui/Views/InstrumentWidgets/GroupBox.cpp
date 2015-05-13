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

GroupBox::GroupBox( QWidget *parent ): QGroupBox( parent )
  , m_collapsed( false ) {}
GroupBox::GroupBox( const QString &title
                    , QWidget *parent ): QGroupBox( title, parent )
  , m_collapsed( false ), m_title(title)
{
    QGroupBox::setTitle("");
//    m_title = title;
}

bool GroupBox::isCollapsed() { return m_collapsed; }

void GroupBox::mousePressEvent( QMouseEvent *e )
{
    if( e->button() == Qt::LeftButton )
    {
        QStyleOptionGroupBox option;
        initStyleOption( &option );
        QRect buttonArea( m_xImage, m_yImage, 16, 16 );
//        buttonArea.moveTopRight( option.rect.adjusted( 0, 0, -10, 0 ).topRight());
        if( buttonArea.contains( e->pos() ) )
        {
            emit clicked(true);
        }
    }
}

//void GroupBox::mouseReleaseEvent( QMouseEvent *e )
//{
//    if( e->button() == Qt::LeftButton && clickPos == e->pos() )
//        setCollapse( !isCollapsed() );
//        std::cout << "here" << std::endl;
//}

void GroupBox::paintEvent( QPaintEvent * )
{
//    QPushButton *button = new QPushButton(this);
//    QIcon icon("/home/sezer/Downloads/qt-creator-opensource-src-3.4.0/share/qtcreator/qmlicons/Qt/16x16/InfoBanner.png");
//    button->setIcon(icon);

    QStylePainter paint( this );
    QStyleOptionGroupBox option;
    initStyleOption( &option );
    paint.drawComplexControl( QStyle::CC_GroupBox, option );
    QPixmap pix = mergeSideBySide(QPixmap(":/images/expand_arrow.png").scaled(16,16,Qt::KeepAspectRatio), m_title);
    paint.drawItemPixmap(
                option.rect.adjusted( 0, 0, -10, 0 ),
                Qt::AlignTop | Qt::AlignLeft,
                pix);

//                QPixmap( m_collapsed ?
//                             ":/images/expand_arrow.png" :
//                             ":/images/collapse_arrow.png" ).scaled(16, 16, Qt::KeepAspectRatio));
}

void GroupBox::setCollapse( bool collapse )
{
    m_collapsed = collapse;
    foreach( QWidget *widget, findChildren<QWidget*>() )
        widget->setHidden( collapse );
}

//void GroupBox::mouseMoveEvent(QMouseEvent * event)
//{
//    double xPos = event->x();
//    double yPos = event->y();
//    QPointF *pointF = new QPointF(xPos, yPos);

//    if( 50 <= xPos && xPos <= 66 && 3 <=  yPos && yPos <= 19) {
//        emit mousePressedButton(event->pos());
//        emit mousePressEvent(new QMouseEvent(QMouseEvent::MouseButtonPress
//                                             ,pointF
//                                             ,Qt::LeftButton
//                                             ,Qt::NoModifier));
//    }
//}

QPixmap GroupBox::mergeSideBySide( const QPixmap& pix, const QString txt )
{
    QPainter p;
    int strWidth = p.fontMetrics().width( txt );
    int strHeight = p.fontMetrics().height();
    int pixWidth = pix.width();
    int pixHeight = pix.height();
    QPixmap res( strWidth + 3 + pixWidth, strHeight);
    res.fill(Qt::transparent);
    p.begin( &res );
    p.drawPixmap(strWidth,0, pix );
    p.drawText( QRect(0, 0, strWidth, strHeight), 0, txt );
    p.end();

    m_xImage = strWidth;
    m_yImage = 0;
    return res;

}

void GroupBox::setTitle(const QString &title)
{
    m_title = title;
}

