// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelPath.h
//! @brief     Defines class ModelPath
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MODELPATH_H
#define MODELPATH_H

#include "WinDllMacros.h"
#include "ParameterTranslators.h"
#include <memory>
#include <vector>

class SessionItem;
class QModelIndex;
class SessionModel;

class BA_CORE_API_ ModelPath
{
public:
    //! retrieves a list of all parameter names in the SessionItem tree starting
    //! with this node and prefixes them
    static QStringList getParameterTreeList(const SessionItem *item, QString prefix = "");

    //! retrieve value of given parameter name
    static double getParameterValue(const SessionItem *item, const QString &name);

    //! translates the given parameter name to a domain parameter name
    //! name should start with a child/subitem name or be a direct parameter name
    static std::string translateParameterName(const SessionItem *item, const QString &par_name);

    static void addParameterTranslator(const IParameterTranslator &translator);

    static QString getPathFromIndex(const QModelIndex &index);

    static QModelIndex getIndexFromPath(const SessionModel *model, const QString &path);

    static SessionItem* getItemFromPath(const QString &relPath, SessionItem *parent);

    static bool isValidItem(SessionModel *model, SessionItem *item, const QModelIndex &parent);

    static bool isTranslatable(const SessionItem *item, const QString &par_name);

    static const SessionItem *ancestor(const SessionItem *item, const QString& requiredModelType);

private:

    static QStringList splitParameterName(const QString& par_name);

    static QString getFirstField(const QString& par_name);

    static QString stripFirstField(const QString& par_name);

    static std::string translateSingleName(const QString& name);

    static SessionItem* findChild(const SessionItem* item, const QString& first_field);

    static std::string stripDistributionNone(const std::string& name);

    static std::vector<std::unique_ptr<IParameterTranslator>> m_special_translators;
};

#endif // MODELPATH_H
