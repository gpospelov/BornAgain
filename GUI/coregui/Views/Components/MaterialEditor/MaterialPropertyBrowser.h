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


//! Class which holds QtProperty tree browser to adjust material properties.
//! Belongs to MaterialEditorWidget
class MaterialPropertyBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialPropertyBrowser(MaterialModel *model, QWidget *parent = 0);
    virtual ~MaterialPropertyBrowser(){}

    void setModel(MaterialModel *model);

    struct SubItem {
        SubItem(MaterialItem *owner=0, QString name = QString())
            : m_owner(owner), m_name(name) {}
        MaterialItem *m_owner;
        QString m_name;
        friend bool operator <(const SubItem& left, const SubItem& right)
        {
            if(left.m_owner == right.m_owner)
                return left.m_name < right.m_name;
            return left.m_owner < right.m_owner;
        }
    };


    MaterialItem *getSelectedMaterial();

    QtTreePropertyBrowser *getPropertyBrowser() { return m_browser; }

private slots:
    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);
    void slotValueChanged(QtProperty *property, const QVariant &value);

    void onCurrentBrowserItemChanged(QtBrowserItem *);

private:
    void updateBrowser();
    void clearBrowser();
    void addMaterialProperties(MaterialItem *material);
    void updateMaterialProperties(MaterialItem *material);
    void addSubProperties(QtProperty *property, MaterialItem *material);
    void removeSubProperties(QtProperty *property);
    void updateSubProperties(MaterialItem *material);

    enum ExpandAction { SaveExpandState, RestoreExpandState};
    void updateExpandState(ExpandAction action);

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

    QMap<QtProperty *, SubItem> m_property_to_subitem;
    QMap<MaterialItem *, QMap<QString, QtVariantProperty *> > m_material_to_property;

    QMap<SubItem, bool> m_subItemToExpanded;
};



#endif
