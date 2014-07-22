#ifndef MATERIALPROPERTYBROWER_H
#define MATERIALPROPERTYBROWER_H

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
class QModelIndex;
class QtBrowserItem;
class QItemSelection;
class ParameterizedItem;


//! Class which holds QtProperty tree browser to adjust material properties.
//! Belongs to MaterialEditorWidget
class MaterialPropertyBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialPropertyBrowser(MaterialModel *materialModel, QWidget *parent = 0);
    virtual ~MaterialPropertyBrowser(){}

    void setModel(MaterialModel *materialModel);

    struct SubItem {
        SubItem(ParameterizedItem *owner=0, QString name = QString())
            : m_owner(owner), m_name(name) {}
        ParameterizedItem *m_owner;
        QString m_name;
        friend bool operator <(const SubItem& left, const SubItem& right)
        {
            if(left.m_owner == right.m_owner)
                return left.m_name < right.m_name;
            return left.m_owner < right.m_owner;
        }
    };


//    struct ItemIndexPair {
//        ItemIndexPair(ParameterizedItem *item=0, int index=0)
//            : m_item(item), m_index(index) {}
//        ParameterizedItem *m_item;
//        int m_index;
//    };


    MaterialItem *getSelectedMaterial();

public slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private slots:
    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);
    void slotValueChanged(QtProperty *property, const QVariant &value);
    void onPropertyChanged(const QString &property_name);

private:
    void updateBrowser();
    void clearBrowser();
    void addMaterialProperties(ParameterizedItem *material);
//    void updateMaterialProperties(ParameterizedItem *material);
    void addSubProperties(QtProperty *property, ParameterizedItem *item);
    void removeSubProperties(QtProperty *property);
//    void updateSubProperties(ParameterizedItem *material);

    enum ExpandAction { SaveExpandState, RestoreExpandState};
    void updateExpandState(ExpandAction action);

    MaterialModel *m_materialModel;
    QtTreePropertyBrowser *m_browser;
    QtVariantPropertyManager *m_variantManager;
    QtVariantPropertyManager *m_readOnlyManager;
    QtVariantEditorFactory *m_variantFactory;

    QMap<QtProperty *, ParameterizedItem *> m_top_property_to_material;
    QMap<ParameterizedItem *, QtVariantProperty *> m_top_material_to_property;
    QMap<QtProperty *, SubItem> m_property_to_subitem;
    QMap<ParameterizedItem *, QMap<QString, QtVariantProperty *> > m_material_to_property;


//    QMap<QtProperty *, ItemIndexPair>     m_property_to_item_index_pair;
//    QMap<const ParameterizedItem *, QMap<int, QtVariantProperty *> >
//        m_item_to_index_to_property;

//    QMap<const ParameterizedItem *, QMap<QString, QtVariantProperty *> >
//        m_item_to_propertyname_to_qtvariantproperty;


    QMap<SubItem, bool> m_subItemToExpanded;

    bool m_selection_changed;
};



#endif
