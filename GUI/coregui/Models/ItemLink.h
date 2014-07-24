#ifndef ITEMLINK_H
#define ITEMLINK_H

#include <ParameterizedItem.h>
#include <QMetaType>


class ItemLink
{

public:
    explicit ItemLink(const QString name = QString(), ParameterizedItem *item = 0);
    virtual ~ItemLink(){}

    QString getName() const { return m_name; }

    ParameterizedItem *getItem() const { return m_item; }
    void setItem(QString name, ParameterizedItem *item);

private:
    QString m_name;
    ParameterizedItem *m_item;

};

Q_DECLARE_METATYPE(ItemLink)

#endif // ITEMLINK_H


