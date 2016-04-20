// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/IComponentService.h
//! @brief     Declares interface IComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPONENTSERVICE_H
#define ICOMPONENTSERVICE_H

#include "WinDllMacros.h"
#include "OutputData.h"
#include "ISampleBuilder.h"

class IFormFactor;
class IFTDistribution2D;
class GISASSimulation;
class IFunctionalTest;

//! @class IComponentService
//! @ingroup simulation_internal
//! @brief Interface to the class which provides client with objects he needs

class BA_CORE_API_ IComponentService
{
public:
    virtual IFormFactor *getFormFactor() const = 0;
    virtual IFTDistribution2D *getFTDistribution2D() const = 0;
    virtual GISASSimulation *getSimulation() const = 0;
    virtual std::shared_ptr<class ISampleBuilder> getSampleBuilder() const = 0;
    virtual OutputData<double> *getReferenceData() const = 0;
    virtual IFunctionalTest *getFunctionalTest() const = 0;

    virtual ~IComponentService(){}
};


#endif /* ICOMPONENTSERVICE_H */
