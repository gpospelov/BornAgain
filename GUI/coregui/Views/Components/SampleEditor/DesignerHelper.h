#ifndef DESIGNERHELPER_H
#define DESIGNERHELPER_H

#include <QGradient>
#include <QColor>
#include <QRect>


//! collection of static methods with SampleDesigner geometry settings
class DesignerHelper
{
public:

    static int getLayerHeight() { return m_default_layer_height; }
    static int getLayerWidth() { return m_default_layer_width; }

    static int getMultiLayerHeight() { return m_default_layer_height; }
    static int getMultiLayerWidth() { return m_default_layer_width*1.20; }

    static QGradient getLayerGradient(const QColor &color, const QRect &rect);

    private:
    static int m_default_layer_height;
    static int m_default_layer_width;
};

#endif // EDITORHELPER_H
