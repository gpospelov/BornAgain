#include "PropertyVariantFactory.h"
#include "PropertyVariantManager.h"
#include "PropertyBrowserUtils.h"
#include "MaterialBrowser.h"

#include <iostream>

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
    connect(manager, SIGNAL(attributeChanged(QtProperty *, const QString &, const QVariant &)),
                this, SLOT(slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &)));
    QtVariantEditorFactory::connectPropertyManager(manager);
}

QWidget *PropertyVariantFactory::createEditor(QtVariantPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    if (manager->propertyType(property) == PropertyVariantManager::materialTypeId()) {
        MaterialPropertyEdit *editor = new MaterialPropertyEdit(parent);
//        QVariant var = manager->value(property);
//        MaterialProperty mat = var.value<MaterialProperty>();
//        editor->setMaterialProperty(mat);
//        editor->setFilePath(manager->value(property).toString());
//        editor->setFilter(manager->attributeValue(property, QLatin1String("filter")).toString());

        QVariant var = manager->value(property);
        MaterialProperty mat = var.value<MaterialProperty>();
        editor->setMaterialProperty(mat);

        theCreatedEditors[property].append(editor);
        theEditorToProperty[editor] = property;

//        connect(editor, SIGNAL(filePathChanged(const QString &)),
//                this, SLOT(slotSetValue(const QString &)));
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
    std::cout << "PropertyVariantFactory::slotPropertyChanged() ->v1.1" << std::endl;
    if (!theCreatedEditors.contains(property))
        return;
    std::cout << "PropertyVariantFactory::slotPropertyChanged() ->v1.2" << std::endl;

    QList<MaterialPropertyEdit *> editors = theCreatedEditors[property];
    QListIterator<MaterialPropertyEdit *> itEditor(editors);
//    while (itEditor.hasNext())
//        itEditor.next()->setFilePath(value.toString());
    while (itEditor.hasNext()) {
        MaterialProperty mat = value.value<MaterialProperty>();
        std::cout << "PropertyVariantFactory::slotPropertyChanged() ->v1.3" << mat.getName().toStdString()<< std::endl;
        itEditor.next()->setMaterialProperty(mat);
    }
}

void PropertyVariantFactory::slotPropertyAttributeChanged(QtProperty *property,
            const QString &attribute, const QVariant &value)
{
    std::cout << "PropertyVariantFactory::slotPropertyAttributeChanged() ->" << std::endl;
//    if (!theCreatedEditors.contains(property))
//        return;

//    if (attribute != QLatin1String("filter"))
//        return;

//    QList<MaterialPropertyEdit *> editors = theCreatedEditors[property];
//    QListIterator<MaterialPropertyEdit *> itEditor(editors);
//    while (itEditor.hasNext())
//        itEditor.next()->setFilter(value.toString());
}

void PropertyVariantFactory::slotSetValue(const MaterialProperty &value)
//void PropertyVariantFactory::slotSetValue(const QString &value)
{
    std::cout << "PropertyVariantFactory::slotSetValue() -> " << std::endl;
    QObject *object = sender();
    QMap<MaterialPropertyEdit *, QtProperty *>::ConstIterator itEditor =
                theEditorToProperty.constBegin();
    while (itEditor != theEditorToProperty.constEnd()) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtVariantPropertyManager *manager = propertyManager(property);
            if (!manager)
                return;
            QVariant var;
            std::cout << "PropertyVariantFactory::slotSetValue() ->  value " << value.getName().toStdString() << std::endl;
            var.setValue(value);
            manager->setValue(property, var);
            std::cout << "PropertyVariantFactory::slotSetValue() ->  done " <<  std::endl;

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

