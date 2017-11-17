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

#include "DetectionProperties.h"
#include "IAxis.h"
#include "ICloneable.h"
#include "INode.h"
#include "SafePointerVector.h"

template<class T> class OutputData;

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup simulation

// workaround for SWIG (instead of just writing enum class DetectorAxesUnits...)
struct BA_CORE_API_ DetectorAxesUnitsWrap {
    enum DetectorAxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QYQZ };
};
typedef DetectorAxesUnitsWrap::DetectorAxesUnits DetectorAxesUnits;

//! Abstract detector interface.
//! @ingroup simulation

class BA_CORE_API_ IDetector :  public ICloneable, public INode {
public:
    IDetector();

    virtual ~IDetector() = default;

    void clear() {m_axes.clear();}

    void addAxis(const IAxis& axis);

    const IAxis& getAxis(size_t index) const;

    size_t getDimension() const {return m_axes.size();}

    //! Calculate axis index for given global index
    size_t getAxisBinIndex(size_t index, size_t selected_axis) const;

    //! Returns total number of pixels
    size_t getTotalSize() const;

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    //! Returns detection properties
    const DetectionProperties& detectionProperties() const {return m_detection_properties;}

    //! Inits axes of OutputData to match the detector and sets values to zero.
    virtual void initOutputData(OutputData<double>& data) const;

    //! Return default axes units
    virtual DetectorAxesUnits getDefaultAxesUnits() const {return DetectorAxesUnits::DEFAULT;}

    //! Returns vector of valid axes units
    virtual std::vector<DetectorAxesUnits> getValidAxesUnits() const {return {DetectorAxesUnits::NBINS};}

    virtual std::vector<const INode*> getChildren() const;

protected:
    IDetector(const IDetector& other);

    bool isCorrectAxisIndex(size_t index) const {return index < getDimension();}

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const = 0;

    //! Generates an axis with correct name and default binning for given index
    virtual IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const;

    //! Checks if given unit is valid for the detector. Throws exception if it is not the case.
    void checkAxesUnits(DetectorAxesUnits units) const;

private:
    SafePointerVector<IAxis> m_axes;
    DetectionProperties m_detection_properties;
};

#endif /* IDETECTOR_H_ */
