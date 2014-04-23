#include "MaterialEditor.h"
#include "MaterialEditorWidget.h"
#include <QDebug>

MaterialEditor *MaterialEditor::m_instance = 0;

MaterialEditor::MaterialEditor(MaterialModel *model)
    : m_materialModel(model)
{
    Q_ASSERT(!m_instance);
    m_instance = this;
}


MaterialEditor::~MaterialEditor()
{
    m_instance = 0;
}


MaterialProperty MaterialEditor::getMaterialProperty()
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterialProperty();
}


MaterialProperty MaterialEditor::this_getMaterialProperty()
{
    qDebug() << "MaterialEditor::this_getMaterialProperty()";
    MaterialEditorWidget widget(m_materialModel);
    if(widget.exec() == QDialog::Accepted) {
        return widget.getSelectedMaterialProperty();
    }

    return MaterialProperty();
}
