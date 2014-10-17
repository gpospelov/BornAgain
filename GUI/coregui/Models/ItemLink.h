#ifndef ITEMLINK_H
#define ITEMLINK_H

#include <ParameterizedItem.h>
#include <QMetaType>
#include <QVariant>

class BA_CORE_API_ ItemLink
{

public:
    explicit ItemLink(const QString name = QString(), ParameterizedItem *item = 0);
    virtual ~ItemLink(){}

    QString getPropertyName() const { return m_name; }

    ParameterizedItem *getItem() const { return m_item; }
    void setItem(QString name, ParameterizedItem *item);

    void setValue(double value);

    void updateItem();

private:
    double getValue() const;
    QVariant getVariant();
    QString m_name;
    ParameterizedItem *m_item;
    double m_value;
};

Q_DECLARE_METATYPE(ItemLink)

#endif // ITEMLINK_H


