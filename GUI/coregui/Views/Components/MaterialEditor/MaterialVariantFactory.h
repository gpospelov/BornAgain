#ifndef MATERIALVARIANTFACTORY_H
#define MATERIALVARIANTFACTORY_H


#include <QtVariantEditorFactory>

class MaterialColorPropertyEdit;
class MaterialColorProperty;

//! The PropertyVariantFactory class provides and manages user defined
//! QVariant based properties.
class MaterialVariantFactory : public QtVariantEditorFactory
{
    Q_OBJECT
public:
    MaterialVariantFactory(QObject *parent = 0)
        : QtVariantEditorFactory(parent)
            { }

    virtual ~MaterialVariantFactory();
protected:
    virtual void connectPropertyManager(QtVariantPropertyManager *manager);
    using QtVariantEditorFactory::createEditor;
    virtual QWidget *createEditor(QtVariantPropertyManager *manager,
                                  QtProperty *property, QWidget *parent);
    virtual void disconnectPropertyManager(QtVariantPropertyManager *manager);
private slots:
    void slotPropertyChanged(QtProperty *property, const QVariant &value);
    void slotSetValue(const MaterialColorProperty &value);
    void slotEditorDestroyed(QObject *object);
private:
    QMap<QtProperty *, QList<MaterialColorPropertyEdit *> >
        m_property_to_material_editors;
    QMap<MaterialColorPropertyEdit *, QtProperty *>
        m_material_editor_to_property;
};


#endif
