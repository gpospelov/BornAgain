#ifndef COLORPROPERTY_H
#define COLORPROPERTY_H


#include <QMetaType>


//! The ColorProperty for ParameterizedItem and PropertyEditor
class ColorProperty
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

private:
    QColor m_color;
};

Q_DECLARE_METATYPE(ColorProperty)



#endif
