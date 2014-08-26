#ifndef COLORPROPERTY_H
#define COLORPROPERTY_H

#include "WinDllMacros.h"
#include <QMetaType>
#include <QColor>
#include <QPixmap>
#include <QVariant>

//! The ColorProperty for ParameterizedItem and PropertyEditor
//!
//! The reason is to have simple color editor in PropertyEditor instead of
//! original one which is too sophisticated.
class BA_CORE_API_ ColorProperty
{
public:
    ColorProperty() : m_color(Qt::red) {}
    ColorProperty(QColor color) : m_color(color) {}
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

    QVariant getVariant() const
    {
        QVariant variant;
        variant.setValue(*this);
        return variant;
    }

private:
    QColor m_color;
};

Q_DECLARE_METATYPE(ColorProperty)



#endif
