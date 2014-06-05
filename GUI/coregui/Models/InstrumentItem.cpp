#include "InstrumentItem.h"

InstrumentItem::InstrumentItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Instrument"), parent)
{
    setItemName("Instrument");
    m_valid_children.append(QString("Beam"));
    m_valid_children.append(QString("Detector"));
}
