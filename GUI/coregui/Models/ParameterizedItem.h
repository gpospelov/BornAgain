// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterizedItem.h
//! @brief     Defines class ParameterizedItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERIZEDITEM_H_
#define PARAMETERIZEDITEM_H_

#include "MaterialItem.h"
#include <QStandardItem>
#include <QStringList>
#include <QList>
#include <QMap>

class QEvent;

class ParameterizedItem : public QObject
{
    Q_OBJECT
public:
    static const QString P_NAME;
    virtual ~ParameterizedItem();

    //! retrieves the model type
    QString modelType() const { return m_model_type; }

    //! retrieves the item's name
    QString itemName() const;

    //! sets the item's name
    void setItemName(const QString &item_name);

    //! retrieve parent item
    ParameterizedItem *parent() const { return m_parent; }

    //! retrieve child item in given row
    ParameterizedItem *childAt(int row) const {
        return m_children.value(row);
    }

    //! get row number of child
    int rowOfChild(ParameterizedItem *child) const {
        return m_children.indexOf(child);
    }

    //! get number of child items
    int childItemCount() const { return m_children.count(); }

    //! indicates if item has child items
    bool hasChildItems() const { return !m_children.isEmpty(); }

    //! returns the a list of child items
    QList<ParameterizedItem *> childItems() const { return m_children; }

    //! inserts a child item at specified row
    void insertChildItem(int row, ParameterizedItem *item)
        { item->m_parent = this; m_children.insert(row, item); }

    //! append child item
    void addChildItem(ParameterizedItem *item)
        { item->m_parent = this; m_children << item; }

    //! swap two child items
    void swapChildItems(int row_1, int row_2)
        { m_children.swap(row_1, row_2); }

    //! take child item (this removes it from the current item)
    ParameterizedItem *takeChildItem(int row);

    //! indicates if the passed item can be set as
    //! a child item
    bool acceptsAsChild(const QString &child_name) const;

    //! get list of acceptable child object names
    QList<QString> acceptableChildItems() const { return m_valid_children; }

    bool event(QEvent * e );

    QMap<QString, ParameterizedItem *> getSubItems() const {
        return m_sub_items;
    }

    void addPropertyItem(QString name, ParameterizedItem *item);

    ParameterizedItem *createPropertyItem(QString name);

    explicit ParameterizedItem(const QString &model_type=QString(),
                               ParameterizedItem *parent=0);

    void setMaterialProperty(MaterialProperty material = MaterialProperty());

    ParameterizedItem *registerGroupProperty(const QString &name, const QString &value);
    ParameterizedItem *setGroupProperty(const QString &name, const QString &value);

    bool isHiddenProperty(const QString &name) const;
    QString getPropertyToolTip(const QString &name) const;

    enum PropertyVisibility {VisibleProperty, HiddenProperty };
    void registerProperty(const QString &name, const QVariant &variant, const QString &tooltip = QString(), PropertyVisibility = VisibleProperty);
    void setRegisteredProperty(const QString &name, const QVariant &variant);
    QVariant getRegisteredProperty(const QString &name) const;

    void setBlockPropertyChangeEvent(bool flag) {m_block_property_change_event = flag; }
    bool getBlockPropertyChangeEvent() const { return m_block_property_change_event; }

    void setPropertyVisibility(const QString &name, PropertyVisibility visibility);

    void print() const;
signals:
    void propertyChanged(const QString &propertyName);
    void propertyItemChanged(const QString &propertyName);

protected:
    void updatePropertyItem(QString name);
    QList<QString> m_valid_children;

    QStringList m_registered_properties;
    QStringList m_hidden_properties;
    QMap<QString, QString> m_property_tooltip;

private:
    QString m_model_type;
    //QString m_item_name;
    ParameterizedItem *m_parent;
    QList<ParameterizedItem *> m_children;
    QMap<QString, ParameterizedItem *> m_sub_items;
    bool m_block_property_change_event;
};

#endif /* PARAMETERIZEDITEM_H_ */
