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
#include "SessionModel.h"


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

std::string ModelPath::translateParameterName(const SessionItem* item, const QString& par_name)
{
    std::ostringstream result;
    QStringList list = splitParameterName(par_name);
    if (list.isEmpty()) {
        return std::string {};
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
                // FIXME additional check t->childAt(j)->isEditable() is to skip
                // JobItem::P_INSTRUMENT_NAME which conflicts with the name "Instrument" of
                // InstrumentItem
                if (t->childAt(j)->itemName() == parts[i] && t->childAt(j)->isEditable()) {
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

SessionItem* ModelPath::findChild(const SessionItem *item, const QString& first_field)
{
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
    return p_child;
}

