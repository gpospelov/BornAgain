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
#include "ParameterTranslators.h"

#include <memory>
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
    explicit ParameterizedItem(QString model_type = QString(),
                               ParameterizedItem *parent = 0);

    virtual ~ParameterizedItem();

    //! retrieves the model type
    QString modelType() const;

    //! returns a user definable name, if present, or returns displayName() otherwise
    QString itemName() const;

    //! sets the item's name
    void setItemName(const QString &item_name);

    //! retrieves a unique name based on the type and an index (if needed to distinguish siblings)
    //! This name is primarely used for generating long parameter names (ParticleDistributionItem
    //! and fitting).
    QString displayName() const;

    //! returns a nice string representation of the data contained in this item
    virtual QString itemLabel() const;

    //! retrieve parent item
    ParameterizedItem *parent() const;

    //! retrieve child item in given row
    ParameterizedItem *childAt(int row) const;

    //! get row number of child
    int rowOfChild(ParameterizedItem *child) const;

    //! get number of child items
    int childItemCount() const;

    //! indicates if item has child items
    bool hasChildItems() const;

    //! returns the a list of child items
    QList<ParameterizedItem *> childItems() const;

    //! inserts a child item at specified row
    virtual void insertChildItem(int row, ParameterizedItem *item);

    //! take child item (this removes it from the current item)
    virtual ParameterizedItem *takeChildItem(int row);

    //! Returns a pointer to the first child of the given type
    ParameterizedItem *getChildOfType(QString type) const;

    //! indicates if the passed item can be set as a child item
    bool acceptsAsChild(const QString &child_name) const;

    //! get list of acceptable child object names
    QList<QString> acceptableChildItems() const;

    bool event(QEvent *e);

    QMap<QString, ParameterizedItem *> getSubItems() const;

    void addPropertyItem(QString name, ParameterizedItem *item);

    bool isRegisteredProperty(const QString &name) const;

    ParameterizedItem *registerGroupProperty(const QString &group_name,
                                             const Constants::ModelType &group_model);
    ParameterizedItem *setGroupProperty(const QString &name, const QString &value);

    PropertyAttribute& registerProperty(const QString &name, const QVariant &variant,
                          const PropertyAttribute &attribute = PropertyAttribute());

    void setRegisteredProperty(const QString &name, const QVariant &variant);
    QVariant getRegisteredProperty(const QString &name) const;
    void removeRegisteredProperty(const QString &name);

    const PropertyAttribute& getPropertyAttribute(const QString &name) const;
    PropertyAttribute& getPropertyAttribute(const QString &name);

    void setPropertyAttribute(const QString &name, const PropertyAttribute &attribute);

    virtual void onPropertyChange(const QString &name);

    virtual void onChildPropertyChange();

    void print() const;

    virtual ParameterizedItem *getCandidateForRemoval(ParameterizedItem *new_comer);

    class PortInfo
    {
    public:
        enum EPorts { DEFAULT = -1, PORT_0 = 0, PORT_1 = 1, PORT_2 = 2 };

        PortInfo(const QString &name = QString(), int nmax_items = 0)
            : m_item_names(name), m_item_max_number(nmax_items) {}

        QStringList m_item_names;
        int m_item_max_number;
    };

    void setItemPort(PortInfo::EPorts nport);

    //! retrieves a list of all parameter names in the ParameterizedItem tree starting
    //! with this node and prefixes them
    QStringList getParameterTreeList(QString prefix = "") const;

    //! translates the given parameter name to a domain parameter name
    //! name should start with a child/subitem name or be a direct parameter name
    std::string translateParameterName(const QString &par_name) const;

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
    //! sets the display name
    void setDisplayName(QString display_name);

    void addToValidChildren(const QString &name, PortInfo::EPorts nport = PortInfo::PORT_0,
                            int nmax_children = 0);

    //! swap two children in member list
    //! use this to enforce a specific order when this matters
    void swapChildren(int first, int second);

    QStringList splitParameterName(const QString& par_name) const;

    QString getFirstField(const QString &par_name) const;

    QString stripFirstField(const QString &par_name) const;

    virtual std::string translateSingleName(const QString &name) const;

    void addParameterTranslator(const IParameterTranslator &translator);

    ParameterizedItem* getChildByDisplayName(const QString &name) const;

    QStringList m_registered_properties;

    QMap<QString, PropertyAttribute> m_property_attribute;

    void notifySiblings();

private:
    QStringList getParameterList(QString prefix = "") const;
    int getCopyNumberOfChild(const ParameterizedItem *p_item) const;
    QList<QString> m_valid_children;
    QMap<int, PortInfo> m_port_info;

    QString m_model_type;
    QString m_display_name;
    ParameterizedItem *mp_parent;
    QList<ParameterizedItem *> m_children;
    QMap<QString, ParameterizedItem *> m_sub_items;
    std::vector<std::unique_ptr<IParameterTranslator>> m_special_translators;
};

#endif /* PARAMETERIZEDITEM_H_ */
