// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ModelPath.cpp
//! @brief     Implements class ModelPath
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ModelPath.h"
#include "SessionItem.h"
#include "GroupProperty.h"
#include "GroupItem.h"
#include "ParticleItem.h"
#include "SessionModel.h"
#include <QModelIndex>
#include <QStringList>
#include <sstream>


std::vector<std::unique_ptr<IParameterTranslator>> ModelPath::m_special_translators;

QStringList ModelPath::getParameterTreeList(const SessionItem *item, QString prefix)
{
    QStringList result;
    if (item->modelType() ==  Constants::PropertyType
            && item->value().type() == QVariant::Double && item->itemName() != ParticleItem::P_ABUNDANCE) {
        if (prefix.endsWith("/"))
            prefix = prefix.mid(0, prefix.size()-1);
        result << prefix;
    }
    else {
        if (item->hasChildren()) {
            for (auto p_child : item->childItems()) {
                if(p_child->isVisible()) {
                    if (p_child->modelType() ==  Constants::GroupItemType) {
                        if (const GroupItem *groupItem = dynamic_cast<const GroupItem*>(p_child)) {
                            if (const SessionItem *subItem = groupItem->group()->getCurrentItem()) {
                                if (groupItem->group()->isFixed()) {
                                    QString child_prefix = prefix + groupItem->itemName() + QString("/");
                                    result << getParameterTreeList(subItem, child_prefix);
                                } else {
                                    QString child_prefix = prefix + subItem->itemName() + QString("/");
                                    result << getParameterTreeList(subItem, child_prefix);
                                }
                            }
                        }
                    } else {
                        QString child_name = p_child->itemName();
                        QString child_prefix = prefix + child_name + QString("/");
                        result << getParameterTreeList(p_child, child_prefix);
                    }
                }
            }
        }
    }
    return result;
}

double ModelPath::getParameterValue(const SessionItem *item, const QString &name)
{
    QString head = getFirstField(name);
    auto p_child = item->getChildByName(head);
    if (p_child) {
        return getParameterValue(p_child, stripFirstField(name));
    }
    if (item->isTag(head)) {
        return item->getItemValue(head).toDouble();
    } else {
        return 0.0;
    }
}

std::string ModelPath::translateParameterName(const SessionItem *item, const QString &par_name)
{
    std::ostringstream result;
    auto list = splitParameterName(par_name);
    if (list.isEmpty()) {
        return std::string();
    }
    auto first_field = list[0];
    result << "/" << translateSingleName(first_field);
    if (list.size() > 1) {
        auto remainder = list[1];
        auto p_child = item->getChildByName(first_field);
        if (!p_child) { //search through group items
            auto groupItems = item->getChildrenOfType(Constants::GroupItemType);
            for (auto groupItem : groupItems) {
                if (GroupItem *gItem = dynamic_cast<GroupItem*>(groupItem)) {
                    if (gItem->group()->getCurrentType() == first_field) {
                        p_child = gItem->group()->getCurrentItem();
                        break;
                    }
                }
            }
        }
        if (p_child) {
            result << translateParameterName(p_child, remainder);
        }
    }
    return result.str();
}

void ModelPath::addParameterTranslator(const IParameterTranslator &translator)
{
    m_special_translators.emplace_back(translator.clone());
}

QString ModelPath::getPathFromIndex(const QModelIndex &index)
{
    if (index.isValid()) {
        QStringList namePath;
        QModelIndex cur = index;
        while (cur.isValid()) {
            namePath << cur.data().toString();
            cur = cur.parent();
        }
        std::reverse(namePath.begin(), namePath.end());
        return namePath.join("/");
    }
    return QString();
}

QModelIndex ModelPath::getIndexFromPath(const SessionModel *model, const QString &path)
{
    if (model) {
        QStringList parts = path.split("/");
        SessionItem *t = model->rootItem();
        for(int i = 0; i < parts.length(); i++) {
            for (int j = 0; j < t->rowCount(); j++) {
                if (t->childAt(j)->itemName() == parts[i]) {
                    t = t->childAt(j);
                    break;
                }
            }
        }
        return t->index();
    }
    return QModelIndex();
}

QStringList ModelPath::splitParameterName(const QString &par_name)
{
    QStringList result;
    for (auto& translator : m_special_translators) {
        result = translator->split(par_name);
        if (result.size() > 0) {
            return result;
        }
    }
    result << getFirstField(par_name);
    QString remainder = stripFirstField(par_name);
    if (!remainder.isEmpty()) {
        result << remainder;
    }
    return result;
}

QString ModelPath::getFirstField(const QString &par_name)
{
    QStringList par_list = par_name.split("/");
    if (par_list.size()==0) return QString();
    return par_list.front();
}

QString ModelPath::stripFirstField(const QString &par_name)
{
    QStringList par_list = par_name.split("/");
    if (par_list.size()<2) return QString();
    par_list.removeFirst();
    return par_list.join("/");
}

std::string ModelPath::translateSingleName(const QString &name)
{
    for (auto& translator : m_special_translators) {
        auto result = translator->translate(name);
        if (!result.empty()) {
            return result;
        }
    }
    return name.toStdString();
}

