// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialSvc.cpp
//! @brief     Implements class MaterialSvc
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialSvc.h"
#include "MaterialEditorDialog.h"
#include "MaterialItem.h"
#include "MaterialModel.h"
#include "MaterialUtils.h"
#include "SessionModel.h"
#include <QDebug>

MaterialSvc *MaterialSvc::m_instance = 0;

MaterialSvc::MaterialSvc(MaterialModel *materialModel)
    : m_materialModel(materialModel)
{
    Q_ASSERT(!m_instance);
    m_instance = this;
}


MaterialSvc::~MaterialSvc()
{
    m_instance = 0;
}

MaterialSvc *MaterialSvc::instance()
{
    return m_instance;
}


MaterialProperty
MaterialSvc::selectMaterialProperty(const MaterialProperty &previousMaterial)
{
    Q_ASSERT(m_instance);
    return m_instance->this_selectMaterialProperty(previousMaterial);
}


MaterialProperty
MaterialSvc::this_selectMaterialProperty(const MaterialProperty &previousMaterial)
{
    MaterialEditorDialog dialog(m_materialModel);
    dialog.setInitialMaterialProperty(previousMaterial);
    if(dialog.exec() == QDialog::Accepted) {
        return dialog.getSelectedMaterialProperty();
    }

    return MaterialProperty();
}


MaterialProperty MaterialSvc::getMaterialProperty(const QString &name)
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterialProperty(name);
}


MaterialProperty MaterialSvc::this_getMaterialProperty(const QString &name)
{
    MaterialItem *material = m_materialModel->getMaterial(name);
    if(material)
        return MaterialProperty(material->getIdentifier());

    return MaterialProperty();
}


MaterialProperty MaterialSvc::getDefaultMaterialProperty()
{
    Q_ASSERT(m_instance);
    return m_instance->this_getDefaultMaterialProperty();
}

//! Returns default MaterialProperty which is the signature of the first
//! MaterialItem in the model.
MaterialProperty MaterialSvc::this_getDefaultMaterialProperty()
{
    Q_ASSERT(m_materialModel);
    if((m_materialModel->rowCount( QModelIndex() ) ) ) {
        QModelIndex firstIndex = m_materialModel->index(0, 0, QModelIndex());
        MaterialItem *material = dynamic_cast<MaterialItem *>(m_materialModel->itemForIndex(firstIndex));
        Q_ASSERT(material);
        return MaterialProperty(material->getIdentifier());
    } else {
        return MaterialProperty();
    }
}


MaterialModel *MaterialSvc::getMaterialModel()
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterialModel();
}

MaterialItem *MaterialSvc::getMaterial(const MaterialProperty &property)
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterial(property);
}


MaterialModel *MaterialSvc::this_getMaterialModel()
{
    return m_materialModel;
}

MaterialItem *MaterialSvc::this_getMaterial(const MaterialProperty &property)
{
    return this_getMaterialModel()->getMaterial(property);
}

