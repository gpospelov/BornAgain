// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedGraphicsItem.h
//! @brief     Defines class ParameterizedGraphicsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERIZEDGRAPHICSITEM_h
#define PARAMETERIZEDGRAPHICSITEM_h


#include "ParameterizedItem.h"


class BA_CORE_API_ ParameterizedGraphicsItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_XPOS;
    static const QString P_YPOS;

protected:
    explicit ParameterizedGraphicsItem(const QString &model_type=QString());
};

#endif


