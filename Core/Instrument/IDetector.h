// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetector.h
//! @brief     Defines common detector interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IDETECTOR_H_
#define IDETECTOR_H_

#include "INode.h"
#include "ICloneable.h"
#include "SafePointerVector.h"
#include "IAxis.h"

//! Abstract detector interface.
//! @ingroup simulation

class BA_CORE_API_ IDetector :  public ICloneable, public INode {
public:
    IDetector() = default;

    virtual ~IDetector() = default;

    void clear() {m_axes.clear();}

    void addAxis(const IAxis& axis);

    const IAxis& getAxis(size_t index) const;

    size_t getDimension() const {return m_axes.size();}

    //! Calculate axis index for given global index
    size_t getAxisBinIndex(size_t index, size_t selected_axis) const;

    //! Returns total number of pixels
    size_t getTotalSize() const;

protected:
    IDetector(const IDetector& other);

    bool isCorrectAxisIndex(size_t index) const {return index < getDimension();}

private:
    SafePointerVector<IAxis> m_axes;
};

#endif /* IDETECTOR_H_ */
