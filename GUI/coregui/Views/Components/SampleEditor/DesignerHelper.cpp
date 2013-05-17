#include <QPainter>
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


QPixmap DesignerHelper::getSceneBackground()
{
    const int size= 10;
    QPixmap result(size, size);
    result.fill(QColor(250, 250, 250));
    QPainter tilePainter(&result);
    QColor color(220, 220, 220);
    tilePainter.fillRect(0.0, 0.0, 2, 2, color);
    tilePainter.end();

    return result;
}


QPixmap DesignerHelper::getPixmapLayer() {
    QRect rect(0,0, DesignerHelper::getLayerWidth(), DesignerHelper::getLayerHeight());
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getLayerGradient(Qt::lightGray, rect));
    painter.drawRect(rect);
    return pixmap;
}


QPixmap DesignerHelper::getPixmapMultiLayer() {
    QRect rect(0,0, DesignerHelper::getLayerWidth(), DesignerHelper::getLayerHeight());
    QPixmap pixmap(rect.width()+1, rect.height()+1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(DesignerHelper::getLayerGradient(Qt::lightGray, rect));
    painter.drawRect(rect);
    painter.setPen(Qt::DashLine);
    painter.drawLine(0, DesignerHelper::getLayerHeight()*0.3, DesignerHelper::getLayerWidth(), DesignerHelper::getLayerHeight()*0.3);
    painter.drawLine(0, DesignerHelper::getLayerHeight()*0.6, DesignerHelper::getLayerWidth(), DesignerHelper::getLayerHeight()*0.6);
    return pixmap;
}


QPixmap DesignerHelper::getPixmapDefault() {
    return QPixmap(":/images/mode_exp.png");
}

