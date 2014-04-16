#ifndef MATERIALITEM_H
#define MATERIALITEM_H

#include <QString>
#include <QStringList>
#include <QColor>
#include <QMap>
#include <QVariant>
#include <QMetaType>


class MaterialPropertyItem : public QObject
{
    Q_OBJECT
};

class MaterialItem : public QObject
{
    Q_OBJECT

public:
    enum MaterialType {
        HomogeneousMaterial,
        HomogeneousMagneticMaterial,
        NonExisting
    };

    MaterialItem(const QString &name, MaterialType type);
    ~MaterialItem(){}
    void setName(const QString &name) { m_name = name;}
    QString getName() const { return m_name; }
    void setType(MaterialType type);
    MaterialType getType() const { return m_type; }
    QString getTypeName() const { return m_type_names.at(int(m_type)); }
    QStringList getTypeNames() const { return m_type_names; }

    virtual QString getTitleString() { return QString(); }

    void setColor(const QColor color) { m_color = color; }
    QColor getColor() const { return m_color;}

    QMap<QString, MaterialItem *> getSubItems() const {
        return m_sub_items;
    }

    bool event(QEvent * e );

    void updateProperties();

    void addRefractiveIndexProperty();
    void removeRefractiveIndexProperty();


    bool setMaterialProperty(QString name, const QVariant &value);

signals:
    void propertyChanged(QString propertyName);
    void propertyItemChanged(QString propertyName);

public slots:
    void onPropertyItemChanged(QString propertyName);

private:
    QString m_name;
    MaterialType m_type;
    QColor m_color;

    static QStringList m_type_names;

    QMap<QString, MaterialItem *> m_sub_items;
};


class RefractiveIndexItem : public MaterialItem
{
    Q_OBJECT

public:
    RefractiveIndexItem() : MaterialItem("Refractive index", MaterialItem::NonExisting)
    //RefractiveIndexItem()
    {
        setProperty("delta", QString("1e-3"));
        setProperty("gamma", QString("1e-5"));
    }

    QString getTitleString()
    {

        return QString("(%1, %2)").arg(property("delta").toString(), property("gamma").toString());
    }

};

//Q_DECLARE_METATYPE(RefractiveIndexItem)




#endif
