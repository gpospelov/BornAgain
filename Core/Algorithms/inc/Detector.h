// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Detector.h
//! @brief     Defines class Detector.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTOR_H_
#define DETECTOR_H_

#include "IDetectorResolution.h"
#include "DetectorParameters.h"
#include "SafePointerVector.h"
#include "EigenCore.h"


//! @class Detector
//! @ingroup simulation
//! @brief The detector with axes and resolution function.

class BA_CORE_API_ Detector : public IParameterized
{
public:

    Detector();
    Detector(const Detector& other);
    Detector& operator=(const Detector& other);

    virtual ~Detector()
    { delete mp_detector_resolution; }

    void addAxis(const IAxis& axis)
    { m_axes.push_back(axis.clone()); }

    void addAxis(const AxisParameters& axis_params);

    const IAxis& getAxis(size_t index) const;

    size_t getDimension() const
    { return m_axes.size(); }

    void clear()
    { m_axes.clear(); }

    //! Sets the detector resolution
    void setDetectorResolution(IDetectorResolution *p_detector_resolution)
    {
        delete mp_detector_resolution;
        mp_detector_resolution = p_detector_resolution;
    }

#ifndef GCCXML_SKIP_THIS
    //! Applies the detector resolution to the given intensity maps
    void applyDetectorResolution(OutputData<double> *p_scalar_intensity,
            OutputData<Eigen::Matrix2d> *p_matrix_intensity) const;
#endif

    const IDetectorResolution *getDetectorResolutionFunction() const
    { return mp_detector_resolution; }

    //! Adds parameters from local pool to external pool and call recursion over direct children.
    virtual std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

#ifndef GCCXML_SKIP_THIS
    //! Normalize intensity data with detector cell sizes.
    void normalize(OutputData<double> *p_data,
            OutputData<Eigen::Matrix2d> *p_polarized_data,
            double sin_alpha_i) const;
#endif
protected:

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}

    bool isCorrectAxisIndex(size_t index) const
    { return index<getDimension(); }

    //! Checks if data has a compatible format with the detector.
    bool dataShapeMatches(const OutputData<double> *p_data) const;

private:

    //! swap function
    void swapContent(Detector& other);

    //! Initializes axis the way IsGISAXS does
    void initializeAnglesIsgisaxs(
        AxisDouble *p_axis, const TSampledRange<double>& axis_range) const;

    //! Returns the solid angle for the given data element
    double getSolidAngle(OutputData<double> *p_data, size_t index) const;

    SafePointerVector<IAxis> m_axes;
    IDetectorResolution *mp_detector_resolution;
};

#endif /* DETECTOR_H_ */


