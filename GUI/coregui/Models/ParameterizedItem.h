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
#include <QList>
#include <QMap>

class QEvent;

class ParameterizedItem : public QObject
{
    Q_OBJECT
public:
    virtual ~ParameterizedItem();

    //! retrieves the model type
    QString modelType() const { return m_model_type; }

    //! retrieves the item's name
    QString itemName() const { return m_item_name; }

    //! sets the item's name
    void setItemName(const QString &item_name) { m_item_name = item_name; }

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

    //friend class ItemFactory;

    bool event(QEvent * e );

    QMap<QString, ParameterizedItem *> getSubItems() const {
        return m_sub_items;
    }

    void addPropertyItem(QString name, ParameterizedItem *item);

    ParameterizedItem *createPropertyItem(QString name);

    ParameterizedItem *addFormFactorProperty(const char *name, QString value);
    explicit ParameterizedItem(const QString &model_type=QString(),
                               ParameterizedItem *parent=0);

    void setMaterialProperty(MaterialProperty material = MaterialProperty());

signals:
    void propertyChanged(QString propertyName);
    void propertyItemChanged(QString propertyName);

protected:
    void updatePropertyItem(QString name);
    QList<QString> m_valid_children;

private:
    QString m_model_type;
    QString m_item_name;
    ParameterizedItem *m_parent;
    QList<ParameterizedItem *> m_children;
    QMap<QString, ParameterizedItem *> m_sub_items;
};

#endif /* PARAMETERIZEDITEM_H_ */
