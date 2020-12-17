//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/sldeditor/roughnesselementview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SLDEDITOR_ROUGHNESSELEMENTVIEW_H
#define BORNAGAIN_GUI2_SLDEDITOR_ROUGHNESSELEMENTVIEW_H

#include "darefl_export.h"
#include "gui2/sldeditor/elementview.h"

#include <QBrush>
#include <QPainterPath>
#include <QPen>

namespace gui2 {

//! The roughness QGraphicsViewItem
class DAREFLCORE_EXPORT RoughnessElementView : public ElementView {
public:
    RoughnessElementView();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void setLeftPath(QPainterPath left_path);
    void setRightPath(QPainterPath right_path);
    void setBrush(QBrush brush);
    void setPen(QPen pen);

protected:
    QPainterPath m_left_path;
    QPainterPath m_right_path;
    QBrush m_brush;
    QPen m_pen;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_SLDEDITOR_ROUGHNESSELEMENTVIEW_H
