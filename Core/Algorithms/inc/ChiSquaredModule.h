// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ChiSquaredModule.h
//! @brief     Defines class ChiSquaredModule.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CHISQUAREDMODULE_H_
#define CHISQUAREDMODULE_H_

#include "IChiSquaredModule.h"

//! @class ChiSquaredModule
//! @ingroup algorithms
//! @brief Calculation of chi2 between two data sets

class BA_CORE_API_ ChiSquaredModule : public IChiSquaredModule
{
public:
    ChiSquaredModule() {}
    ChiSquaredModule(const ChiSquaredModule& other)
        : IChiSquaredModule(other) {}
    virtual ~ChiSquaredModule() {}

    virtual ChiSquaredModule *clone() const
    { return new ChiSquaredModule(*this); }

    //! Returns chi squared volume over experimental and simulated data.
    virtual double calculateChiSquared();

    //! Returns output data which contains chi^2 values.
    virtual OutputData<double> *createChi2DifferenceMap() const;

    //! Returns residual between data and simulation for single element.
    virtual double getResidualValue(size_t index ) const;

};

#endif /* CHISQUAREDMODULE_H_ */