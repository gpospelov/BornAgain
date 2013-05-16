#include "DesignerHelper.h"

int DesignerHelper::m_default_layer_height = 50;
int DesignerHelper::m_default_layer_width = 200;

QGradient DesignerHelper::getLayerGradient(const QColor &color, const QRect &rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
    return result;
}
