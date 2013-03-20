// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IFittingDataSelector.h
//! @brief     Defines classes IFittingDataSelector and DefaultAllDataSelector.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IFITTINGDATASELECTOR_H_
#define IFITTINGDATASELECTOR_H_

#include "OutputData.h"

class IFittingDataSelector
{
public:
    virtual ~IFittingDataSelector() {}
    virtual IFittingDataSelector *clone() const=0;

    virtual OutputData<double> *createWeightMap(
        const OutputData<double> &real_data,
        const OutputData<double> &simulated_data) const=0;
};

class DefaultAllDataSelector : public IFittingDataSelector
{
public:
    DefaultAllDataSelector() {}
    virtual ~DefaultAllDataSelector() {}
    virtual DefaultAllDataSelector *clone() const {
        return new DefaultAllDataSelector();
    }

    virtual OutputData<double> *createWeightMap(
        const OutputData<double> &real_data,
        const OutputData<double> &simulated_data) const;
};

#endif /* IFITTINGDATASELECTOR_H_ */
