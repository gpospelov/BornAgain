// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_ELEMENTVIEW_H
#define DAREFL_SLDEDITOR_ELEMENTVIEW_H

#include <darefl/darefl_export.h>
#include <darefl/sldeditor/graphicsscene.h>

#include <QGraphicsObject>

namespace DaRefl
{

//! The interface of any QGraphicsViewItem on GraphicsScene to the Sceneadapter
class DAREFLCORE_EXPORT ElementView : public QGraphicsObject
{
    Q_OBJECT

public:
    ElementView();
    ~ElementView();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;

    ModelView::SceneAdapterInterface* sceneAdapter() const;

    void setCenterBased(bool choice);
    void adaptX(bool choice);
    void adaptY(bool choice);
    void adaptW(bool choice);
    void adaptH(bool choice);
    void stretchLeft(bool choice);
    void stretchRight(bool choice);

protected:
    QRectF displayRect(const QRectF& real_rect) const;
    QPainterPath displayPath(QPainterPath real_path) const;
    QPointF scenePos(QPointF pixel_pos) const;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF displayRectCenterBased(const QRectF& real_rect) const;
    QRectF displayRectEdgeBased(const QRectF& real_rect) const;
    QRectF stretchRectLeft(const QRectF& real_rect) const;
    QRectF stretchRectRight(const QRectF& real_rect) const;

private:
    bool m_center_based = true;
    bool m_adapt_x = true;
    bool m_adapt_y = true;
    bool m_adapt_width = true;
    bool m_adapt_height = true;
    bool m_stretch_left = false;
    bool m_stretch_right = false;
};

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_ELEMENTVIEW_H
