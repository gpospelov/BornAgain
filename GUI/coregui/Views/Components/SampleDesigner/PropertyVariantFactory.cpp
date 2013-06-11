#include "PropertyVariantFactory.h"
#include "PropertyVariantManager.h"
#include "PropertyBrowserUtils.h"
#include "MaterialBrowser.h"


PropertyVariantFactory::~PropertyVariantFactory()
{
    QList<MaterialPropertyEdit *> editors = theEditorToProperty.keys();
    QListIterator<MaterialPropertyEdit *> it(editors);
    while (it.hasNext())
        delete it.next();
}

void PropertyVariantFactory::connectPropertyManager(QtVariantPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QVariant &)));
//    connect(manager, SIGNAL(attributeChanged(QtProperty *, const QString &, const QVariant &)),
//                this, SLOT(slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &)));
    QtVariantEditorFactory::connectPropertyManager(manager);
}


QWidget *PropertyVariantFactory::createEditor(QtVariantPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    if (manager->propertyType(property) == PropertyVariantManager::materialTypeId()) {
        MaterialPropertyEdit *editor = new MaterialPropertyEdit(parent);
        QVariant var = manager->value(property);
        MaterialProperty mat = var.value<MaterialProperty>();
        editor->setMaterialProperty(mat);

        theCreatedEditors[property].append(editor);
        theEditorToProperty[editor] = property;

        connect(editor, SIGNAL(materialPropertyChanged(const MaterialProperty &)),
                this, SLOT(slotSetValue(const MaterialProperty &)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
        return editor;
    }
    return QtVariantEditorFactory::createEditor(manager, property, parent);
}


void PropertyVariantFactory::disconnectPropertyManager(QtVariantPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QVariant &)));
    disconnect(manager, SIGNAL(attributeChanged(QtProperty *, const QString &, const QVariant &)),
                this, SLOT(slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &)));
    QtVariantEditorFactory::disconnectPropertyManager(manager);
}


void PropertyVariantFactory::slotPropertyChanged(QtProperty *property,
                const QVariant &value)
{
    if (!theCreatedEditors.contains(property))
        return;

    QList<MaterialPropertyEdit *> editors = theCreatedEditors[property];
    QListIterator<MaterialPropertyEdit *> itEditor(editors);
    while (itEditor.hasNext()) {
        MaterialProperty mat = value.value<MaterialProperty>();
        itEditor.next()->setMaterialProperty(mat);
    }
}


void PropertyVariantFactory::slotSetValue(const MaterialProperty &value)
{
    QObject *object = sender();
    QMap<MaterialPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                theEditorToProperty.constBegin();
    while (itEditor != theEditorToProperty.constEnd()) {
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
    QMap<MaterialPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                theEditorToProperty.constBegin();
    while (itEditor != theEditorToProperty.constEnd()) {
        if (itEditor.key() == object) {
            MaterialPropertyEdit *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            theEditorToProperty.remove(editor);
            theCreatedEditors[property].removeAll(editor);
            if (theCreatedEditors[property].isEmpty())
                theCreatedEditors.remove(property);
            return;
        }
        itEditor++;
    }
}

