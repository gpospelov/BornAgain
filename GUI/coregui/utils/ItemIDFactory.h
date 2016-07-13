// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/ItemIDFactory.h
//! @brief     Declares class ItemIDFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMIDFACTORY_H
#define ITEMIDFACTORY_H

#include <QUuid>
#include <QMap>

class SessionItem;

class ItemIDFactory {
public:
    // delete copy/move constructor/assignment:
    ItemIDFactory(const ItemIDFactory&) = delete;
    ItemIDFactory(ItemIDFactory&&) = delete;
    ItemIDFactory& operator=(const ItemIDFactory&) = delete;
    ItemIDFactory& operator=(ItemIDFactory&&) = delete;

    static ItemIDFactory& instance();

    static QString createID(SessionItem* toBeInsertedItem);

    static QString getID(SessionItem* existingItem);

    static SessionItem* getItem(QString existingID);

    static int IDSize();

private:
    ItemIDFactory() = default;

    QMap<QString, SessionItem*> IDtoItemMap;
    QMap<SessionItem*, QString> ItemtoIDMap;
};

#endif // ITEMIDFACTORY_H
