// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/IconProvider.h
//! @brief     Declares class IconProvider
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include "WinDllMacros.h"
#include <QIcon>
#include <QString>

class SessionItem;

//! Class which returns icons for SessionItems to use in SessionModel
class BA_CORE_API_ IconProvider
{
public:
    IconProvider(){}
    virtual ~IconProvider(){}

    virtual QIcon icon(const SessionItem *item);

};


#endif // ICONPROVIDER_H

