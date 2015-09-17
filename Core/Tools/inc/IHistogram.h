// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IHistogram.h
//! @brief     Defines class IHistogram.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IHISTOGRAM_H
#define IHISTOGRAM_H

#include "OutputData.h"
#include "CumulativeValue.h"

//! @class IHistogram
//! @ingroup tools
//! @brief Base class for 1D and 2D histograms holding values of double type

class IHistogram
{
public:

    enum ProjectionType {INTEGRAL, AVERAGE};

    IHistogram(){}
    virtual ~IHistogram(){}

    IHistogram(const IAxis &axis_x);
    IHistogram(const IAxis &axis_x, const IAxis &axis_y);
    IHistogram(const OutputData<double> &source);

    //! Returns number of histogram dimensions (1 or 2).
    virtual size_t getRank() const;

    //! Returns total number of histogram bins. For 2D histograms the result will be the product
    //! of bin numbers along X and Y axes.
    virtual size_t getTotalNumberOfBins() const;

    double getBinValue(size_t binGlobalIndex) const;

    //! returns x-axis
    virtual const IAxis *getXaxis() const;

    //! returns y-axis (throws an exception for 1D histograms)
    virtual const IAxis *getYaxis() const;

    //! Returns the value on x-axis corresponding to the global bin index.
    //! @param binGlobalIndex The global bin index
    virtual double getXaxisValue(size_t binGlobalIndex);

    //! Returns the value on y-axis corresponding to the global bin index.
    //! @param globalbin The global bin index
    virtual double getYaxisValue(size_t binGlobalIndex);

    //! Reset histogram content (axes remains)
    virtual void reset();

protected:
    void check_x_axis() const;
    void check_y_axis() const;

    OutputData<CumulativeValue> m_data;
};

#endif

