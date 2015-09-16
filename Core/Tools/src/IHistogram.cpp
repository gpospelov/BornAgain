// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IntensityDataObject.cpp
//! @brief     Implements class IntensityDataObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IHistogram.h"
#include "FixedBinAxis.h"
#include "VariableBinAxis.h"


IHistogram::IHistogram(const IAxis &axis_x)
{
    m_data.addAxis(axis_x);
}

IHistogram::IHistogram(const IAxis &axis_x, const IAxis &axis_y)
{
    m_data.addAxis(axis_x);
    m_data.addAxis(axis_y);
}
