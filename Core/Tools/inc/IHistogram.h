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
//! @brief Base class for 1D and 2D histograms

class IHistogram
{
public:
    IHistogram(){}
    IHistogram(const IAxis &axis_x);
    IHistogram(const IAxis &axis_x, const IAxis &axis_y);

protected:
    OutputData<CumulativeValue> m_data;
};

#endif

