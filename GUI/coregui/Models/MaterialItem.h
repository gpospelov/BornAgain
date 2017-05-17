// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItem.h
//! @brief     Defines class MaterialItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALITEM_H
#define MATERIALITEM_H

#include "SessionItem.h"

class HomogeneousMaterial;

class BA_CORE_API_ MaterialItem : public SessionItem
{


public:
    static const QString P_COLOR;
    static const QString P_REFRACTIVE_INDEX;
    static const QString P_IDENTIFIER;
    explicit MaterialItem();

    QString getIdentifier() const;
    QColor getColor() const;
    std::unique_ptr<HomogeneousMaterial> createMaterial() const;
};

#endif // MATERIALITEM_H
