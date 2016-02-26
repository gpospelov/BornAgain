// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ItemFactory.h
//! @brief     Defines class ItemFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QMap>
#include <QStringList>
#include "ParameterizedItem.h"

class BA_CORE_API_ ItemFactory
{
public:
    typedef QMap<QString, ParameterizedItem *(*)()> ItemMap_t;


    //! create ParameterizedItem of specific type and parent
    static ParameterizedItem *createItem(const QString &model_name,
                                         ParameterizedItem *parent=0);

    //! create empty ParameterizedItem that serves as a root item
    static ParameterizedItem *createEmptyItem();

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
