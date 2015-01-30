// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedItem.h
//! @brief     Defines class ParameterizedItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERIZEDITEM_H_
#define PARAMETERIZEDITEM_H_

#include "WinDllMacros.h"
#include "item_constants.h"
#include "PropertyAttribute.h"
#include "MaterialProperty.h"
#include <QStandardItem>
#include <QStringList>
#include <QList>
#include <QMap>

class QEvent;

class BA_CORE_API_ ParameterizedItem : public QObject
{
    Q_OBJECT
public:
    static const QString P_NAME;
    static const QString P_PORT;
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
    virtual void insertChildItem(int row, ParameterizedItem *item);

    //! take child item (this removes it from the current item)
    virtual ParameterizedItem *takeChildItem(int row);

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

    explicit ParameterizedItem(const QString &model_type=QString(),
                               ParameterizedItem *parent=0);

    bool isRegisteredProperty(const QString &name);

    ParameterizedItem *registerGroupProperty(const QString &group_name, const Constants::ModelType &group_model);
    ParameterizedItem *setGroupProperty(const QString &name, const QString &value);

    void registerProperty(const QString &name, const QVariant &variant, const PropertyAttribute &attribute = PropertyAttribute());
    void setRegisteredProperty(const QString &name, const QVariant &variant);
    QVariant getRegisteredProperty(const QString &name) const;
    void removeRegisteredProperty(const QString &name);

    PropertyAttribute getPropertyAttribute(const QString &name) const;

    void print() const;

    virtual void onPropertyChange(const QString &name);

    virtual ParameterizedItem *getCandidateForRemoval(ParameterizedItem *new_comer);

    class PortInfo {
    public:
        enum EPorts {
            DEFAULT = -1,
            PORT_0 = 0,
            PORT_1 = 1,
            PORT_2 = 2
        };
        PortInfo(const QString &name=QString(), int nmax_items=0) : m_item_names(name), m_item_max_number(nmax_items){}
        QStringList m_item_names;
        int m_item_max_number;
    };

    void setItemPort(PortInfo::EPorts nport);

    virtual QString getItemLabel() const { return QString("no label"); }

    void setPropertyAppearance(const QString &name, const PropertyAttribute::EAppearance &appearance);

    QStringList getParameterTreeList() const;

    virtual void onChildPropertyChange();

public slots:
    void onPropertyItemChanged(const QString &propertyName);

signals:
    void propertyChanged(const QString &propertyName);
    void propertyItemChanged(const QString &propertyName);

protected:
    void addToValidChildren(const QString &name, PortInfo::EPorts nport = PortInfo::PORT_0, int nmax_children = 0);
    void setPropertyAttribute(const QString &name, const PropertyAttribute &attribute);

    QStringList m_registered_properties;

    QMap<QString, PropertyAttribute> m_property_attribute;

private:
    QStringList getParameterList() const;
    QList<QString> m_valid_children;
    QMap<int, PortInfo> m_port_info;

    QString m_model_type;
    ParameterizedItem *m_parent;
    QList<ParameterizedItem *> m_children;
    QMap<QString, ParameterizedItem *> m_sub_items;
};

#endif /* PARAMETERIZEDITEM_H_ */
