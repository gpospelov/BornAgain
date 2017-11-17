// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentUtis.cpp
//! @brief     Implements ComponentUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentUtils.h"
#include "item_constants.h"

QStringList ComponentUtils::propertyRelatedTypes()
{
    QStringList result = QStringList() << Constants::PropertyType << Constants::GroupItemType
                                       << Constants::VectorType << Constants::BasicAxisType
                                       << Constants::AmplitudeAxisType;
    return result;
}
