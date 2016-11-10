// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelPath.cpp
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
#include "GroupItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "SessionModel.h"
#include "JobItem.h"

using std::string;

std::vector<std::unique_ptr<IParameterTranslator>> ModelPath::m_special_translators {};

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
                                QString child_prefix = prefix + subItem->itemName() + QString("/");
                                result << getParameterTreeList(subItem, child_prefix);
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

string ModelPath::translateParameterName(const SessionItem* item, const QString& par_name)
{
    std::ostringstream result;
    QStringList list = splitParameterName(par_name);
    if (list.isEmpty()) {
        return {};
    }
    QString first_field = list[0];
    result << "/" << translateSingleName(first_field);
    if (list.size() > 1) {
        QString remainder = list[1];
        const SessionItem* p_child = findChild(item, first_field);
        if (p_child) {
            result << translateParameterName(p_child, remainder);
        }
    }
    return stripDistributionNone(result.str());
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

// FIXME TODO refactor this hell, item #1623, item #1624

QModelIndex ModelPath::getIndexFromPath(const SessionModel *model, const QString &path)
{
    if (model) {
        QStringList parts = path.split("/");
        SessionItem *t = model->rootItem();
        for(int i = 0; i < parts.length(); i++) {
            if (t->modelType()==Constants::JobItemType && parts[i]==Constants::InstrumentType) {
                t = t->getItem(JobItem::T_INSTRUMENT);
                continue;
            }
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

//! returns an item from relative path wrt to given parent
SessionItem *ModelPath::getItemFromPath(const QString &relPath, SessionItem *parent)
{
    Q_ASSERT(parent);
    QString fullPath = getPathFromIndex(parent->index()) + "/" + relPath;
    return parent->model()->itemForIndex(ModelPath::getIndexFromPath(parent->model(), fullPath));
}

//! Iterates through all the model and returns true if item is found. This is to

bool ModelPath::isValidItem(SessionModel *model, SessionItem *item, const QModelIndex &parent)
{
    for(int i_row=0; i_row<model->rowCount(parent); ++i_row) {
        QModelIndex index = model->index(i_row, 0, parent);
        SessionItem *curr = model->itemForIndex(index);
        if(curr == item) return true;

        bool isvalid = isValidItem(model, item, index);
        if(isvalid) return isvalid;
    }
    return false;
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
    // TODO: extract as default split method
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
    if (par_list.size()==0) return QString {};
    return par_list.front();
}

QString ModelPath::stripFirstField(const QString &par_name)
{
    QStringList par_list = par_name.split("/");
    if (par_list.size()<2) return QString {};
    par_list.removeFirst();
    return par_list.join("/");
}

string ModelPath::translateSingleName(const QString &name)
{
    for (auto& translator : m_special_translators) {
        auto result = translator->translate(name);
        if (!result.empty()) {
            return result;
        }
    }
    return name.toStdString();
}

SessionItem* ModelPath::findChild(const SessionItem *item, const QString& first_field)
{
    if (item->modelType()==Constants::JobItemType) {
        if (first_field==Constants::MultiLayerType) {
            return item->getItem(JobItem::T_SAMPLE);
        } else if (first_field==Constants::InstrumentType) {
            return item->getItem(JobItem::T_INSTRUMENT);
        }
    }
    SessionItem* p_child = item->getChildByName(first_field);
    if (!p_child) { //search through group items
        auto groupItems = item->getChildrenOfType(Constants::GroupItemType);
        for (SessionItem* groupItem : groupItems) {
            if (GroupItem *gItem = dynamic_cast<GroupItem*>(groupItem)) {
                if (gItem->group()->getCurrentType() == first_field) {
                    p_child = gItem->group()->getCurrentItem();
                    break;
                }
            }
        }
    }
    return p_child;
}

// TODO: item #1623, remove this hack when refactoring name translations
string ModelPath::stripDistributionNone(const string &name)
{
    const string distribution_none { "/DistributionNone/Value" };
    if (name.length() >= distribution_none.length() &&
        name.compare(name.length()-distribution_none.length(), distribution_none.length(),
                     distribution_none)==0) {
        return name.substr(0, name.length()-distribution_none.length());
    }
    return name;
}

//! Returns true when we know how to translate ParameterItem link to domain name.
// TODO: item #1623, item #1624 remove this hack when refactoring name translations
// Function is intended to disalow drag-and-drop of ParameterItem onto FitParameterItem
// for non-implemented  or senseless translations (in GUI)
bool ModelPath::isTranslatable(const SessionItem *item, const QString &par_name)
{
    Q_UNUSED(item);
    if(par_name.contains(Constants::DetectorType))
        return false;
    if(par_name.contains(ParticleItem::P_ABUNDANCE))
        return false;
    if(par_name.contains(ParticleLayoutItem::P_TOTAL_DENSITY))
        return false;
    if(par_name.contains("FTDistribution1D") || par_name.contains("FTDecayFunction1D"))
        return false;
    if(par_name.contains("FTDistribution2D") || par_name.contains("FTDecayFunction2D"))
        return false;
    return true;
}

//! Returns ancestor of given modelType for given item.
//! For example, returns corresponding jobItem owning ParameterItem via ParameterContainer.

const SessionItem* ModelPath::ancestor(const SessionItem *item, const QString &requiredModelType)
{
    const SessionItem *cur = item;
    while (cur && cur->modelType() != requiredModelType)
        cur = cur->parent();

    return cur;
}
