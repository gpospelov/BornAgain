// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialModel.h
//! @brief     Defines class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "SessionModel.h"

class MaterialItem;
class ExternalProperty;

class BA_CORE_API_ MaterialModel : public SessionModel
{
    Q_OBJECT

public:
    explicit MaterialModel(QObject* parent = 0);
    ~MaterialModel();

    virtual MaterialModel* createCopy(SessionItem* parent = 0);

    MaterialItem* addMaterial(const QString& name, double material_data_real = 0.0, double material_data_imag = 0.0);
    void removeMaterial(MaterialItem*);

    MaterialItem* getMaterial(const QModelIndex& index);

    MaterialItem* cloneMaterial(const QModelIndex& index);

    MaterialItem* materialFromName(const QString& material_name);
    MaterialItem* materialFromIdentifier(const QString& identifier);
};

#endif // MATERIALMODEL_H

