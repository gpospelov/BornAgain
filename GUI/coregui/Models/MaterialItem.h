#ifndef MATERIALITEM_H
#define MATERIALITEM_H


#include <QString>
#include <QStringList>
#include <QColor>
#include <QMap>
#include <QVariant>
#include <QMetaType>
#include <QPixmap>

class QXmlStreamWriter;
class QXmlStreamReader;

#include "MaterialProperty.h"

namespace MaterialProperties {
const QString RefractiveIndex("Refractive index");
const QString MagneticField("Magnetic field");
const char Color[] = "Color";
const char Name[]  = "Name";
}



class MaterialItem : public QObject
{
    Q_OBJECT

public:
    enum MaterialType {
        HomogeneousMaterial,
        HomogeneousMagneticMaterial,
        SubItem
    };

    MaterialItem(const QString &name=QString(), MaterialType type = HomogeneousMaterial);
    ~MaterialItem();
    QString getName() const { return m_name; }
    void setName(const QString &name);
    void setType(MaterialType type);
    void setType(QString typeName);
    MaterialType getType() const { return m_type; }
    QString getTypeName() const { return m_type_names.at(int(m_type)); }

    QStringList getMaterialTypes() const;

    virtual QString getTitleString() { return QString(); }

    QMap<QString, MaterialItem *> getSubItems() const {
        return m_sub_items;
    }

    bool event(QEvent * e );

    void updateProperties();

    bool setMaterialProperty(QString name, const QVariant &value);

    virtual void writeTo(QXmlStreamWriter *writer);

    virtual void writeProperty(QXmlStreamWriter *writer, MaterialItem *item, const char *property_name) const;

    void writeSubProperty(QXmlStreamWriter *writer, MaterialItem *item) const;

    void readFrom(QXmlStreamReader *reader);
    QString readProperty(QXmlStreamReader *reader, MaterialItem *item);

signals:
    void propertyChanged(QString propertyName);
    void propertyItemChanged(QString propertyName);

public slots:
    void onPropertyItemChanged(QString propertyName);

private:
    void addSubProperty(QString name);
    void removeSubProperty(QString name);
    void addColorProperty();

    QString m_name;
    MaterialType m_type;

    static QStringList m_type_names;

    QMap<QString, MaterialItem *> m_sub_items;
};


class RefractiveIndexItem : public MaterialItem
{
    Q_OBJECT

public:
    RefractiveIndexItem() : MaterialItem(MaterialProperties::RefractiveIndex, MaterialItem::SubItem)
    {
        setProperty("delta", QString("1e-3"));
        setProperty("gamma", QString("1e-5"));
    }

    QString getTitleString()
    {

        return QString("(1.0 - %1, %2)").arg(property("delta").toString(), property("gamma").toString());
    }
};


class MagneticFieldProperty : public MaterialItem
{
    Q_OBJECT

public:
    MagneticFieldProperty() : MaterialItem(MaterialProperties::MagneticField, MaterialItem::SubItem)
    {
        setProperty("Bx", 0.0);
        setProperty("By", 0.0);
        setProperty("Bz", 0.0);
    }

    QString getTitleString()
    {

        return QString("(%1, %2, %3)").arg(property("Bx").toString(), property("By").toString(), property("Bz").toString());
    }
};


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
