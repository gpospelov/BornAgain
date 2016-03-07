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


class BA_CORE_API_ ParameterizedItem : public QObject
{
    Q_OBJECT

    friend class SessionModel;

public:
    static const QString P_NAME;
    explicit ParameterizedItem(QString modelType = QString());
    virtual ~ParameterizedItem();
    QVariant data(int role) const;
    virtual bool setData(int role, const QVariant &value);
    QModelIndex index() const;
    ParameterizedItem *parent() const;
    int childItemCount() const;
    ParameterizedItem *childAt(int row) const;

    SessionModel *model() const;
    ModelMapper *mapper();

    // tags

    SessionTagInfo getTagInfo(const QString &name) const;
    bool registerTag(QString name, int min = 0, int max = -1, QStringList modelTypes = QStringList());

    ParameterizedItem *getItem(QString tag = QString(), int index = 0) const;
    QVector<ParameterizedItem *> getItems(QString tag = QString()) const;
    bool insertItem(int row, ParameterizedItem *item, const QString &tag);
    ParameterizedItem *takeItem(int row, const QString &tag);
    QString tagFromItem(const ParameterizedItem *item) const;

    QVector<int> getRoles() const;


    void emitValueChanged(int role = Qt::DisplayRole);



    ParameterizedItem *registerProperty(const QString &name, const QVariant &variant);
    ParameterizedItem *registerGroupProperty(const QString &group_name,
                                             const Constants::ModelType &group_model);

    bool isRegisteredProperty(const QString &name) const;
    QVariant getRegisteredProperty(const QString &name) const;
    void setRegisteredProperty(const QString &name, const QVariant &variant);
    void removeRegisteredProperty(const QString &name);
    bool isGroupProperty(const QString &name) const;
    ParameterizedItem *setGroupProperty(const QString &name, const QString &value = QString()) const;
    ParameterizedItem *getGroupItem(const QString &name, const QString &type = QString()) const;

    virtual QString itemLabel() const;
    int rowOfChild(ParameterizedItem *child) const;
    int childNumber() const;
    bool hasChildItems() const;
    QVector<ParameterizedItem *> childItems() const;
    ParameterizedItem *getChildOfType(const QString &type) const;
    ParameterizedItem* getChildByName(const QString &name) const;
    QList<ParameterizedItem *> getChildrenOfType(const QString &model_type) const;
    QList<ParameterizedItem *> getUnregisteredChildren() const;

    virtual void insertChildItem(int row, ParameterizedItem *item, const QString tag = QString());
    virtual ParameterizedItem *takeChildItem(int row);
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
    int getCopyNumberOfChild(const ParameterizedItem *p_item) const;
    void childDeleted(ParameterizedItem *child);
    void setParentAndModel(ParameterizedItem *parent, SessionModel *model);
    void setModel(SessionModel *model);
    int tagStartIndex(const QString &name) const;
    void changeFlags(bool enabled, int flag);
    int flags() const;

    ParameterizedItem *mp_parent;
    SessionModel *m_model;
    QVector<ParameterizedItem *> m_children;
    QVector<SessionItemData> m_values;
    QVector<SessionTagInfo> m_tags;
    std::unique_ptr<ModelMapper> m_mapper;
};

#endif /* PARAMETERIZEDITEM_H_ */
