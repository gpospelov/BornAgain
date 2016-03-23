// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MaterialModel.h
//! @brief     Defines class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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

    virtual MaterialModel *createCopy(SessionItem *parent = 0);

    MaterialItem *addMaterial(const QString &name, double delta = 0.0, double beta = 0.0);
    void removeMaterial(MaterialItem *);

    MaterialItem *getMaterial(const QModelIndex &index);
    MaterialItem *getMaterial(const MaterialProperty &property);
    MaterialItem *getMaterial(const QString &material_name);
};

#endif

