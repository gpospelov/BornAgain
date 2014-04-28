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

    enum WidgetTypes {
        IViewType = QGraphicsItem::UserType+1, // = 65537
        ISampleRectType,
        NodeEditorPortType,
        NodeEditorConnectionType,
        MultiLayerType,
        LayerType,
        ParticleLayoutType,
        InterferenceFunctionType,
        InterferenceFunction1DParaType,
        FormFactorType,
        FormFactorFullSphereType,
        FormFactorPyramidType,
        FormFactorCylinderType,
        FormFactorPrism3Type
    };

    static int getDefaultLayerWidth() { return m_default_layer_width; }
    static int getDefaultLayerHeight() { return m_default_layer_height; }
    static QColor getDefaultLayerColor() { return QColor(Qt::lightGray); }

    static int getDefaultMultiLayerWidth() { return m_default_layer_width*1.15; }
    static int getDefaultMultiLayerHeight() { return m_default_layer_height; }
    static QRectF getDefaultMultiLayerRect();

    static int getDefaultParticleLayoutWidth() { return m_default_layer_height*3.5; }
    static int getDefaultParticleLayoutHeight() { return m_default_layer_height*4.5; }

    static int getDefaultInterferenceFunctionWidth() { return m_default_layer_height*3; }
    static int getDefaultInterferenceFunctionHeight() { return m_default_layer_height*3; }

    static int getDefaultParticleWidth() { return m_default_layer_height*3; }
    static int getDefaultParticleHeight() { return m_default_layer_height*4; }
    static QColor getDefaultParticleColor() { return QColor(210, 223, 237); }

    static int getDefaultMaterialWidth() { return m_default_layer_height*1.2; }
    static int getDefaultMaterialHeight() { return m_default_layer_height*1.2; }
    static QColor getDefaultMaterialColor() { return QColor(qrand() % 256, qrand() % 256, qrand() % 256); }

    static QGradient getLayerGradient(const QColor &color, const QRectF &rect);
    static QGradient getDecorationGradient(const QColor &color, const QRectF &rect);

    static QPixmap getSceneBackground();
    static QPixmap getPixmapLayer();
    static QPixmap getPixmapMultiLayer();
    static QPixmap getPixmapParticleLayout();
    static QPixmap getPixmapInterferenceFunction();
    static QPixmap getPixmapParticle();
    static QPixmap getPixmapDefault();

    static QColor getRandomColor() { return QColor(qrand() % 256, qrand() % 256, qrand() % 256); }

    //! sort graphics item according they y-coordinate
    static bool sort_layers(QGraphicsItem* left, QGraphicsItem *right) {
        return left->y() < right->y();
    }

    //! non-linear convertion of layer's thickness in nanometers to screen size
    //! to have reasonable graphics representation of layer in the form of QRect
    static int nanometerToScreen(double nanometer);

    //! returns default bounding rectangle for given SampleView name
    static QRectF getDefaultBoundingRect(const QString &name);

    //! returns system dependent font size
    static int getLabelFontSize();
    static int getPortFontSize();

private:
    static int m_default_layer_height;
    static int m_default_layer_width;
};

#include <complex>
typedef std::complex<double> complex_t;
Q_DECLARE_METATYPE(complex_t)


#endif // EDITORHELPER_H
