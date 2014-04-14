#ifndef MATERIALITEM_H
#define MATERIALITEM_H

#include <QString>
#include <QStringList>

class MaterialItem : public QObject
{
    Q_OBJECT

public:
    enum MaterialType {
        HomogeneousMaterial,
        HomogeneousMagneticMaterial
    };

    explicit MaterialItem(const QString &name, MaterialType type);
    ~MaterialItem(){}
    void setName(const QString &name) { m_name = name;}
    QString getName() const { return m_name; }
    void setType(MaterialType type) { m_type = type; }
    MaterialType getType() const { return m_type; }
    QString getTypeName() const { return m_type_names.at(int(m_type)); }

private:
    QString m_name;
    MaterialType m_type;
    static QStringList m_type_names;
};





#endif
