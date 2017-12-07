// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ObsoletePropertyVariantFactory.cpp
//! @brief     Implements class ObsoletePropertyVariantFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoletePropertyVariantFactory.h"
#include "ObsoletePropertyBrowserUtils.h"
#include "ObsoletePropertyVariantManager.h"

ObsoletePropertyVariantFactory::~ObsoletePropertyVariantFactory()
{
    QList<ObsoleteMaterialPropertyEdit *> mat_editors =
            m_material_editor_to_property.keys();
    QListIterator<ObsoleteMaterialPropertyEdit *> mat_it(mat_editors);
    while (mat_it.hasNext())
        delete mat_it.next();

    QList<ObsoleteColorPropertyEdit *> color_editors =
            m_color_editor_to_property.keys();
    QListIterator<ObsoleteColorPropertyEdit *> color_it(color_editors);
    while (color_it.hasNext())
        delete color_it.next();

    QList<ObsoleteScientificDoublePropertyEdit *> scdouble_editors =
            m_scdouble_editor_to_property.keys();
    QListIterator<ObsoleteScientificDoublePropertyEdit *> scdouble_it(scdouble_editors);
    while (scdouble_it.hasNext())
        delete scdouble_it.next();

    QList<ObsoleteGroupPropertyEdit *> fancy_editors =
            m_fancygroup_editor_to_property.keys();
    QListIterator<ObsoleteGroupPropertyEdit *> fancy_it(fancy_editors);
    while (fancy_it.hasNext())
        delete fancy_it.next();

    QList<ObsoleteComboPropertyEdit *> combo_editors =
            m_combo_editor_to_property.keys();
    QListIterator<ObsoleteComboPropertyEdit *> combo_it(combo_editors);
    while (combo_it.hasNext())
        delete combo_it.next();
}

void ObsoletePropertyVariantFactory::connectPropertyManager(
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


QWidget *ObsoletePropertyVariantFactory::createEditor(QtVariantPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    if (manager->propertyType(property) ==
            ObsoletePropertyVariantManager::materialTypeId()) {
        ObsoleteMaterialPropertyEdit *editor = new ObsoleteMaterialPropertyEdit(parent);
        QVariant var = manager->value(property);
        ExternalProperty mat = var.value<ExternalProperty>();
        editor->setMaterialProperty(mat);

        m_property_to_material_editors[property].append(editor);
        m_material_editor_to_property[editor] = property;

        connect(editor, SIGNAL(materialPropertyChanged(const ExternalProperty &)),
                this, SLOT(slotSetValue(const ExternalProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    if (manager->propertyType(property) ==
            ObsoletePropertyVariantManager::colorPropertyTypeId()) {
        ObsoleteColorPropertyEdit *editor = new ObsoleteColorPropertyEdit(parent);
        QVariant var = manager->value(property);
        ObsoleteColorProperty mat = var.value<ObsoleteColorProperty>();
        editor->setColorProperty(mat);

        m_property_to_color_editors[property].append(editor);
        m_color_editor_to_property[editor] = property;

        connect(editor, SIGNAL(colorPropertyChanged(const ObsoleteColorProperty &)),
                this, SLOT(slotSetValue(const ObsoleteColorProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    if (manager->propertyType(property) ==
            ObsoletePropertyVariantManager::scientificDoubleTypeId()) {
        ObsoleteScientificDoublePropertyEdit *editor = new ObsoleteScientificDoublePropertyEdit(parent);
        QVariant var = manager->value(property);
        ObsoleteScientificDoubleProperty sc = var.value<ObsoleteScientificDoubleProperty>();
        editor->setScientificDoubleProperty(sc);

        m_property_to_scdouble_editors[property].append(editor);
        m_scdouble_editor_to_property[editor] = property;

        connect(editor,
                SIGNAL(scientificDoublePropertyChanged(const ObsoleteScientificDoubleProperty &)),
                this, SLOT(slotSetValue(const ObsoleteScientificDoubleProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    if (manager->propertyType(property) ==
            ObsoletePropertyVariantManager::fancyGroupTypeId()) {
        ObsoleteGroupPropertyEdit *editor = new ObsoleteGroupPropertyEdit(parent);
        QVariant var = manager->value(property);
        ObsoleteGroupProperty_t ff = var.value<ObsoleteGroupProperty_t>();
        editor->setGroupProperty(ff);

        m_property_to_fancygroup_editors[property].append(editor);
        m_fancygroup_editor_to_property[editor] = property;

        connect(editor,
                SIGNAL(groupPropertyChanged(ObsoleteGroupProperty_t)),
                this, SLOT(slotSetValue(ObsoleteGroupProperty_t)));

        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    if (manager->propertyType(property) ==
            ObsoletePropertyVariantManager::comboPropertyTypeId()) {
        ObsoleteComboPropertyEdit *editor = new ObsoleteComboPropertyEdit(parent);

        QVariant var = manager->value(property);
        ComboProperty combo = var.value<ComboProperty>();
        editor->setComboProperty(combo);

        m_property_to_combo_editors[property].append(editor);
        m_combo_editor_to_property[editor] = property;

        connect(editor, SIGNAL(comboPropertyChanged(const ComboProperty &)),
                this, SLOT(slotSetValue(const ComboProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    return QtVariantEditorFactory::createEditor(manager, property, parent);
}


void ObsoletePropertyVariantFactory::disconnectPropertyManager(
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


void ObsoletePropertyVariantFactory::slotPropertyChanged(QtProperty *property,
                const QVariant &value)
{
    if (m_property_to_material_editors.contains(property)) {
        QList<ObsoleteMaterialPropertyEdit *> editors =
                m_property_to_material_editors[property];
        QListIterator<ObsoleteMaterialPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            ExternalProperty mat = value.value<ExternalProperty>();
            itEditor.next()->setMaterialProperty(mat);
        }
    }
    else if (m_property_to_color_editors.contains(property)) {
        QList<ObsoleteColorPropertyEdit *> editors =
                m_property_to_color_editors[property];
        QListIterator<ObsoleteColorPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            ObsoleteColorProperty mat = value.value<ObsoleteColorProperty>();
            itEditor.next()->setColorProperty(mat);
        }
    }
    else if (m_property_to_scdouble_editors.contains(property)) {
        QList<ObsoleteScientificDoublePropertyEdit *> editors =
                m_property_to_scdouble_editors[property];
        QListIterator<ObsoleteScientificDoublePropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            ObsoleteScientificDoubleProperty mat = value.value<ObsoleteScientificDoubleProperty>();
            itEditor.next()->setScientificDoubleProperty(mat);
        }
    }
    else if (m_property_to_fancygroup_editors.contains(property)) {
        QList<ObsoleteGroupPropertyEdit *> editors =
                m_property_to_fancygroup_editors[property];
        QListIterator<ObsoleteGroupPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            ObsoleteGroupProperty_t mat = value.value<ObsoleteGroupProperty_t>();
            itEditor.next()->setGroupProperty(mat);
        }
    }
    else if (m_property_to_combo_editors.contains(property)) {
        QList<ObsoleteComboPropertyEdit *> editors =
                m_property_to_combo_editors[property];
        QListIterator<ObsoleteComboPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            ComboProperty combo = value.value<ComboProperty>();
            itEditor.next()->setComboProperty(combo);
        }
    }
}


void ObsoletePropertyVariantFactory::slotSetValue(const ExternalProperty &value)
{
    QObject *object = sender();
    QMap<ObsoleteMaterialPropertyEdit *, QtProperty *>::ConstIterator itEditor =
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

void ObsoletePropertyVariantFactory::slotSetValue(const ObsoleteColorProperty &value)
{
    QObject *object = sender();
    QMap<ObsoleteColorPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_color_editor_to_property.constBegin();
    while (itEditor != m_color_editor_to_property.constEnd()) {
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

void ObsoletePropertyVariantFactory::slotSetValue(const ObsoleteScientificDoubleProperty &value)
{
    QObject *object = sender();
    QMap<ObsoleteScientificDoublePropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_scdouble_editor_to_property.constBegin();
    while (itEditor != m_scdouble_editor_to_property.constEnd()) {
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

void ObsoletePropertyVariantFactory::slotSetValue(const ObsoleteGroupProperty_t &value)
{
    QObject *object = sender();
    QMap<ObsoleteGroupPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_fancygroup_editor_to_property.constBegin();
    while (itEditor != m_fancygroup_editor_to_property.constEnd()) {
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

void ObsoletePropertyVariantFactory::slotSetValue(const ComboProperty &value)
{
    QObject *object = sender();
    QMap<ObsoleteComboPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_combo_editor_to_property.constBegin();
    while (itEditor != m_combo_editor_to_property.constEnd()) {
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

void ObsoletePropertyVariantFactory::slotEditorDestroyed(QObject *object)
{
    QMap<ObsoleteMaterialPropertyEdit *, QtProperty *>::ConstIterator mat_it_editor =
                m_material_editor_to_property.constBegin();
    while (mat_it_editor != m_material_editor_to_property.constEnd()) {
        if (mat_it_editor.key() == object) {
            ObsoleteMaterialPropertyEdit *editor = mat_it_editor.key();
            QtProperty *property = mat_it_editor.value();
            m_material_editor_to_property.remove(editor);
            m_property_to_material_editors[property].removeAll(editor);
            if (m_property_to_material_editors[property].isEmpty())
                m_property_to_material_editors.remove(property);
            return;
        }
        mat_it_editor++;
    }

    QMap<ObsoleteColorPropertyEdit *, QtProperty *>::ConstIterator color_it_editor =
                m_color_editor_to_property.constBegin();
    while (color_it_editor != m_color_editor_to_property.constEnd()) {
        if (color_it_editor.key() == object) {
            ObsoleteColorPropertyEdit *editor = color_it_editor.key();
            QtProperty *property = color_it_editor.value();
            m_color_editor_to_property.remove(editor);
            m_property_to_color_editors[property].removeAll(editor);
            if (m_property_to_color_editors[property].isEmpty())
                m_property_to_color_editors.remove(property);
            return;
        }
        color_it_editor++;
    }

    QMap<ObsoleteScientificDoublePropertyEdit *, QtProperty *>::ConstIterator scdouble_it_editor =
                m_scdouble_editor_to_property.constBegin();
    while (scdouble_it_editor != m_scdouble_editor_to_property.constEnd()) {
        if (scdouble_it_editor.key() == object) {
            ObsoleteScientificDoublePropertyEdit *editor = scdouble_it_editor.key();
            QtProperty *property = scdouble_it_editor.value();
            m_scdouble_editor_to_property.remove(editor);
            m_property_to_scdouble_editors[property].removeAll(editor);
            if (m_property_to_scdouble_editors[property].isEmpty())
                m_property_to_scdouble_editors.remove(property);
            return;
        }
        scdouble_it_editor++;
    }

    QMap<ObsoleteGroupPropertyEdit *, QtProperty *>::ConstIterator fancygroup_editor_it =
                m_fancygroup_editor_to_property.constBegin();
    while (fancygroup_editor_it != m_fancygroup_editor_to_property.constEnd()) {
        if (fancygroup_editor_it.key() == object) {
            ObsoleteGroupPropertyEdit *editor = fancygroup_editor_it.key();
            QtProperty *property = fancygroup_editor_it.value();
            m_fancygroup_editor_to_property.remove(editor);
            m_property_to_fancygroup_editors[property].removeAll(editor);
            if (m_property_to_fancygroup_editors[property].isEmpty())
                m_property_to_fancygroup_editors.remove(property);
            return;
        }
        fancygroup_editor_it++;
    }

    QMap<ObsoleteComboPropertyEdit *, QtProperty *>::ConstIterator combo_it_editor =
                m_combo_editor_to_property.constBegin();
    while (combo_it_editor != m_combo_editor_to_property.constEnd()) {
        if (combo_it_editor.key() == object) {
            ObsoleteComboPropertyEdit *editor = combo_it_editor.key();
            QtProperty *property = combo_it_editor.value();
            m_combo_editor_to_property.remove(editor);
            m_property_to_combo_editors[property].removeAll(editor);
            if (m_property_to_combo_editors[property].isEmpty())
                m_property_to_combo_editors.remove(property);
            return;
        }
        combo_it_editor++;
    }
}

void ObsoletePropertyVariantFactory::slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &)
{

}

