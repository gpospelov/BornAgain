// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyVariantFactory.cpp
//! @brief     Implements class PropertyVariantFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PropertyVariantFactory.h"
#include "PropertyBrowserUtils.h"
#include "PropertyVariantManager.h"
#include <QDebug>


PropertyVariantFactory::~PropertyVariantFactory()
{
//    qDebug() << "PropertyVariantFactory::~PropertyVariantFactory()";
    QList<MaterialPropertyEdit *> mat_editors =
            m_material_editor_to_property.keys();
    QListIterator<MaterialPropertyEdit *> mat_it(mat_editors);
    while (mat_it.hasNext())
        delete mat_it.next();

    QList<ColorPropertyEdit *> color_editors =
            m_color_editor_to_property.keys();
    QListIterator<ColorPropertyEdit *> color_it(color_editors);
    while (color_it.hasNext())
        delete color_it.next();

    QList<ScientificDoublePropertyEdit *> scdouble_editors =
            m_scdouble_editor_to_property.keys();
    QListIterator<ScientificDoublePropertyEdit *> scdouble_it(scdouble_editors);
    while (scdouble_it.hasNext())
        delete scdouble_it.next();

    QList<GroupPropertyEdit *> fancy_editors =
            m_fancygroup_editor_to_property.keys();
    QListIterator<GroupPropertyEdit *> fancy_it(fancy_editors);
    while (fancy_it.hasNext())
        delete fancy_it.next();

    QList<ComboPropertyEdit *> combo_editors =
            m_combo_editor_to_property.keys();
    QListIterator<ComboPropertyEdit *> combo_it(combo_editors);
    while (combo_it.hasNext())
        delete combo_it.next();
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
//    qDebug() << "PropertyVariantFactory::createEditor()" << property->propertyName();
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
            PropertyVariantManager::colorPropertyTypeId()) {
        ColorPropertyEdit *editor = new ColorPropertyEdit(parent);
        QVariant var = manager->value(property);
        ColorProperty mat = var.value<ColorProperty>();
        editor->setColorProperty(mat);

        m_property_to_color_editors[property].append(editor);
        m_color_editor_to_property[editor] = property;

        connect(editor, SIGNAL(colorPropertyChanged(const ColorProperty &)),
                this, SLOT(slotSetValue(const ColorProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    if (manager->propertyType(property) ==
            PropertyVariantManager::scientificDoubleTypeId()) {
        ScientificDoublePropertyEdit *editor = new ScientificDoublePropertyEdit(parent);
        QVariant var = manager->value(property);
        ScientificDoubleProperty sc = var.value<ScientificDoubleProperty>();
        editor->setScientificDoubleProperty(sc);

        m_property_to_scdouble_editors[property].append(editor);
        m_scdouble_editor_to_property[editor] = property;

        connect(editor,
                SIGNAL(scientificDoublePropertyChanged(const ScientificDoubleProperty &)),
                this, SLOT(slotSetValue(const ScientificDoubleProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    if (manager->propertyType(property) ==
            PropertyVariantManager::fancyGroupTypeId()) {
        GroupPropertyEdit *editor = new GroupPropertyEdit(parent);
        QVariant var = manager->value(property);
        GroupProperty_t ff = var.value<GroupProperty_t>();
        editor->setGroupProperty(ff);

        m_property_to_fancygroup_editors[property].append(editor);
        m_fancygroup_editor_to_property[editor] = property;

        connect(editor,
                SIGNAL(groupPropertyChanged(GroupProperty_t)),
                this, SLOT(slotSetValue(GroupProperty_t)));

        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }

    if (manager->propertyType(property) ==
            PropertyVariantManager::comboPropertyTypeId()) {
        ComboPropertyEdit *editor = new ComboPropertyEdit(parent);
//        qDebug() << "       PropertyVariantFactory::createEditor() -> created ComboEditor" << editor;

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
//    qDebug() << "PropertyVariantFactory::slotPropertyChanged()" << property->propertyName() << value;
    if (m_property_to_material_editors.contains(property)) {
        QList<MaterialPropertyEdit *> editors =
                m_property_to_material_editors[property];
        QListIterator<MaterialPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            MaterialProperty mat = value.value<MaterialProperty>();
            itEditor.next()->setMaterialProperty(mat);
        }
    }
    else if (m_property_to_color_editors.contains(property)) {
        QList<ColorPropertyEdit *> editors =
                m_property_to_color_editors[property];
        QListIterator<ColorPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            ColorProperty mat = value.value<ColorProperty>();
            itEditor.next()->setColorProperty(mat);
        }
    }
    else if (m_property_to_scdouble_editors.contains(property)) {
        QList<ScientificDoublePropertyEdit *> editors =
                m_property_to_scdouble_editors[property];
        QListIterator<ScientificDoublePropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            ScientificDoubleProperty mat = value.value<ScientificDoubleProperty>();
            itEditor.next()->setScientificDoubleProperty(mat);
        }
    }
    else if (m_property_to_fancygroup_editors.contains(property)) {
        QList<GroupPropertyEdit *> editors =
                m_property_to_fancygroup_editors[property];
        QListIterator<GroupPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
            GroupProperty_t mat = value.value<GroupProperty_t>();
//            qDebug() << "       PropertyVariantFactory::slotPropertyChanged() -> Setting editor";
            itEditor.next()->setGroupProperty(mat);
        }
    }
    else if (m_property_to_combo_editors.contains(property)) {
        QList<ComboPropertyEdit *> editors =
                m_property_to_combo_editors[property];
        QListIterator<ComboPropertyEdit *> itEditor(editors);
        while (itEditor.hasNext()) {
//            qDebug() << "       PropertyVariantFactory::slotPropertyChanged() -> Setting editor";
            ComboProperty combo = value.value<ComboProperty>();
            itEditor.next()->setComboProperty(combo);
        }
    }
}


void PropertyVariantFactory::slotSetValue(const MaterialProperty &value)
{
//    qDebug() << "PropertyVariantFactory::slotSetValue(const MaterialProperty &value)";
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
            // FIXME g.p. Is it the right place to delete?
            //object->deleteLater();
            return;
        }
        itEditor++;
    }
}

void PropertyVariantFactory::slotSetValue(const ColorProperty &value)
{
    QObject *object = sender();
    QMap<ColorPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_color_editor_to_property.constBegin();
    while (itEditor != m_color_editor_to_property.constEnd()) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtVariantPropertyManager *manager = propertyManager(property);
            if (!manager) return;
            QVariant var;
            var.setValue(value);
            manager->setValue(property, var);
            // FIXME g.p. Is it the right place to delete?
            //object->deleteLater();
            return;
        }
        itEditor++;
    }
}

void PropertyVariantFactory::slotSetValue(const ScientificDoubleProperty &value)
{
    QObject *object = sender();
    QMap<ScientificDoublePropertyEdit *, QtProperty *>::ConstIterator itEditor =
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

void PropertyVariantFactory::slotSetValue(const GroupProperty_t &value)
{
//    qDebug() << "PropertyVariantFactory::slotSetValue(const GroupProperty_t &value)";
    QObject *object = sender();
    QMap<GroupPropertyEdit *, QtProperty *>::ConstIterator itEditor =
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

void PropertyVariantFactory::slotSetValue(const ComboProperty &value)
{
//    qDebug() << "PropertyVariantFactory::slotSetValue(const ComboProperty &value)";
    QObject *object = sender();
    QMap<ComboPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                m_combo_editor_to_property.constBegin();
    while (itEditor != m_combo_editor_to_property.constEnd()) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtVariantPropertyManager *manager = propertyManager(property);
            if (!manager) return;
            QVariant var;
            var.setValue(value);
            manager->setValue(property, var);
            // FIXME g.p. Is it the right place to delete?
            //object->deleteLater();
            return;
        }
        itEditor++;
    }
}

void PropertyVariantFactory::slotEditorDestroyed(QObject *object)
{
//    qDebug() << "PropertyVariantFactory::slotEditorDestroyed(QObject *object)";
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

    QMap<ColorPropertyEdit *, QtProperty *>::ConstIterator color_it_editor =
                m_color_editor_to_property.constBegin();
    while (color_it_editor != m_color_editor_to_property.constEnd()) {
        if (color_it_editor.key() == object) {
            ColorPropertyEdit *editor = color_it_editor.key();
            QtProperty *property = color_it_editor.value();
            m_color_editor_to_property.remove(editor);
            m_property_to_color_editors[property].removeAll(editor);
            if (m_property_to_color_editors[property].isEmpty())
                m_property_to_color_editors.remove(property);
            return;
        }
        color_it_editor++;
    }

    QMap<ScientificDoublePropertyEdit *, QtProperty *>::ConstIterator scdouble_it_editor =
                m_scdouble_editor_to_property.constBegin();
    while (scdouble_it_editor != m_scdouble_editor_to_property.constEnd()) {
        if (scdouble_it_editor.key() == object) {
            ScientificDoublePropertyEdit *editor = scdouble_it_editor.key();
            QtProperty *property = scdouble_it_editor.value();
            m_scdouble_editor_to_property.remove(editor);
            m_property_to_scdouble_editors[property].removeAll(editor);
            if (m_property_to_scdouble_editors[property].isEmpty())
                m_property_to_scdouble_editors.remove(property);
            return;
        }
        scdouble_it_editor++;
    }

    QMap<GroupPropertyEdit *, QtProperty *>::ConstIterator fancygroup_editor_it =
                m_fancygroup_editor_to_property.constBegin();
    while (fancygroup_editor_it != m_fancygroup_editor_to_property.constEnd()) {
        if (fancygroup_editor_it.key() == object) {
            qDebug() << "PropertyVariantFactory::slotEditorDestroyed(QObject *object) -> fancy group editor";

            GroupPropertyEdit *editor = fancygroup_editor_it.key();
            QtProperty *property = fancygroup_editor_it.value();
            m_fancygroup_editor_to_property.remove(editor);
            m_property_to_fancygroup_editors[property].removeAll(editor);
            if (m_property_to_fancygroup_editors[property].isEmpty())
                m_property_to_fancygroup_editors.remove(property);
            return;
        }
        fancygroup_editor_it++;
    }

    QMap<ComboPropertyEdit *, QtProperty *>::ConstIterator combo_it_editor =
                m_combo_editor_to_property.constBegin();
    while (combo_it_editor != m_combo_editor_to_property.constEnd()) {
        if (combo_it_editor.key() == object) {
            ComboPropertyEdit *editor = combo_it_editor.key();
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

void PropertyVariantFactory::slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &)
{
//    qDebug() << "PropertyVariantFactory::slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &) -> ???";

}

