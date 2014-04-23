#include "PropertyVariantFactory.h"
#include "PropertyVariantManager.h"
#include "PropertyBrowserUtils.h"


PropertyVariantFactory::~PropertyVariantFactory()
{
    QList<MaterialPropertyEdit *> mat_editors =
            m_material_editor_to_property.keys();
    QListIterator<MaterialPropertyEdit *> mat_it(mat_editors);
    while (mat_it.hasNext())
        delete mat_it.next();
    QList<FormFactorPropertyEdit *> ff_editors =
            m_form_factor_editor_to_property.keys();
    QListIterator<FormFactorPropertyEdit *> ff_it(ff_editors);
    while (ff_it.hasNext())
        delete ff_it.next();
}

void PropertyVariantFactory::connectPropertyManager(
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


QWidget *PropertyVariantFactory::createEditor(QtVariantPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    if (manager->propertyType(property) ==
            PropertyVariantManager::materialTypeId()) {
        MaterialPropertyEdit *editor = new MaterialPropertyEdit(parent);
        QVariant var = manager->value(property);
        MaterialProperty mat = var.value<MaterialProperty>();
        editor->setMaterialProperty(mat);

        m_property_to_material_editors[property].append(editor);
        m_material_editor_to_property[editor] = property;

        connect(editor, SIGNAL(materialPropertyChanged(const MaterialProperty &)),
                this, SLOT(slotSetValue(const MaterialProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }
    if (manager->propertyType(property) ==
            PropertyVariantManager::formFactorTypeId()) {
        FormFactorPropertyEdit *editor = new FormFactorPropertyEdit(parent);
        QVariant var = manager->value(property);
        FormFactorProperty ff = var.value<FormFactorProperty>();
        editor->setFormFactorProperty(ff);

        m_property_to_form_factor_editors[property].append(editor);
        m_form_factor_editor_to_property[editor] = property;

        connect(editor,
                SIGNAL(formFactorPropertyChanged(const FormFactorProperty &)),
                this, SLOT(slotSetValue(const FormFactorProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }
    return QtVariantEditorFactory::createEditor(manager, property, parent);
}


void PropertyVariantFactory::disconnectPropertyManager(
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


void PropertyVariantFactory::slotPropertyChanged(QtProperty *property,
                const QVariant &value)
{
    if (m_property_to_material_editors.contains(property)) {
        QList<MaterialPropertyEdit *> editors =
                m_property_to_material_editors[property];
        QListIterator<MaterialPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            MaterialProperty mat = value.value<MaterialProperty>();
            itEditor.next()->setMaterialProperty(mat);
        }
    }
    else if (m_property_to_form_factor_editors.contains(property)) {
        QList<FormFactorPropertyEdit *> editors =
                m_property_to_form_factor_editors[property];
        QListIterator<FormFactorPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            FormFactorProperty mat = value.value<FormFactorProperty>();
            itEditor.next()->setFormFactorProperty(mat);
        }
    }
    return;
}


void PropertyVariantFactory::slotSetValue(const MaterialProperty &value)
{
    QObject *object = sender();
    QMap<MaterialPropertyEdit *, QtProperty *>::ConstIterator itEditor =
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

void PropertyVariantFactory::slotSetValue(const FormFactorProperty &value)
{
    QObject *object = sender();
    QMap<FormFactorPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_form_factor_editor_to_property.constBegin();
    while (itEditor != m_form_factor_editor_to_property.constEnd()) {
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


void PropertyVariantFactory::slotEditorDestroyed(QObject *object)
{
    QMap<MaterialPropertyEdit *, QtProperty *>::ConstIterator mat_it_editor =
                m_material_editor_to_property.constBegin();
    while (mat_it_editor != m_material_editor_to_property.constEnd()) {
        if (mat_it_editor.key() == object) {
            MaterialPropertyEdit *editor = mat_it_editor.key();
            QtProperty *property = mat_it_editor.value();
            m_material_editor_to_property.remove(editor);
            m_property_to_material_editors[property].removeAll(editor);
            if (m_property_to_material_editors[property].isEmpty())
                m_property_to_material_editors.remove(property);
            return;
        }
        mat_it_editor++;
    }
    QMap<FormFactorPropertyEdit *, QtProperty *>::ConstIterator ff_it_editor =
                m_form_factor_editor_to_property.constBegin();
    while (ff_it_editor != m_form_factor_editor_to_property.constEnd()) {
        if (ff_it_editor.key() == object) {
            FormFactorPropertyEdit *editor = ff_it_editor.key();
            QtProperty *property = ff_it_editor.value();
            m_form_factor_editor_to_property.remove(editor);
            m_property_to_form_factor_editors[property].removeAll(editor);
            if (m_property_to_form_factor_editors[property].isEmpty())
                m_property_to_form_factor_editors.remove(property);
            return;
        }
        ff_it_editor++;
    }
}

