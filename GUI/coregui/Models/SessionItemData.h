// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemData.h
//! @brief     Defines class SessionItemData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONITEMDATA_H
#define SESSIONITEMDATA_H

#include "WinDllMacros.h"
#include <QVector>
#include <QVariant>

//! Handles all data roles for SessionItem.

class BA_CORE_API_ SessionItemData
{
public:

    QVector<int> roles() const;

    QVariant data(int role) const;

    bool setData(int role, const QVariant& value);

private:
    class ItemData
    {
    public:
        ItemData(int r = -1, const QVariant& v = QVariant());
        int role;
        QVariant data;
        bool operator==(const ItemData& other) const;
    };

    QVector<ItemData> m_values;
};

#endif //   SESSIONITEMDATA_H
