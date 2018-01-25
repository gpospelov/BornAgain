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

#include "SessionItem.h"

class BA_CORE_API_ MaterialDataItem : public SessionItem
{

public:
    static const QString P_REAL;
    static const QString P_IMAG;

    double real() const;
    void setReal(double real);

    double imag() const;
    void setImag(double imag);

protected:
    MaterialDataItem(const QString& modelType);

private:
    void updateLabel();
};

class BA_CORE_API_ MaterialRefractiveDataItem : public MaterialDataItem
{
public:
    MaterialRefractiveDataItem();
};

class BA_CORE_API_ MaterialSLDDataItem : public MaterialDataItem
{
public:
    MaterialSLDDataItem();
};

#endif // MATERIALDATAITEMS_H
