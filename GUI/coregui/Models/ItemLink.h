// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ItemLink.h
//! @brief     Defines class ItemLink
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ITEMLINK_H
#define ITEMLINK_H

#include "SessionItem.h"
#include <QMetaType>
#include <QVariant>

class BA_CORE_API_ ItemLink
{

public:
    explicit ItemLink(const QString property_name = QString(), SessionItem *item = 0);
    virtual ~ItemLink(){}

    QString getPropertyName() const { return m_property_name; }

    SessionItem *getItem() const { return m_item; }
    void setItem(QString property_name, SessionItem *item);

    void setValue(double value);

    void updateItem();

private:
    double getValue() const;
    QVariant getVariant();
    QString m_property_name;
    SessionItem *m_item;
    double m_value;
};

Q_DECLARE_METATYPE(ItemLink)

#endif // ITEMLINK_H


