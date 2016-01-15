// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MaterialModel.h
//! @brief     Defines class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "SessionModel.h"

class MaterialItem;
class MaterialProperty;

class BA_CORE_API_ MaterialModel : public SessionModel
{
    Q_OBJECT

public:
    explicit MaterialModel(QObject *parent = 0);
    virtual ~MaterialModel(){}

    MaterialItem *addMaterial(const QString &name, double delta = 0.0, double beta = 0.0);
    void removeMaterial(MaterialItem *);

    MaterialItem *getMaterial(const MaterialProperty &property);
    MaterialItem *getMaterial(const QString &material_name);
};

#endif

