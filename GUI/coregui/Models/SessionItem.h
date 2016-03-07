// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedItem.h
//! @brief     Defines class SessionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONITEM_H_
#define SESSIONITEM_H_

#include "WinDllMacros.h"
#include "item_constants.h"
#include "ModelMapper.h"
#include "AttLimits.h"

#include <memory>
#include <QObject>
#include <QVector>
#include <QVariant>
#include <QMetaType>

Q_DECLARE_METATYPE(AttLimits)

class SessionModel;
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


class BA_CORE_API_ SessionItem : public QObject
{
    Q_OBJECT

    friend class SessionModel;

public:
    static const QString P_NAME;
    explicit SessionItem(QString modelType = QString());
    virtual ~SessionItem();
    QVariant data(int role) const;
    virtual bool setData(int role, const QVariant &value);
    QModelIndex index() const;
    SessionItem *parent() const;
    int childItemCount() const;
    SessionItem *childAt(int row) const;

    SessionModel *model() const;
    ModelMapper *mapper();

    // tags

    SessionTagInfo getTagInfo(const QString &name) const;
    bool registerTag(QString name, int min = 0, int max = -1, QStringList modelTypes = QStringList());

    SessionItem *getItem(QString tag = QString(), int index = 0) const;
    QVector<SessionItem *> getItems(QString tag = QString()) const;
    bool insertItem(int row, SessionItem *item, const QString &tag);
    SessionItem *takeItem(int row, const QString &tag);
    QString tagFromItem(const SessionItem *item) const;

    QVector<int> getRoles() const;


    void emitValueChanged(int role = Qt::DisplayRole);



    SessionItem *registerProperty(const QString &name, const QVariant &variant);
    SessionItem *registerGroupProperty(const QString &group_name,
                                             const Constants::ModelType &group_model);

    bool isRegisteredProperty(const QString &name) const;
    QVariant getRegisteredProperty(const QString &name) const;
    void setRegisteredProperty(const QString &name, const QVariant &variant);
    void removeRegisteredProperty(const QString &name);
    bool isGroupProperty(const QString &name) const;
    SessionItem *setGroupProperty(const QString &name, const QString &value = QString()) const;
    SessionItem *getGroupItem(const QString &name, const QString &type = QString()) const;

    virtual QString itemLabel() const;
    int rowOfChild(SessionItem *child) const;
    int childNumber() const;
    bool hasChildItems() const;
    QVector<SessionItem *> childItems() const;
    SessionItem *getChildOfType(const QString &type) const;
    SessionItem* getChildByName(const QString &name) const;
    QList<SessionItem *> getChildrenOfType(const QString &model_type) const;
    QList<SessionItem *> getUnregisteredChildren() const;

    virtual void insertChildItem(int row, SessionItem *item, const QString tag = QString());
    virtual SessionItem *takeChildItem(int row);
    bool acceptsAsChild(const QString &child_name) const;
    QList<QString> acceptableChildItems() const;



    // transparent layer to roles
    QString modelType() const;

    QVariant value() const;
    bool setValue(QVariant value);

    QString defaultTag() const;
    void setDefaultTag(QString tag);

    QString displayName() const; // append index takes some logic - ?
    void setDisplayName(QString display_name);

    QString itemName() const; // storing data in property item
    void setItemName(const QString &name);

    void setVisible(bool enabled);
    void setEnabled(bool enabled);
    void setEditable(bool enabled);

    bool isVisible() const;
    bool isEnabled() const;
    bool isEditable() const;

    AttLimits limits() const;
    void setLimits(AttLimits value);

    int decimals() const;
    void setDecimals(int n);

    QString toolTip() const;
    void setToolTip(QString tooltip);



private:
    int getCopyNumberOfChild(const SessionItem *p_item) const;
    void childDeleted(SessionItem *child);
    void setParentAndModel(SessionItem *parent, SessionModel *model);
    void setModel(SessionModel *model);
    int tagStartIndex(const QString &name) const;
    void changeFlags(bool enabled, int flag);
    int flags() const;

    SessionItem *mp_parent;
    SessionModel *m_model;
    QVector<SessionItem *> m_children;
    QVector<SessionItemData> m_values;
    QVector<SessionTagInfo> m_tags;
    std::unique_ptr<ModelMapper> m_mapper;
};

#endif /* SessionItem_H_ */
