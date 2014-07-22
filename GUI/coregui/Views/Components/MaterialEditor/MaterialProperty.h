#ifndef MATERIALPROPERTY_H
#define MATERIALPROPERTY_H

#include <QColor>
#include <QPixmap>
#include <QMetaType>
#include <QString>
#include <QVariant>


//! The MaterialProperty class defines unique identifier to help LayerItem, ParticleItem etc
//! to access materials from MaterialEditor;
class MaterialProperty
{
public:
    MaterialProperty(const QString &identifier=QString())
        : m_identifier(identifier){}

    QString getIdentifier() const {
        return m_identifier;
    }

    QVariant getVariant() const
    {
        QVariant variant;
        variant.setValue(*this);
        return variant;
    }

    QString getName() const;
    QColor getColor() const;
    QPixmap getPixmap() const;

    bool isDefined() const;

private:
    QString m_identifier;
};

Q_DECLARE_METATYPE(MaterialProperty)


////! The MaterialProperty defines material property (name,color) to be used
////! in LayerView, FormFactorView together with SamplePropertyEditor
//class MaterialProperty
//{
//public:
//    MaterialProperty() : m_name("Undefined"), m_color(Qt::red){}
//    MaterialProperty(const QString &name, const QColor &color) : m_name(name), m_color(color){}
//    virtual ~MaterialProperty(){}
//    QString getName() const { return m_name; }
//    QColor getColor() const { return m_color; }
//    QPixmap getPixmap() const {
//        QPixmap pixmap(10,10);
//        pixmap.fill(getColor());
//        return pixmap;
//    }
//    void setName(const QString &name) { m_name = name; }
//    void setColor(const QColor &color) { m_color = color; }
//    bool operator!=(const MaterialProperty &other) {
//        return getName() != other.getName();
//    }
//    bool isDefined() { return m_name != QStringLiteral("Undefined"); }
//private:
//    QString m_name;
//    QColor m_color;
//};


#endif // MATERIALPROPERTY_H
