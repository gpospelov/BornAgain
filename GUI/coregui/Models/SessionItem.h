// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItem.h
//! @brief     Defines class SessionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include "RealLimits.h"
#include "ModelMapper.h"
#include "item_constants.h"
#include <QStringList>
#include <memory>

Q_DECLARE_METATYPE(RealLimits)

class SessionItemData;

class SessionTagInfo
{
public:
    inline SessionTagInfo() : name(QString()), min(0), max(-1), childCount(0) {}
    inline SessionTagInfo(QString n, int mi, int ma, QStringList mt = QStringList())
        :name(n)
        , min(mi)
        , max(ma)
        , childCount(0)
        , modelTypes(mt) {}
    QString name;
    int min;
    int max;
    int childCount;
    QStringList modelTypes;
    inline bool isValid() { return !name.isEmpty(); }
};


class BA_CORE_API_ SessionItem
{
    friend class SessionModel;

public:
    static const QString P_NAME;

    explicit SessionItem(const QString &modelType = QString());
    virtual ~SessionItem();
    SessionModel *model() const;
    SessionItem *parent() const;

    // these functions work without tags and operate on all children
    QModelIndex index() const;
    bool hasChildren() const;
    int rowCount() const;
    QVector<SessionItem *> childItems() const;
    SessionItem *childAt(int row) const;
    int rowOfChild(SessionItem *child) const;
    int parentRow() const;
    SessionItem* getChildByName(const QString &name) const;
    SessionItem *getChildOfType(const QString &type) const;
    QVector<SessionItem *> getChildrenOfType(const QString &model_type) const;
    SessionItem *takeRow(int row);

    // manage and check tags
    bool registerTag(const QString &name, int min = 0, int max = -1,
                     QStringList modelTypes = QStringList());
    bool isTag(const QString &name) const;
    QString tagFromItem(const SessionItem *item) const;
    SessionTagInfo getTagInfo(const QString &name = QString()) const;
    bool acceptsAsDefaultItem(const QString &item_name) const;
    QVector<QString> acceptableDefaultItemTypes() const;

    // access tagged items
    SessionItem *getItem(const QString &tag = QString(), int row = 0) const;
    QVector<SessionItem *> getItems(const QString &tag = QString()) const;
    bool insertItem(int row, SessionItem *item, const QString &tag = QString());
    SessionItem *takeItem(int row, const QString &tag);

    // convenience functions for properties and groups
    SessionItem *addProperty(const QString &name, const QVariant &variant);
    QVariant getItemValue(const QString &tag) const;
    void setItemValue(const QString &tag, const QVariant &variant);
    SessionItem *addGroupProperty(const QString &groupName, const QString &groupType);

    SessionItem *setGroupProperty(const QString &name, const QString &value) const;
    SessionItem *getGroupItem(const QString &name, const QString &type = QString()) const;

    // access data stored in roles
    virtual QVariant data(int role) const;
    virtual bool setData(int role, const QVariant &value);
    QVector<int> getRoles() const;
    void emitDataChanged(int role = Qt::DisplayRole);

    // custom data types
    QString modelType() const;

    QVariant value() const;
    bool setValue(QVariant value);

    QString defaultTag() const;
    void setDefaultTag(const QString &tag);

    QString displayName() const;
    void setDisplayName(const QString &display_name);

    QString itemName() const;
    void setItemName(const QString &name);

    void setVisible(bool enabled);
    void setEnabled(bool enabled);
    void setEditable(bool enabled);
    bool isVisible() const;
    bool isEnabled() const;
    bool isEditable() const;

    RealLimits limits() const;
    SessionItem& setLimits(const RealLimits &value);

    int decimals() const;
    SessionItem& setDecimals(int n);

    QString toolTip() const;
    SessionItem& setToolTip(const QString &tooltip);


    // helper functions
    virtual QString itemLabel() const;
    ModelMapper *mapper();

private:
    void childDeleted(SessionItem *child);
    void setParentAndModel(SessionItem *parent, SessionModel *model);
    void setModel(SessionModel *model);
    int tagStartIndex(const QString &name) const;
    int flags() const;
    void changeFlags(bool enabled, int flag);
    int getCopyNumberOfChild(const SessionItem *item) const;

    SessionItem *m_parent;
    SessionModel *m_model;
    QVector<SessionItem *> m_children;
    QVector<SessionItemData> m_values;
    QVector<SessionTagInfo> m_tags;
    std::unique_ptr<ModelMapper> m_mapper;
};

Q_DECLARE_METATYPE(SessionItem*) // INVESTIGATE something requires sessionitem be declared as meta type

#endif // SESSIONITEM_H
