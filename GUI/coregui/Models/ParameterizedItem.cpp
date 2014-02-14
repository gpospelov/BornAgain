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



ParameterizedItem::ParameterizedItem(BA_MODEL_ID::Model_ID model_type,
                                     const QString &name)
    : QStandardItem(name)
    , m_model_type(model_type)
{
    populateWithParameters();
}

ParameterizedItem::~ParameterizedItem()
{

}

void ParameterizedItem::setParameter(QString name, double value)
{
    if (m_parameters.contains(name)) {
        m_parameters[name] = value;
    }
}

void ParameterizedItem::populateWithParameters()
{
    m_parameters[QString("firstparam")] = 5.0;
    m_parameters[QString("anotherparam")] = 6.0;
    m_parameters[QString("lastparam")] = 7.0;
}
