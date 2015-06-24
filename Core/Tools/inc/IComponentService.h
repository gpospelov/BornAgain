// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IComponentService.h
//! @brief     Defines interface IComponentService.
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
#include <boost/shared_ptr.hpp>

class IFormFactor;
class GISASSimulation;
class IFunctionalTest;

//! @class IComponentService
//! @ingroup simulation_internal
//! @brief Interface to the class which provides client with objects he needs

class BA_CORE_API_ IComponentService
{
public:
    virtual IFormFactor *getFormFactor() = 0;
    virtual GISASSimulation *getSimulation() = 0;
    virtual OutputData<double> *getReferenceData() = 0;
    virtual SampleBuilder_t getSampleBuilder() = 0;
    virtual IFunctionalTest *getFunctionalTest() = 0;

    virtual ~IComponentService(){}
};

typedef boost::shared_ptr<class IComponentService > ComponentLocator_t;


#endif /* ICOMPONENTSERVICE_H */
