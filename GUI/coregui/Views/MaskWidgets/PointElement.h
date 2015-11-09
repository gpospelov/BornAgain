// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/PointElement.h
//! @brief     Defines PointElement class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef POINTELEMENT_H
#define POINTELEMENT_H

#include "WinDllMacros.h"
#include <QCursor>
#include <QGraphicsObject>
#include <QMap>

//! Point on MaskGraphicsScene represented as small circle or small rectangle.
//! Used by RectangleView to denote corners

class BA_CORE_API_ PointElement : public QGraphicsObject
{
    Q_OBJECT

public:
    enum EPointType
    {
        NONE, TOPLEFT, TOPMIDDLE, TOPRIGHT,
        MIDDLERIGHT,
        BOTTOMRIGHT, BOTTOMMIDLE, BOTTOMLEFT,
        MIDDLELEFT
    };

    PointElement(EPointType pointType, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void set_position(const QRectF &rect);

protected slots:
    void onParentChanged();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    static QMap<EPointType, Qt::CursorShape> m_cursors;
    EPointType m_pointType;
};

#endif
