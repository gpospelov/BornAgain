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
#include "SessionModel.h"
#include "AppSvc.h"

MaterialSvc *MaterialSvc::m_instance = 0;

MaterialSvc::MaterialSvc()
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
    MaterialEditorDialog dialog(AppSvc::materialModel());
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
    MaterialItem *material = AppSvc::materialModel()->getMaterial(name);
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
    if((AppSvc::materialModel()->rowCount( QModelIndex() ) ) ) {
        QModelIndex firstIndex = AppSvc::materialModel()->index(0, 0, QModelIndex());
        MaterialItem *material = dynamic_cast<MaterialItem *>(AppSvc::materialModel()->itemForIndex(firstIndex));
        Q_ASSERT(material);
        return MaterialProperty(material->getIdentifier());
    } else {
        return MaterialProperty();
    }
}


MaterialItem *MaterialSvc::getMaterial(const MaterialProperty &property)
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterial(property);
}


MaterialItem *MaterialSvc::this_getMaterial(const MaterialProperty &property)
{
    return AppSvc::materialModel()->getMaterial(property);
}

