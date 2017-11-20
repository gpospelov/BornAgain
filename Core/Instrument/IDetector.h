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
#include "ICloneable.h"
#include "INode.h"
#include "SafePointerVector.h"

template<class T> class OutputData;
class IAxis;
class IDetectorResolution;
class IResolutionFunction2D;
class SimulationElement;

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup simulation

// workaround for SWIG (instead of just writing enum class AxesUnits...)
struct BA_CORE_API_ AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QYQZ };
};
typedef AxesUnitsWrap::AxesUnits AxesUnits;

//! Abstract detector interface.
//! @ingroup simulation

class BA_CORE_API_ IDetector :  public ICloneable, public INode {
public:
    IDetector();

    virtual ~IDetector();

    void clear() {m_axes.clear();}

    void addAxis(const IAxis& axis);

    const IAxis& getAxis(size_t index) const;

    //! Returns actual dimensionality of the detector (number of defined axes)
    size_t dimension() const {return m_axes.size();}

    //! Calculate axis index for given global index
    size_t getAxisBinIndex(size_t index, size_t selected_axis) const;

    //! Returns total number of pixels
    size_t getTotalSize() const;

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    //! Sets the detector resolution
    void setDetectorResolution(const IDetectorResolution& p_detector_resolution);
    void setResolutionFunction(const IResolutionFunction2D& resFunc);

    //! Applies the detector resolution to the given intensity maps
    void applyDetectorResolution(OutputData<double>* p_intensity_map) const;

    //! Removes detector resolution function.
    void removeDetectorResolution();

    //! Returns a pointer to detector resolution object
    const IDetectorResolution* detectorResolution() const;

#ifndef SWIG
    //! Returns empty detector map in given axes units.
    std::unique_ptr<OutputData<double>> createDetectorMap(const Beam& beam, AxesUnits units) const;
#endif // SWIG

    //! Returns detection properties
    const DetectionProperties& detectionProperties() const {return m_detection_properties;}

    //! Inits axes of OutputData to match the detector and sets values to zero.
    virtual void initOutputData(OutputData<double>& data) const;

    //! Returns new intensity map with detector resolution applied and axes in requested units
    OutputData<double>* createDetectorIntensity(const std::vector<SimulationElement>& elements,
                                                const Beam& beam,
                                                AxesUnits units_type = AxesUnits::DEFAULT) const;

    //! Return default axes units
    virtual AxesUnits getDefaultAxesUnits() const {return AxesUnits::DEFAULT;}

    //! Returns vector of valid axes units
    virtual std::vector<AxesUnits> getValidAxesUnits() const {return {AxesUnits::NBINS};}

    virtual std::vector<const INode*> getChildren() const override;

protected:
    IDetector(const IDetector& other);

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const = 0;

    //! Calculates axis range from original detector axes in given units (mm, rad, etc)
    virtual void calculateAxisRange(size_t axis_index, const Beam& beam, AxesUnits units,
                                    double& amin, double& amax) const;

    //! Constructs axis with min, max corresponding to selected units
    virtual std::unique_ptr<IAxis> constructAxis(size_t axis_index, const Beam& beam,
                                                 AxesUnits units) const = 0;

    //! Generates an axis with correct name and default binning for given index
    virtual std::unique_ptr<IAxis> createAxis(size_t index, size_t n_bins, double min,
                                              double max) const;

private:
    //! Checks if given unit is valid for the detector. Throws exception if it is not the case.
    void checkAxesUnits(AxesUnits units) const;

    virtual void
    setDataToDetectorMap(OutputData<double>& detectorMap,
                         const std::vector<SimulationElement>& elements) const = 0;

    SafePointerVector<IAxis> m_axes;
    DetectionProperties m_detection_properties;
    std::unique_ptr<IDetectorResolution> mP_detector_resolution;
};

#endif /* IDETECTOR_H_ */
