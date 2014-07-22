#include "MaterialEditor.h"
#include "MaterialEditorWidget.h"
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
    MaterialEditorWidget widget(m_materialModel);
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
    Q_ASSERT(0);
//    MaterialItem *material = m_materialModel->getMaterial(name);
//    if(material)
//        return MaterialUtils::getMaterialProperty(material);

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
    Q_ASSERT(m_materialModel->rowCount( QModelIndex() ));
    QModelIndex firstIndex = m_materialModel->index(0, 0, QModelIndex());
    MaterialItem *material = dynamic_cast<MaterialItem *>(m_materialModel->itemForIndex(firstIndex));
    return MaterialProperty(material->getIdentifier());
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

