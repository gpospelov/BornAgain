#ifndef OBJECTVARIANTFACTORY_H
#define OBJECTVARIANTFACTORY_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtVariantEditorFactory>

class MaterialPropertyEdit;
class MaterialProperty;
class GroupPropertyEdit;
class GroupProperty;
class ColorPropertyEdit;
class ColorProperty;
class ScientificDoublePropertyEdit;
class ScientificDoubleProperty;
class FancyGroupPropertyEdit;
class FancyGroupProperty;

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
    void slotSetValue(const ColorProperty &value);
    void slotSetValue(const ScientificDoubleProperty &value);
    void slotSetValue(FancyGroupProperty *value);
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
    QMap<QtProperty *, QList<ColorPropertyEdit *> >
        m_property_to_color_editors;
    QMap<ColorPropertyEdit *, QtProperty *>
        m_color_editor_to_property;

    QMap<QtProperty *, QList<ScientificDoublePropertyEdit *> >
        m_property_to_scdouble_editors;
    QMap<ScientificDoublePropertyEdit *, QtProperty *>
        m_scdouble_editor_to_property;

    QMap<QtProperty *, QList<FancyGroupPropertyEdit *> >
        m_property_to_fancygroup_editors;
    QMap<FancyGroupPropertyEdit *, QtProperty *>
        m_fancygroup_editor_to_property;


};

#endif // OBJECTVARIANTFACTORY_H
