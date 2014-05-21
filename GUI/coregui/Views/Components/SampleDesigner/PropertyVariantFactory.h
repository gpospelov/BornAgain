#ifndef OBJECTVARIANTFACTORY_H
#define OBJECTVARIANTFACTORY_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtVariantEditorFactory>

class MaterialPropertyEdit;
class MaterialProperty;
class GroupPropertyEdit;
class GroupProperty;

//! The PropertyVariantFactory class provides and manages user defined
//! QVariant based properties.
class PropertyVariantFactory : public QtVariantEditorFactory
{
    Q_OBJECT
public:
    PropertyVariantFactory(QObject *parent = 0)
        : QtVariantEditorFactory(parent)
            { }

    virtual ~PropertyVariantFactory();
protected:
    virtual void connectPropertyManager(QtVariantPropertyManager *manager);
    using QtVariantEditorFactory::createEditor;
    virtual QWidget *createEditor(QtVariantPropertyManager *manager,
                                  QtProperty *property, QWidget *parent);
    virtual void disconnectPropertyManager(QtVariantPropertyManager *manager);
private slots:
    void slotPropertyChanged(QtProperty *property, const QVariant &value);
    void slotSetValue(const MaterialProperty &value);
    void slotSetValue(const GroupProperty &value);
    void slotEditorDestroyed(QObject *object);
    void slotPropertyAttributeChanged(QtProperty *, const QString &, const QVariant &);

private:
    QMap<QtProperty *, QList<MaterialPropertyEdit *> >
        m_property_to_material_editors;
    QMap<MaterialPropertyEdit *, QtProperty *>
        m_material_editor_to_property;
    QMap<QtProperty *, QList<GroupPropertyEdit *> >
        m_property_to_group_editors;
    QMap<GroupPropertyEdit *, QtProperty *>
        m_group_editor_to_property;
};

#endif // OBJECTVARIANTFACTORY_H
