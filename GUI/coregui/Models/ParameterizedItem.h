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

#include "ParameterTranslators.h"

#include <memory>
#include <QObject>
#include <QVector>
#include <QVariant>

class SessionModel;

class BA_CORE_API_ ParameterizedItem : public QObject
{
    Q_OBJECT

public:
    //! create new parameterized item and set model type
    explicit ParameterizedItem(QString model_type = QString());

    //! delete me and children
    virtual ~ParameterizedItem();


    // data manipulation

    //! retrieve data of given column, return invalid qvariant when out of range
    QVariant data(int column) const;

    //! set data in the given column, return true when successful, notify model if present
    //! we only support one role
    bool setData(int column, const QVariant &data);

    //! return variant stored in data column
    QVariant value() const;

    //! set data column
    bool setValue(QVariant value);

    //! check if data is set
    bool hasData(int column);


    // labels

    //! return a user definable name, if present, or returs displayName() otherwise
    QString itemName() const;

    //! set the item's name through the model, use this instead of P_NAME
    void setItemName(const QString &name);

    //! retrieve a unique name based on the type and an index (if needed to distinguish siblings)
    //! This name is primarely used for generating long parameter names (ParticleDistributionItem
    //! and fitting).
    QString displayName() const;

    //! retrieves the model type
    QString modelType() const;

    //! return a nice string representation of the data contained in this item
    virtual QString itemLabel() const;


    // members

    //! set model of item and children
    void setModel(SessionModel *model);

    SessionModel *model() const;

    class PortInfo
    {
    public:
        enum EPorts { DEFAULT = -1, PORT_0 = 0, PORT_1 = 1, PORT_2 = 2 };

        PortInfo(const QString &name = QString(), int nmax_items = 0)
            : m_item_names(name), m_item_max_number(nmax_items) {}

        QStringList m_item_names;
        int m_item_max_number;
    };

    //! gets the item port, should be used instead of P_PORT
    PortInfo::EPorts port() const;

    //! not quite sure how this works, leave it as it is
    void setPort(PortInfo::EPorts nport);


    // navigation functions

    //! retrieve parent item
    ParameterizedItem *parent() const;

    //! get number of child items
    int childItemCount() const;

    //! column count is equal for all items and is derived from session model
    int columnCount() const;

    //! retrieve child item in given row - take care of null pointer
    ParameterizedItem *childAt(int row) const;

    //! get row number of child
    int rowOfChild(ParameterizedItem *child) const;

    //! the index of this item from his parent
    int childNumber() const;


    // accessing children

    //! indicates if item has child items
    bool hasChildItems() const;

    //! returns the a list of child items
    QList<ParameterizedItem *> childItems() const;

    //! Returns a pointer to the first child of the given type
    ParameterizedItem *getChildOfType(const QString &type) const;

    //! get pointer to irst child with given display name (take care of appended index number)
    ParameterizedItem* getChildByName(const QString &name) const;

    //! returns a list of children of a certain type
    QList<ParameterizedItem *> getChildrenOfType(const QString &model_type) const;

    //! insert a child item at specified row
    virtual void insertChildItem(int row, ParameterizedItem *item);

    //! take child item (this removes it from the current item)
    virtual ParameterizedItem *takeChildItem(int row);

    //! indicates if the passed item can be set as a child item
    bool acceptsAsChild(const QString &child_name) const;

    //! get list of acceptable child object names
    QList<QString> acceptableChildItems() const;


    // registered properties

    //! insert child item and make it known to it, populate with default value
    //! TODO propertyattributes should now be set on the item itself
    PropertyAttribute &registerProperty(const QString &name, const QVariant &variant,
                          const PropertyAttribute &attribute = PropertyAttribute());

    //! check in its property map
    bool isRegisteredProperty(const QString &name) const;

    //! retrieve property
    QVariant getRegisteredProperty(const QString &name) const;

    //! update the property through the model
    void setRegisteredProperty(const QString &name, const QVariant &variant);

    //! unset property from this item
    void removeRegisteredProperty(const QString &name);


    // group properties

    //! register a new group property according to group name
    ParameterizedItem *registerGroupProperty(const QString &group_name,
                                             const Constants::ModelType &group_model);

    //! check if this group property exists
    bool isGroupProperty(const QString &name) const;

    //! set the group of the property, returns current item
    //! call without second parameter to get current item directly
    ParameterizedItem *setGroupProperty(const QString &name, const QString &value = QString()) const;

    //! returns current item of group property
    ParameterizedItem *getGroupItem(const QString &name) const;


    // attributes

    //! get the reference to the attribute of a registered property
    const PropertyAttribute& getPropertyAttribute(const QString &name) const;
    PropertyAttribute& getPropertyAttribute(const QString &name);

    //! set the attribute
    void setPropertyAttribute(const QString &name, const PropertyAttribute &attribute);


    // helper

    //! checking constrains of ports
    virtual ParameterizedItem *getCandidateForRemoval(ParameterizedItem *new_comer);


protected:
    //! sets the display name
    void setDisplayName(QString display_name);

    //! make this type insertable as child
    void addToValidChildren(const QString &name, PortInfo::EPorts nport = PortInfo::PORT_0,
                            int nmax_children = 0);

    //! swap two children in member list
    //! use this to enforce a specific order when this matters
    void swapChildren(int first, int second);


private:
    //! used for display name to get the index of the item
    int getCopyNumberOfChild(const ParameterizedItem *p_item) const;


    ParameterizedItem *mp_parent;
    SessionModel *m_model;
    QVector<QVariant> m_data;
    QString m_model_type;
    QString m_display_name;
    PortInfo::EPorts m_port;
    QList<ParameterizedItem *> m_children;
    QMap<QString, ParameterizedItem *> m_propertyItems;
    QMap<QString, PropertyAttribute> m_property_attribute;
    QList<QString> m_valid_children;
    QMap<int, PortInfo> m_port_info;





    // end of refactored parameterized item








    // the following function will be moved out of parameterized item

    // signals and slots -> use signals of session model


public:


    QMap<QString, ParameterizedItem *> getSubItems() const;




    virtual void onPropertyChange(const QString &name);

    virtual void onChildPropertyChange(ParameterizedItem *item, const QString &propertyName=QString());

    void print() const;



signals:
    void propertyChanged(const QString &propertyName);
    void subItemChanged(const QString &propertyName);
    void subItemPropertyChanged(const QString &property_group, const QString &property_name);
    void siblingsChanged();

protected slots:
    virtual void onSubItemChanged(const QString &propertyName);
    virtual void onSubItemPropertyChanged(const QString &property_group,
                                          const QString &property_name);
    virtual void onSiblingsChanged();

private slots:
    virtual void processSubItemPropertyChanged(const QString &propertyName);

protected:






    void notifySiblings();

};

#endif /* PARAMETERIZEDITEM_H_ */
