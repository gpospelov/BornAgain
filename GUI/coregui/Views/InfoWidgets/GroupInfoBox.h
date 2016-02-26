// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/GroupInfoBox.h
//! @brief     Defines class GroupInfoBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GROUPINFOBOX_H
#define GROUPINFOBOX_H

#include <QGroupBox>

//! The class which extends QGroupBox with clickable icon next to the label
class GroupInfoBox : public QGroupBox
{
        Q_OBJECT

public:
        GroupInfoBox( QWidget *parent = 0 );
        GroupInfoBox( const QString &title, QWidget *parent = 0 );

        void setButtonToolTip(const QString &text);

protected:
        void mousePressEvent( QMouseEvent *e );
        void paintEvent( QPaintEvent * );
        void mouseMoveEvent(QMouseEvent *event);

private:
        void init_box();

        QString m_title;
        QString m_toolTipText;
        int m_xImage;
        int m_yImage;
};

#endif
