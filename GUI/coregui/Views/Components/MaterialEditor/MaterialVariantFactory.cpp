#include "MaterialVariantFactory.h"
#include "MaterialVariantManager.h"
#include "MaterialColorPropertyEdit.h"


MaterialVariantFactory::~MaterialVariantFactory()
{
    QList<MaterialColorPropertyEdit *> mat_editors =
            m_material_editor_to_property.keys();
    QListIterator<MaterialColorPropertyEdit *> mat_it(mat_editors);
    while (mat_it.hasNext())
        delete mat_it.next();
}


void MaterialVariantFactory::connectPropertyManager(
        QtVariantPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotPropertyChanged(QtProperty *,
                                               const QVariant &)));
    connect(manager, SIGNAL(attributeChanged(QtProperty *, const QString &,
                                             const QVariant &)),
                this, SLOT(slotPropertyAttributeChanged(QtProperty *,
                                    const QString &, const QVariant &)));
    QtVariantEditorFactory::connectPropertyManager(manager);
}


QWidget *MaterialVariantFactory::createEditor(QtVariantPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    if (manager->propertyType(property) ==
            MaterialVariantManager::materialColorPropertyTypeId()) {
        MaterialColorPropertyEdit *editor = new MaterialColorPropertyEdit(parent);
        QVariant var = manager->value(property);
        MaterialColorProperty mat = var.value<MaterialColorProperty>();
        editor->setMaterialColorProperty(mat);

        m_property_to_material_editors[property].append(editor);
        m_material_editor_to_property[editor] = property;

        connect(editor, SIGNAL(materialColorPropertyChanged(const MaterialColorProperty &)),
                this, SLOT(slotSetValue(const MaterialColorProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }
    return QtVariantEditorFactory::createEditor(manager, property, parent);
}


void MaterialVariantFactory::disconnectPropertyManager(
        QtVariantPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
               this, SLOT(slotPropertyChanged(QtProperty *, const QVariant &)));
    disconnect(manager, SIGNAL(attributeChanged(QtProperty *, const QString &,
                                     const QVariant &)),
                this, SLOT(slotPropertyAttributeChanged(QtProperty *,
                                     const QString &, const QVariant &)));
    QtVariantEditorFactory::disconnectPropertyManager(manager);
}


void MaterialVariantFactory::slotPropertyChanged(QtProperty *property,
                const QVariant &value)
{
    if (m_property_to_material_editors.contains(property)) {
        QList<MaterialColorPropertyEdit *> editors =
                m_property_to_material_editors[property];
        QListIterator<MaterialColorPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            MaterialColorProperty mat = value.value<MaterialColorProperty>();
            itEditor.next()->setMaterialColorProperty(mat);
        }
    }
//    else if (m_property_to_form_factor_editors.contains(property)) {
//        QList<FormFactorPropertyEdit *> editors =
//                m_property_to_form_factor_editors[property];
//        QListIterator<FormFactorPropertyEdit *> itEditor(editors);
//        while (itEditor.hasNext()) {
//            FormFactorProperty mat = value.value<FormFactorProperty>();
//            itEditor.next()->setFormFactorProperty(mat);
//        }
//    }
    return;
}


void MaterialVariantFactory::slotSetValue(const MaterialColorProperty &value)
{
    QObject *object = sender();
    QMap<MaterialColorPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_material_editor_to_property.constBegin();
    while (itEditor != m_material_editor_to_property.constEnd()) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtVariantPropertyManager *manager = propertyManager(property);
            if (!manager) return;
            QVariant var;
            var.setValue(value);
            manager->setValue(property, var);
            return;
        }
        itEditor++;
    }
}


void MaterialVariantFactory::slotEditorDestroyed(QObject *object)
{
    QMap<MaterialColorPropertyEdit *, QtProperty *>::ConstIterator mat_it_editor =
                m_material_editor_to_property.constBegin();
    while (mat_it_editor != m_material_editor_to_property.constEnd()) {
        if (mat_it_editor.key() == object) {
            MaterialColorPropertyEdit *editor = mat_it_editor.key();
            QtProperty *property = mat_it_editor.value();
            m_material_editor_to_property.remove(editor);
            m_property_to_material_editors[property].removeAll(editor);
            if (m_property_to_material_editors[property].isEmpty())
                m_property_to_material_editors.remove(property);
            return;
        }
        mat_it_editor++;
    }
}

