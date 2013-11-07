#ifndef MATERIALPROPERTY_H
#define MATERIALPROPERTY_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QPixmap>
#include <QMetaType>

#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif


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
    bool operator!=(const MaterialProperty &other) { return getName() != other.getName();}
    bool isDefined() { return m_name != QStringLiteral("Undefined"); }
private:
    QString m_name;
    QColor m_color;
};

Q_DECLARE_METATYPE(MaterialProperty)

#endif // MATERIALPROPERTY_H
