// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainFittingBuilder.h
//! @brief     Declares class DomainFittingBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DOMAINFITTINGBUILDER_H
#define DOMAINFITTINGBUILDER_H

#include <QString>
#include <memory>

class JobItem;
class FitSuite;

//! The DomainFittingBuilder class builds the domain FitSuite using JobItem

class DomainFittingBuilder
{
public:
    static std::shared_ptr<FitSuite> createFitSuite(JobItem *jobItem);
};

#endif // DOMAINFITTINGBUILDER_H
