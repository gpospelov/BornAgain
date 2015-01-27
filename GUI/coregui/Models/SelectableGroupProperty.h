// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SelectableGroupProperty.h
//! @brief     Defines class SelectableGroupProperty
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SELECTABLEGROUPPROPERTY_H
#define SELECTABLEGROUPPROPERTY_H

#include "FancyGroupProperty.h"
#include <QStringList>

class BA_CORE_API_ SelectableGroupProperty : public FancyGroupProperty
{
public:

//    SelectableGroupProperty() {}
//    ~SelectableGroupProperty(){}

//    virtual GroupType type() const { return SelectableGroupType; }

//    void setValue(const QString &value);

private:
};


Q_DECLARE_METATYPE(SelectableGroupProperty*)



#endif
