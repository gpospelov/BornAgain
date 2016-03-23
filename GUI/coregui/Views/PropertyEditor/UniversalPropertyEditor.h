// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/UniversalPropertyEditor.h
//! @brief     Defines class UniversalPropertyEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef UNIVERSALPROPERTYEDITOR_H
#define UNIVERSALPROPERTYEDITOR_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>
#include <QString>

class SampleDesignerInterface;
class QItemSelectionModel;
class QItemSelection;
class QtVariantPropertyManager;
class QtTreePropertyBrowser;
class QtProperty;
class QtVariantProperty;
class QVariant;
class QtAbstractPropertyBrowser;
class SessionItem;


//! property editor to display and modify properties of currently selected SessionItem
class BA_CORE_API_ UniversalPropertyEditor : public QWidget
{
    Q_OBJECT

public:
    enum EBrowserType { BROWSER_TREE_TYPE, BROWSER_GROUPBOX_TYPE, BROWSER_BUTTON_TYPE};

    UniversalPropertyEditor(QItemSelectionModel *selection_model,
                         QWidget *parent = 0, EBrowserType browser_type = BROWSER_TREE_TYPE);
    virtual ~UniversalPropertyEditor(){}

    QObject *getObject() const;
    struct ItemIndexPair {
        ItemIndexPair(SessionItem *item=0, int index=0)
            : m_item(item), m_index(index) {}
        SessionItem *m_item;
        int m_index;
    };

    void setSelectionModel(QItemSelectionModel *selection_model);

    //! assigns item to the property editor
    void setItem(SessionItem *item);

    void setCreateGroupProperty(bool create_group_property);

public slots:
    //! show property of currently selected object (triggered by graphics scene)
    void selectionChanged(const QItemSelection & selected,
                          const QItemSelection & deselected);

private slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);
    void updateSubItems(const QString &name);
    void onPropertyChanged(const QString &property_name);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);

private:
    //! clear editor
    void clearEditor();

    SessionItem *m_item; //! object to modify

    QItemSelectionModel *m_selection_model;

    QMap<QtProperty *, ItemIndexPair>     m_property_to_item_index_pair;
    QMap<const SessionItem *, QMap<int, QtVariantProperty *> >
        m_item_to_index_to_property;

    QMap<const SessionItem *, QMap<QString, QtVariantProperty *> >
        m_item_to_propertyname_to_qtvariantproperty;


    QtAbstractPropertyBrowser    *m_browser;
    QtVariantPropertyManager *m_manager;
    QtVariantPropertyManager *m_read_only_manager;

    void addItemProperties(const SessionItem *item);
    void addSubProperties(QtProperty *item_property,
                          const SessionItem *item);

    //! If true than group property will be created, i.e. all properties of
    //! SessionItem will be sub-properties of group with the name modelType
    //! (as in PropertyEditor of SampleDesigner)
    bool m_create_group_property;

    //! type of property browser
    EBrowserType m_browser_type;
};


#endif // SAMPLEPROPERTYEDITOR_H
