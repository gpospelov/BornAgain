// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialDataItems.h
//! @brief     Defines MaterialDataItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALDATAITEMS_H
#define MATERIALDATAITEMS_H

#include "GUI/coregui/Models/SessionItem.h"

class BA_CORE_API_ MaterialDataItem : public SessionItem
{
protected:
    MaterialDataItem(const QString& modelType);
};

class BA_CORE_API_ MaterialRefractiveDataItem : public MaterialDataItem
{
public:
    static const QString P_DELTA;
    static const QString P_BETA;

    MaterialRefractiveDataItem();
};

class BA_CORE_API_ MaterialSLDDataItem : public MaterialDataItem
{
public:
    static const QString P_SLD_REAL;
    static const QString P_SLD_IMAG;

    MaterialSLDDataItem();
};

#endif // MATERIALDATAITEMS_H
