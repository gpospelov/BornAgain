#ifndef MATERIALPROPERTY_H
#define MATERIALPROPERTY_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QPixmap>


//! The MaterialProperty defines material property (name,color) to be used
//! in LayerView, FormFactorView together with SamplePropertyEditor
class MaterialProperty
{
public:
    MaterialProperty() : m_name("Undefined"), m_color(Qt::red){}
    virtual ~MaterialProperty(){}
    QString getName() const { return m_name; }
    QColor getColor() const { return m_color; }
    QPixmap getPixmap() const {
        QPixmap pixmap(10,10);
        pixmap.fill(getColor());
        return pixmap;
    }
    void setName(const QString &name) { m_name = name; }
    void setColor(const QColor &color) { m_color = color; }
private:
    QString m_name;
    QColor m_color;
};

Q_DECLARE_METATYPE(MaterialProperty)

#endif // MATERIALPROPERTY_H
