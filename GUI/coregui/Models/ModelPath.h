// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TestItem.h
//! @brief     Defines class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MODELPATH_H
#define MODELPATH_H

#include "WinDllMacros.h"
#include "ParameterTranslators.h"
#include <string>
#include <vector>
#include <memory>

class ParameterizedItem;
class QString;
class QStringList;

class BA_CORE_API_ ModelPath
{
public:
    //! retrieves a list of all parameter names in the ParameterizedItem tree starting
    //! with this node and prefixes them
    static QStringList getParameterTreeList(const ParameterizedItem *item, QString prefix = "");

    //! retrieve value of given parameter name
    static double getParameterValue(const ParameterizedItem *item, const QString &name);

    //! translates the given parameter name to a domain parameter name
    //! name should start with a child/subitem name or be a direct parameter name
    static std::string translateParameterName(const ParameterizedItem *item, const QString &par_name);

    static void addParameterTranslator(const IParameterTranslator &translator);

private:

    static QStringList splitParameterName(const QString& par_name);

    static QString getFirstField(const QString &par_name);

    static QString stripFirstField(const QString &par_name);

    static std::string translateSingleName(const QString &name);

    static std::vector<std::unique_ptr<IParameterTranslator>> m_special_translators;
};

#endif
