// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/DesignerHelper.h
//! @brief     Defines class DesignerHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DESIGNERHELPER_H
#define DESIGNERHELPER_H

#include "WinDllMacros.h"
#include <QColor>
#include <QGradient>
#include <QGraphicsItem>
#include <QRect>
#include <complex>

//! collection of static methods with SampleDesigner geometry settings
class BA_CORE_API_ DesignerHelper
{
public:
    enum EWidgetTypes {
        IVIEW = QGraphicsItem::UserType + 1, // = 65537
        ISAMPLE_RECT,
        NODE_EDITOR_PORT,
        NODE_EDITOR_CONNECTION,
        MULTILAYER,
        LAYER,
        PARTICLE_LAYOUT,
        INTERFERENCE_FUNCTION,
        INTERFERENCE_FUNCTION_1D_LATTICE,
        INTERFERENCE_FUNCTION_2D_LATTICE,
        INTERFERENCE_FUNCTION_2D_PARA,
        INTERFERENCE_FUNCTION_FINITE_2D_LATTICE,
        INTERFERENCE_FUNCTION_HARD_DISK,
        INTERFERENCE_FUNCTION_RADIAL_PARA,
        PARTICLE,
        TRANSFORMATION,
    };

    static int getDefaultLayerWidth();
    static int getDefaultLayerHeight();
    static QColor getDefaultLayerColor();

    static int getDefaultMultiLayerWidth();
    static int getDefaultMultiLayerHeight();
    static QRectF getDefaultMultiLayerRect();

    static int getDefaultParticleLayoutWidth();
    static int getDefaultParticleLayoutHeight();

    static int getDefaultInterferenceFunctionWidth();
    static int getDefaultInterferenceFunctionHeight();

    static int getDefaultParticleWidth();
    static int getDefaultParticleHeight();
    static QColor getDefaultParticleColor();

    static int getDefaultTransformationWidth();
    static int getDefaultTransformationHeight();
    static QColor getDefaultTransformationColor();

    static int getDefaultMaterialWidth();
    static int getDefaultMaterialHeight();
    static QColor getDefaultMaterialColor();

    static QGradient getLayerGradient(const QColor& color, const QRectF& rect);
    static QGradient getDecorationGradient(const QColor& color, const QRectF& rect);

    static QPixmap getSceneBackground();
    static QPixmap getPixmapLayer();
    static QPixmap getPixmapMultiLayer();
    static QPixmap getPixmapParticleLayout();
    static QPixmap getPixmapInterferenceFunction();
    static QPixmap getPixmapParticle();

    static QColor getRandomColor();

    //! sort graphics item according they y-coordinate
    static bool sort_layers(QGraphicsItem* left, QGraphicsItem* right);

    //! non-linear conversion of layer's thickness in nanometers to screen size
    //! to have reasonable graphics representation of layer in the form of QRect
    static int nanometerToScreen(double nanometer);

    //! returns default bounding rectangle for given IvView name
    static QRectF getDefaultBoundingRect(const QString& name);

    //! returns default color for IView with given name
    static QColor getDefaultColor(const QString& name);

    //! returns Mime pixmap for givew IView name
    static QPixmap getMimePixmap(const QString& name);

    //! returns system dependent font size
    static int getHeaderFontSize();
    static int getSectionFontSize();
    static int getLabelFontSize();
    static int getPortFontSize();
    static int getPythonEditorFontSize();

private:
    static int m_default_layer_height;
    static int m_default_layer_width;
};

typedef std::complex<double> complex_t;
Q_DECLARE_METATYPE(complex_t)

#endif // DESIGNERHELPER_H
