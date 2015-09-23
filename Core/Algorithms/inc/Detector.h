// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Detector.h
//! @brief     Defines class Detector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTOR_H_
#define DETECTOR_H_

#include "IDetectorResolution.h"
#include "SafePointerVector.h"
#include "EigenCore.h"

//! @class Detector
//! @ingroup simulation
//! @brief The detector with axes and resolution function.

class BA_CORE_API_ Detector : public IParameterized
{
public:
    Detector();
    Detector(const Detector &other);
    Detector &operator=(const Detector &other);

    virtual ~Detector()
    {
        delete mp_detector_resolution;
    }

    void addAxis(const IAxis &axis)
    {
        m_axes.push_back(axis.clone());
    }

    const IAxis &getAxis(size_t index) const;

    size_t getDimension() const
    {
        return m_axes.size();
    }

    void clear()
    {
        m_axes.clear();
    }

    //! Sets the detector resolution
    void setDetectorResolution(IDetectorResolution *p_detector_resolution)
    {
        delete mp_detector_resolution;
        mp_detector_resolution = p_detector_resolution;
    }

    //! Applies the detector resolution to the given intensity maps
    void applyDetectorResolution(OutputData<double> *p_scalar_intensity) const;

    const IDetectorResolution *getDetectorResolutionFunction() const
    {
        return mp_detector_resolution;
    }

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t &direction, double efficiency,
                               double total_transmission=1.0);

#ifndef GCCXML_SKIP_THIS
    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const
    {
        return m_analyzer_operator;
    }
#endif

    //! Adds parameters from local pool to external pool and call recursion over direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

    //! Normalize intensity data with detector cell sizes.
    void normalize(OutputData<double> *p_data, double sin_alpha_i) const;

protected:
    virtual void print(std::ostream &ostr) const;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters()
    {
    }

    bool isCorrectAxisIndex(size_t index) const
    {
        return index < getDimension();
    }

    //! Checks if data has a compatible format with the detector.
    bool dataShapeMatches(const OutputData<double> *p_data) const;

private:
    //! swap function
    void swapContent(Detector &other);

    //! Returns the solid angle for the given data element
    double getSolidAngle(OutputData<double> *p_data, size_t index) const;

    //! Initialize polarization (for constructors)
    void initPolarizationOperator();

    //! Verify if the given analyzer properties are physical
    bool checkAnalyzerProperties(const kvector_t &direction, double efficiency,
                                 double total_transmission) const;

#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd calculateAnalyzerOperator(const kvector_t &direction, double efficiency,
                                               double total_transmission = 1.0) const;
#endif

    SafePointerVector<IAxis> m_axes;
    IDetectorResolution *mp_detector_resolution;
#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
#endif
};

#endif /* DETECTOR_H_ */
