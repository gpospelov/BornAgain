// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditor.cpp
//! @brief     Implements class MaterialEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaterialEditor.h"
#include "MaterialEditorDialog.h"
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "MaterialUtils.h"
#include "SessionModel.h"
#include <QDebug>

MaterialEditor *MaterialEditor::m_instance = 0;

MaterialEditor::MaterialEditor(MaterialModel *materialModel)
    : m_materialModel(materialModel)
{
    Q_ASSERT(!m_instance);
    m_instance = this;
}


MaterialEditor::~MaterialEditor()
{
    m_instance = 0;
}

MaterialEditor *MaterialEditor::instance()
{
    return m_instance;
}


MaterialProperty MaterialEditor::selectMaterialProperty()
{
    Q_ASSERT(m_instance);
    return m_instance->this_selectMaterialProperty();
}


MaterialProperty MaterialEditor::this_selectMaterialProperty()
{
    qDebug() << "MaterialEditor::this_getMaterialProperty()";
    MaterialEditorDialog widget(m_materialModel);
    if(widget.exec() == QDialog::Accepted) {
        return widget.getSelectedMaterialProperty();
    }

    return MaterialProperty();
}


MaterialProperty MaterialEditor::getMaterialProperty(const QString &name)
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterialProperty(name);
}


MaterialProperty MaterialEditor::this_getMaterialProperty(const QString &name)
{
    MaterialItem *material = m_materialModel->getMaterial(name);
    if(material)
        return MaterialProperty(material->getIdentifier());

    return MaterialProperty();
}


MaterialProperty MaterialEditor::getDefaultMaterialProperty()
{
    Q_ASSERT(m_instance);
    return m_instance->this_getDefaultMaterialProperty();
}

//! Returns default MaterialProperty which is the signature of the first
//! MaterialItem in the model.
MaterialProperty MaterialEditor::this_getDefaultMaterialProperty()
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


MaterialModel *MaterialEditor::getMaterialModel()
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterialModel();
}


MaterialModel *MaterialEditor::this_getMaterialModel()
{
    return m_materialModel;
}

