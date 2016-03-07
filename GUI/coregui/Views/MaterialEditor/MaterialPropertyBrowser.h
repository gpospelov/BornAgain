// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialPropertyBrowser.h
//! @brief     Defines class MaterialPropertyBrowser
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALPROPERTYBROWER_H
#define MATERIALPROPERTYBROWER_H

#include <QWidget>
#include <QMap>
#include <QString>

#include "WinDllMacros.h"

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
class SessionItem;


//! Class which holds QtProperty tree browser to adjust material properties.
//! Belongs to MaterialEditorWidget
class BA_CORE_API_ MaterialPropertyBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialPropertyBrowser(MaterialModel *materialModel, QWidget *parent = 0);
    virtual ~MaterialPropertyBrowser(){}

    void setModel(MaterialModel *materialModel);

    struct SubItem {
        SubItem(SessionItem *owner=0, QString name = QString())
            : m_owner(owner), m_name(name) {}
        SessionItem *m_owner;
        QString m_name;
        friend bool operator <(const SubItem& left, const SubItem& right)
        {
            if(left.m_owner == right.m_owner)
                return left.m_name < right.m_name;
            return left.m_owner < right.m_owner;
        }
    };


//    struct ItemIndexPair {
//        ItemIndexPair(SessionItem *item=0, int index=0)
//            : m_item(item), m_index(index) {}
//        SessionItem *m_item;
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
    void addMaterialProperties(SessionItem *material);
//    void updateMaterialProperties(SessionItem *material);
    void addSubProperties(QtProperty *property, SessionItem *item);
    void removeSubProperties(QtProperty *property);
//    void updateSubProperties(SessionItem *material);

    enum EExpandAction { SAVE_EXPAND_STATE, RESTORE_EXPAND_STATE };
    void updateExpandState(EExpandAction action);

    MaterialModel *m_materialModel;
    QtTreePropertyBrowser *m_browser;
    QtVariantPropertyManager *m_variantManager;
    QtVariantPropertyManager *m_readOnlyManager;
    //QtVariantEditorFactory *m_variantFactory;

    QMap<QtProperty *, SessionItem *> m_top_property_to_material;
    QMap<SessionItem *, QtVariantProperty *> m_top_material_to_property;
    QMap<QtProperty *, SubItem> m_property_to_subitem;
    QMap<SessionItem *, QMap<QString, QtVariantProperty *> > m_material_to_property;


//    QMap<QtProperty *, ItemIndexPair>     m_property_to_item_index_pair;
//    QMap<const SessionItem *, QMap<int, QtVariantProperty *> >
//        m_item_to_index_to_property;

//    QMap<const SessionItem *, QMap<QString, QtVariantProperty *> >
//        m_item_to_propertyname_to_qtvariantproperty;


    QMap<SubItem, bool> m_subItemToExpanded;

    bool m_selection_changed;
};



#endif
