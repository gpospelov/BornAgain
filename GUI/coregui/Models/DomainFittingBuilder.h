// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainFittingBuilder.h
//! @brief     Defines DomainFittingBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DOMAINFITTINGBUILDER_H
#define DOMAINFITTINGBUILDER_H

#include "WinDllMacros.h"
#include <memory>

class JobItem;
class FitSuite;

//! The DomainFittingBuilder namespace

namespace DomainFittingBuilder {

    //! Creates domain's fitSuite from JobItem
    BA_CORE_API_ std::shared_ptr<FitSuite> createFitSuite(JobItem *jobItem);

}

#endif // DOMAINFITTINGBUILDER_H
