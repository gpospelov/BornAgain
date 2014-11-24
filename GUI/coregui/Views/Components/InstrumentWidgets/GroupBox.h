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
