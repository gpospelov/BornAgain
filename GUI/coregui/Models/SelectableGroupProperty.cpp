#include "SelectableGroupProperty.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"
#include <QDebug>



//void SelectableGroupProperty::setValue(const QString &value)
//{
//    qDebug() << "SelectableGroupProperty::setValue() -> " << value;
//    if(value == getValue()) return;

//    FancyGroupProperty::setValue(value);

//    if(m_parent) {
//        m_parent->addPropertyItem(getGroupName(), createCorrespondingItem());
//        emit m_parent->propertyItemChanged(getGroupName());
//    }
//}

