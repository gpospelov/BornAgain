// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DetectorMask.h
//! @brief     Defines class DetectorMask.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTORMASK_H
#define DETECTORMASK_H

#include "WinDllMacros.h"
#include "SafePointerVector.h"
#include "OutputData.h"
#include <map>

namespace Geometry {
class IShape2D;
}

class Detector;

//! @class DetectorMask
//! @ingroup simulation
//! @brief The container with all masks

class BA_CORE_API_ DetectorMask
{
public:
    DetectorMask();

    //! Add mask to the stack of detector masks. The value "true" means that the area will
    //! be excluded from the analysis.
    //! @param shape The shape of mask.
    //! @param mask_value The value of mask
    void addMask(const Geometry::IShape2D &shape, bool mask_value);

    //! Init the map of masks for the whole detector plane
    void initMaskData(const Detector &detector);

    bool getMask(size_t index);

    const OutputData<bool>* getMaskData() const;

private:
    SafePointerVector<Geometry::IShape2D> m_shapes;
    std::map<const Geometry::IShape2D *, bool> m_shape_to_mask;
    OutputData<bool> m_mask_data;
};

#endif

