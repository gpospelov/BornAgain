#ifndef MATERIALEDITORWIDGET_H
#define MATERIALEDITORWIDGET_H

#include <QWidget>
#include <QMap>
#include <QString>
class MaterialModel;
class MaterialItem;
class QtTreePropertyBrowser;
class QtAbstractPropertyBrowser;
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtProperty;
class MaterialVariantManager;
class QtVariantProperty;

class MaterialEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialEditorWidget(MaterialModel *model, QWidget *parent = 0);
    virtual ~MaterialEditorWidget(){}

    void setModel(MaterialModel *model);


    struct SubProperty {
        SubProperty(MaterialItem *parent=0, QString name = QString())
            : m_parent(parent), m_name(name) {}
        MaterialItem *m_parent;
        QString m_name;
    };

private slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);

private:
    void updateBrowser();
    void addMaterialProperties(MaterialItem *material);
    void updateMaterialProperties(MaterialItem *material);
    void addSubProperties(QtProperty *property, MaterialItem *material);
    void removeSubProperties(QtProperty *property);
    void updateSubProperties(MaterialItem *material);

    MaterialModel *m_materialModel;
    QtTreePropertyBrowser *m_browser;
    QtVariantPropertyManager *m_variantManager;
    QtVariantPropertyManager *m_readOnlyManager;
    QtVariantEditorFactory *m_variantFactory;

    QMap<QtProperty *, MaterialItem *> m_top_property_to_material;
    QMap<MaterialItem *, QtVariantProperty *> m_top_material_to_property;

//    QMap<QtProperty *, ItemIndexPair>     m_property_to_item_index_pair;
//    QMap<const ParameterizedItem *, QMap<int, QtVariantProperty *> >
//        m_item_to_index_to_property;

    QMap<QtProperty *, SubProperty> m_property_to_subitem;
    QMap<MaterialItem *, QMap<QString, QtVariantProperty *> > m_material_to_property;
};



#endif
