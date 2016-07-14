// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/IDetector2D.h
//! @brief     Declares interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IDETECTOR2D_H
#define IDETECTOR2D_H

#include "Beam.h"
#include "DetectorMask.h"
#include "IDetectorResolution.h"
#include "SimulationElement.h"



//! @class IDetector
//! @ingroup simulation
//! @brief The detector interface.

class BA_CORE_API_ IDetector2D : public IParameterized
{
public:
    enum EAxesUnits {DEFAULT, NBINS, RADIANS, DEGREES, MM, QYQZ};

    IDetector2D();
    IDetector2D(const IDetector2D& other);

    virtual IDetector2D* clone() const=0;

    virtual ~IDetector2D() {}

    //! Inits detector with the beam settings
    virtual void init(const Beam& beam);

    void addAxis(const IAxis& axis);

    const IAxis& getAxis(size_t index) const;

    size_t getDimension() const;

    void clear();

    //! Sets detector parameters using axes of output data
    void matchDetectorAxes(const OutputData<double>& output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_x, double x_min, double x_max,
                               size_t n_y, double y_min, double y_max);

    //! Sets detector parameters using axes
    void setDetectorAxes(const IAxis& axis0, const IAxis& axis1);

    //! Sets the detector resolution
    void setDetectorResolution(IDetectorResolution* p_detector_resolution);

    //! Applies the detector resolution to the given intensity maps
    void applyDetectorResolution(OutputData<double>* p_intensity_map) const;

    const IDetectorResolution* getDetectorResolutionFunction() const;

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission=1.0);

#ifndef SWIG
    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const;
#endif

    //! removes all masks from the detector
    void removeMasks();

    //! Adds mask of given shape to the stack of detector masks. The mask value 'true' means
    //! that the channel will be excluded from the simulation. The mask which is added last
    //! has priority.
    //! @param shape The shape of mask (Rectangle, Polygon, Line, Ellipse)
    //! @param mask_value The value of mask
    void addMask(const Geometry::IShape2D& shape, bool mask_value = true);

    //! Put the mask for all detector channels (i.e. exclude whole detector from the analysis)
    void maskAll();

    const DetectorMask* getDetectorMask() const;

    int getNumberOfMaskedChannels() const;


    bool isMasked(size_t index) const;

    //! return true if has masks
    bool hasMasks() const;

#ifndef SWIG
    //! Create a vector of SimulationElement objects according to the detector and its mask
    std::vector<SimulationElement> createSimulationElements(const Beam& beam);
    SimulationElement getSimulationElement(size_t index, const Beam& beam) const;
#endif

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool* external_pool,
                                                    int copy_number = -1) const;

    //! Returns detector map in given axes units
    virtual OutputData<double>* createDetectorMap(const Beam& beam, EAxesUnits units_type) const;

    //! returns vector of valid axes units
    virtual std::vector<EAxesUnits> getValidAxesUnits() const;

    //! return default axes units
    virtual EAxesUnits getDefaultAxesUnits() const;

protected:
    //! Create an IPixelMap for the given OutputData object and index
    virtual IPixelMap* createPixelMap(size_t index) const=0;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}

    //! Generates an axis with correct name and default binning for given index
    virtual IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const=0;

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const=0;

    bool isCorrectAxisIndex(size_t index) const;

    //! Returns true if data has a compatible format with the detector.
    bool dataShapeMatches(const OutputData<double>* p_data) const;

    //! Initialize polarization (for constructors)
    void initPolarizationOperator();

    //! Calculate axis index for given global index
    size_t getAxisBinIndex(size_t index, size_t selected_axis) const;

    //! swap function
    void swapContent(IDetector2D& other);

    SafePointerVector<IAxis> m_axes;
    std::unique_ptr<IDetectorResolution> mP_detector_resolution;
#ifndef SWIG
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
#endif
    DetectorMask m_detector_mask;
private:
    //! Verify if the given analyzer properties are physical
    bool checkAnalyzerProperties(const kvector_t direction, double efficiency,
                                 double total_transmission) const;

#ifndef SWIG
    Eigen::Matrix2cd calculateAnalyzerOperator(
        const kvector_t direction, double efficiency, double total_transmission = 1.0) const;
#endif
};

inline void IDetector2D::addAxis(const IAxis& axis)
{
    m_axes.push_back(axis.clone());
}

inline size_t IDetector2D::getDimension() const
{
    return m_axes.size();
}

inline void IDetector2D::clear()
{
    m_axes.clear();
}

inline void IDetector2D::setDetectorResolution(IDetectorResolution* p_detector_resolution)
{
    if (mP_detector_resolution.get()!=p_detector_resolution) {
        mP_detector_resolution.reset(p_detector_resolution);
    }
}

inline const IDetectorResolution* IDetector2D::getDetectorResolutionFunction() const
{
    return mP_detector_resolution.get();
}

#ifndef SWIG
inline Eigen::Matrix2cd IDetector2D::getAnalyzerOperator() const
{
    return m_analyzer_operator;
}
#endif

inline bool IDetector2D::isCorrectAxisIndex(size_t index) const
{
    return index < getDimension();
}

#endif // IDETECTOR2D_H
