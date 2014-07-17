#include "FixedGroupProperty.h"
#include "ItemFactory.h"

ParameterizedItem *FixedGroupProperty::createCorrespondingItem(const QString & /* name */)
{
    ParameterizedItem *result = ItemFactory::createItem(getGroupName());
    setValueLabel(result->getItemLabel());
    return result;
}
