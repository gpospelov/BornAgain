// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterModelBuilder.h
//! @brief     Declares class ParameterModelBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERMODELBUILDER_H
#define PARAMETERMODELBUILDER_H

#include <QString>

class JobItem;
class SessionItem;

class ParameterModelBuilder
{
public:
    static void createParameterTree(JobItem *item, const QString &tag = QString());
private:
    static void handleItem(SessionItem *tree, SessionItem *source);
    static void populateDomainLinks(JobItem *jobItem,  const QString &tag);
};


#endif

