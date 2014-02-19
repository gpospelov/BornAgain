// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterizedItem.h
//! @brief     Defines class ParameterizedItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterizedItem.h"
#include "Exceptions.h"



ParameterizedItem::ParameterizedItem(const QString &name)
    : QStandardItem(name)
{
}

ParameterizedItem::~ParameterizedItem()
{
}

double ParameterizedItem::getParameterValue(QString name)
{
    if (!m_parameters.contains(name)) {
        throw Exceptions::RuntimeErrorException("ParameterizedItem::getParameterValue: "
                                                "parameter does not exist");
    }
    return m_parameters[name];
}

void ParameterizedItem::setParameter(QString name, double value)
{
    if (!m_parameters.contains(name)) {
        throw Exceptions::RuntimeErrorException("ParameterizedItem::getParameterValue: "
                                                "parameter does not exist");
    }
    m_parameters[name] = value;
}

bool ParameterizedItem::acceptsAsChild(ParameterizedItem *child)
{
    return child->isValidParent(this->text());
}

bool ParameterizedItem::isValidParent(QString parentName)
{
    return m_valid_parents.contains(parentName);
}

