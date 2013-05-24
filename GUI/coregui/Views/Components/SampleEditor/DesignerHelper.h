#ifndef DESIGNERHELPER_H
#define DESIGNERHELPER_H

#include <QGradient>
#include <QColor>
#include <QRect>
#include <QGraphicsItem>

//! collection of static methods with SampleDesigner geometry settings
class DesignerHelper
{
public:

    static int getDefaultLayerWidth() { return m_default_layer_width; }
    static int getDefaultLayerHeight() { return m_default_layer_height; }

    static int getDefaultMultiLayerWidth() { return m_default_layer_width*1.20; }
    static int getDefaultMultiLayerHeight() { return m_default_layer_height; }

    static int getDefaultDecorationWidth() { return m_default_layer_height*3; }
    static int getDefaultDecorationHeight() { return m_default_layer_height*4; }

    static int getDefaultInterferenceFunctionWidth() { return m_default_layer_height*3; }
    static int getDefaultInterferenceFunctionHeight() { return m_default_layer_height*3; }

    static int getDefaultFormFactorWidth() { return m_default_layer_height*3; }
    static int getDefaultFormFactorHeight() { return m_default_layer_height*3; }
    //static QColor getDefaultFormFactorColor() { return QColor(99, 184, 255); }
    static QColor getDefaultFormFactorColor() { return QColor(Qt::lightGray); }

    static QGradient getLayerGradient(const QColor &color, const QRect &rect);
    static QGradient getDecorationGradient(const QColor &color, const QRect &rect);

    static QPixmap getSceneBackground();
    static QPixmap getPixmapLayer();
    static QPixmap getPixmapMultiLayer();
    static QPixmap getPixmapDefault();

    //! sort graphics item according they y-coordinate
    static bool sort_layers(QGraphicsItem* left, QGraphicsItem *right) {
        return left->y() < right->y();
    }

    //! non-linear converttion of layer's thickness in nanometers to screen size
    //! to have reasonable graphics representation of layer in the form of QRect
    static int nanometerToScreen(double nanometer);

    private:
    static int m_default_layer_height;
    static int m_default_layer_width;
};

#include <complex>
typedef std::complex<double> complex_t;
Q_DECLARE_METATYPE(complex_t)


#endif // EDITORHELPER_H
