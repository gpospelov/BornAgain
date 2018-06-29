// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataPresentationProperties.h
//! @brief     Defines class DataPresentationProperties and its descendants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATAPRESENTATIONPROPERTIES_H
#define DATAPRESENTATIONPROPERTIES_H

#include "SessionItem.h"

class DataItem;

//! Implements a link to DataItem. If path name
//! of a DataItem changes, the link becomes invalid.
//! Also serves as a base for Data1DPresentationProperties
class BA_CORE_API_ DataPresentationProperties : public SessionItem
{
public:
   static const QString P_LINK;

   void setDataItem(DataItem* item);
   DataItem* dataItem();

protected:
   DataPresentationProperties(const QString& model_type);
};

//! Holds data required for 1D DataItem representation
class BA_CORE_API_ Data1DPresentationProperties : public DataPresentationProperties
{
public:
    static const QString P_COLOR;

    Data1DPresentationProperties();
};

#endif // DATAPRESENTATIONPROPERTIES_H
