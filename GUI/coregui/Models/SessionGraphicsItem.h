// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionGraphicsItem.h
//! @brief     Defines class SessionGraphicsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONGRAPHICSITEM_h
#define SESSIONGRAPHICSITEM_h


#include "SessionItem.h"


class BA_CORE_API_ SessionGraphicsItem : public SessionItem
{

public:
    static const QString P_XPOS;
    static const QString P_YPOS;

protected:
    explicit SessionGraphicsItem(const QString &model_type=QString());
};

#endif


