#ifndef OBJECTVARIANTFACTORY_H
#define OBJECTVARIANTFACTORY_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtVariantEditorFactory>

class MaterialPropertyEdit;
class MaterialProperty;

//! The PropertyVariabtFactory class provides and manages user defined QVariant based properties.
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
    virtual QWidget *createEditor(QtVariantPropertyManager *manager, QtProperty *property,
                QWidget *parent);
    virtual void disconnectPropertyManager(QtVariantPropertyManager *manager);
private slots:
    void slotPropertyChanged(QtProperty *property, const QVariant &value);
    void slotSetValue(const MaterialProperty &value);
    void slotEditorDestroyed(QObject *object);
private:
    QMap<QtProperty *, QList<MaterialPropertyEdit *> > theCreatedEditors;
    QMap<MaterialPropertyEdit *, QtProperty *> theEditorToProperty;
};

#endif // OBJECTVARIANTFACTORY_H
