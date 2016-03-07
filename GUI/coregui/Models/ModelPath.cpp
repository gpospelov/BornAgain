// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TestItem.cpp
//! @brief     Implements class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ModelPath.h"
#include "SessionItem.h"
#include <QStringList>
#include <sstream>


std::vector<std::unique_ptr<IParameterTranslator>> ModelPath::m_special_translators;

QStringList ModelPath::getParameterTreeList(const SessionItem *item, QString prefix)
{
    QStringList result;
    if (item->modelType() ==  Constants::PropertyType
            && item->value().type() == QVariant::Double) {
        result << prefix + item->itemName();
    } else {
        if (item->hasChildItems()) {
            for (auto p_child : item->childItems()) {
                QString child_name = p_child->itemName();
                QString child_prefix = prefix + child_name + QString("/");
                result << getParameterTreeList(p_child, child_prefix);
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
    if (item->isRegisteredProperty(head)) {
        return item->getRegisteredProperty(head).toDouble();
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

