#ifndef MATERIALPROPERTIES_H
#define MATERIALPROPERTIES_H


#include "MaterialProperty.h"


namespace MaterialProperties {
const QString RefractiveIndex("Refractive index");
const QString MagneticField("Magnetic field");
const char Color[] = "Color";
const char Name[]  = "Name";
}


//! The MaterialColorProperty class defines color property for MaterialItem to
//! be used from MaterialPropertyBrowser
class MaterialColorProperty
{
public:
    MaterialColorProperty() : m_color(Qt::red) {}
    MaterialColorProperty(QColor color) : m_color(color) {}
    QPixmap getPixmap() const {
        QPixmap pixmap(10,10);
        pixmap.fill(m_color);
        return pixmap;
    }
    QColor getColor() const { return m_color; }
    void setColor(QColor color) { m_color = color; }
    QString getText() const {
        return QString("[%1, %2, %3] (%4)")
               .arg(m_color.red()).arg(m_color.green()).arg(m_color.blue()).arg(m_color.alpha());
    }

private:
    QColor m_color;
};

Q_DECLARE_METATYPE(MaterialColorProperty)




#endif

