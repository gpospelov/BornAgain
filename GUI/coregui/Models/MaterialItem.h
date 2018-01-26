// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItem.h
//! @brief     Defines class MaterialItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALITEM_H
#define MATERIALITEM_H

#include "SessionItem.h"

class Material;

class BA_CORE_API_ MaterialItem : public SessionItem
{
public:
    static const QString P_COLOR;
    static const QString P_MATERIAL_DATA;
    static const QString P_MAGNETIZATION;
    static const QString P_IDENTIFIER;
    MaterialItem();

    void setRefractiveData(double delta, double beta);
    void setSLDData(double sld, double abs_term);

    QString getIdentifier() const;
    QColor getColor() const;
    std::unique_ptr<Material> createMaterial() const;
};

#endif // MATERIALITEM_H
