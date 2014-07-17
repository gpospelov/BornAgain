#ifndef FIXEDGROUPPROPERTY_H
#define FIXEDGROUPPROPERTY_H

#include "FancyGroupProperty.h"

class FixedGroupProperty : public FancyGroupProperty
{
public:
    FixedGroupProperty() {}
    ~FixedGroupProperty(){}

    virtual GroupType type() const { return FixedGroupType; }

    ParameterizedItem *createCorrespondingItem(const QString &name = QString());

};

#endif
