// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ItemFactory.h
//! @brief     Defines class ItemFactory.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "ParameterizedItem.h"

class ItemFactory
{
public:
    //! create ParameterizedItem of specific type and parent
    static ParameterizedItem *createItem(const QString &model_name,
                                         ParameterizedItem *parent=0);

    //! create empty ParameterizedItem that serves as a root item
    static ParameterizedItem *createEmptyItem();

    //! retrieve list of all possible item names
    static QList<QString> getAllItemNames();

    //! returns true if item with given name can be created
    static bool isValidName(const QString &name);

private:
    static QList<QString> m_all_item_names;
    ItemFactory() {}
    ~ItemFactory() {}
};

#endif // ITEMFACTORY_H
