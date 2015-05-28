// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/AwesomePropertyEditor.h
//! @brief     Defines class AwesomePropertyEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef AWESOMEPROPERTYEDITOR_H
#define AWESOMEPROPERTYEDITOR_H

#include "WinDllMacros.h"
#include <QWidget>

class ParameterizedItem;
class AwesomePropertyEditorPrivate;
class ParameterizedIytem;
class QtProperty;
class QtVariantProperty;
class QGroupBox;

//! property editor to display and modify properties of multiple ParameterizedItem
class BA_CORE_API_ AwesomePropertyEditor : public QWidget
{
    Q_OBJECT

public:
    enum EBrowserType {
        BROWSER_TREE_TYPE,
        BROWSER_GROUPBOX_TYPE,
        BROWSER_BUTTON_TYPE
    };

    enum EInsertMode {
        INSERT_AS_CHILD, //! child will be inserted as child to form tree structure
        INSERT_AFTER,    //! child will be inserted on the same level as parent right after him
        SKIP
    };

    AwesomePropertyEditor(QWidget *parent = 0, EBrowserType browser_type = BROWSER_TREE_TYPE);
    virtual ~AwesomePropertyEditor();

    void setItem(ParameterizedItem *item, const QString &group_name = QString());
    void addItemProperty(ParameterizedItem *item, const QString &property_name, const QString &group_name=QString(), EInsertMode subitem_insert_policy = INSERT_AS_CHILD);
    void addItemProperties(ParameterizedItem *item, const QString &group_name=QString(), EInsertMode subitem_insert_policy = INSERT_AS_CHILD);

    void clearEditor();

    bool eventFilter(QObject *obj, QEvent *event);

    QGroupBox *getGroupBox();

private slots:
    void slotValueChanged(QtProperty *property, const QVariant &value);
    void onPropertyChanged(const QString &property_name);
    void onSubItemChanged(const QString &property_name);

private:
    void insertItemProperties(ParameterizedItem *item, QtVariantProperty *parent_qtproperty=0, EInsertMode insert_mode = INSERT_AFTER, EInsertMode subitem_insert_mode = INSERT_AS_CHILD);
    void insertItemProperty(ParameterizedItem *item, const QString &property_name, QtVariantProperty *parent_qtproperty=0, EInsertMode insert_mode = INSERT_AFTER, EInsertMode subitem_insert_mode = INSERT_AS_CHILD);
    QtVariantProperty *createQtVariantProperty(ParameterizedItem *item, const QString &property_name);
    void insertQtVariantProperty(QtVariantProperty *qtVariantItem, QtVariantProperty *parent_qtproperty, EInsertMode insert_mode);
    void removeQtVariantProperties(QList<QtVariantProperty *> &list_of_properties);

    AwesomePropertyEditorPrivate *m_d;
};


#endif // SAMPLEPROPERTYEDITOR_H
