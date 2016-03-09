// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TestItem.h
//! @brief     Defines class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTITEM_H
#define TESTITEM_H

#include "SessionItem.h"

//! The TestItem class for TestSessionItem unit tests and for checking AwesomePropertyEditor machinery
class BA_CORE_API_ TestItem : public SessionItem
{

public:
    static const QString P_DISTRIBUTION;
    static const QString P_VALUE;
    static const QString P_COMBO;
    static const QString P_VECTOR;
    explicit TestItem();
    virtual ~TestItem(){}
};

#endif
