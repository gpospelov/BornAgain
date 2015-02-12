// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/GroupBox.h
//! @brief     Defines class GroupBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QGroupBox>

class GroupBox : public QGroupBox
{
        Q_OBJECT

public:
        GroupBox( QWidget *parent = 0 );
        GroupBox( const QString &title, QWidget *parent = 0 );

        bool isCollapsed();
        void setCollapse( bool collapse );

protected:
        void mousePressEvent( QMouseEvent *e );
        void mouseReleaseEvent( QMouseEvent *e );
        void paintEvent( QPaintEvent * );

private:
        QPoint  clickPos;
        bool    m_collapsed;
};

#endif
