// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_ROUGHNESSELEMENTVIEW_H
#define DAREFL_SLDEDITOR_ROUGHNESSELEMENTVIEW_H

#include <darefl/darefl_export.h>
#include <darefl/sldeditor/elementview.h>

#include <QBrush>
#include <QPainterPath>
#include <QPen>

namespace DaRefl
{

//! The roughness QGraphicsViewItem
class DAREFLCORE_EXPORT RoughnessElementView : public ElementView
{
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

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_ROUGHNESSELEMENTVIEW_H
