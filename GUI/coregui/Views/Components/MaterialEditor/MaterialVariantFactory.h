#ifndef MATERIALVARIANTFACTORY_H
#define MATERIALVARIANTFACTORY_H


#include <QtVariantEditorFactory>

//class MaterialPropertyEdit;
//class MaterialColorProperty;

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
//    void slotSetValue(const MaterialProperty &value);
//    void slotSetValue(const FormFactorProperty &value);
    void slotEditorDestroyed(QObject *object);
private:
//    QMap<QtProperty *, QList<MaterialPropertyEdit *> >
//        m_property_to_material_editors;
//    QMap<MaterialPropertyEdit *, QtProperty *>
//        m_material_editor_to_property;
//    QMap<QtProperty *, QList<FormFactorPropertyEdit *> >
//        m_property_to_form_factor_editors;
//    QMap<FormFactorPropertyEdit *, QtProperty *>
//        m_form_factor_editor_to_property;
};


#endif
