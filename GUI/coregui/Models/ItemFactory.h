// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemFactory.h
//! @brief     Declares class ItemFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QMap>
#include <QStringList>
#include "SessionItem.h"

class BA_CORE_API_ ItemFactory
{
public:
    typedef QMap<QString, SessionItem *(*)()> ItemMap_t;


    //! create SessionItem of specific type and parent
    static SessionItem *createItem(const QString &model_name,
                                         SessionItem *parent=0);

    //! create empty SessionItem that serves as a root item
    static SessionItem *createEmptyItem();

    //! retrieve list of all possible item names
    static QList<QString> getValidTopItemNames();

    //! returns true of factory supports given item type
    static bool isValidItemType(const QString &name);

private:
    static QStringList m_valid_top_item_names;
    static ItemMap_t m_item_map;
    ItemFactory() {}
    ~ItemFactory() {}
};

#endif // ITEMFACTORY_H
