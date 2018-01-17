// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpecularDetector1D.h
//! @brief     Defines a detector for specular simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDETECTOR1D_H_
#define SPECULARDETECTOR1D_H_

#include "IDetector.h"

//! 1D detector for specular simulations
//! @ingroup simulation

class BA_CORE_API_ SpecularDetector1D : public IDetector {
public:
    SpecularDetector1D(const IAxis& axis);
    virtual ~SpecularDetector1D();

    SpecularDetector1D* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Returns detector masks container.
    const DetectorMask* detectorMask() const override { return nullptr; }

#ifndef SWIG
    //! Create a vector of SimulationElement objects according to the detector
    std::vector<SimulationElement> createSimulationElements(const Beam& beam) override;

    //! Create a vector of DetectorElement objects according to the detector
    std::vector<DetectorElement> createDetectorElements(const Beam& beam) override;
#endif // SWIG

    //! Returns region of interest if exists.
    const RegionOfInterest* regionOfInterest() const override { return nullptr; }

    void resetRegionOfInterest() override {}

    //! Return default axes units
    AxesUnits defaultAxesUnits() const override;

    //! Returns vector of valid axes units
    std::vector<AxesUnits> validAxesUnits() const override;

protected:
    SpecularDetector1D(const SpecularDetector1D& other);

    //! Returns the name for the axis with given index
    std::string axisName(size_t index) const override;

    //! Calculates axis range from original detector axes in given units (mm, rad, etc)
    void calculateAxisRange(size_t axis_index, const Beam& beam, AxesUnits units,
                                    double& amin, double& amax) const override;

private:
    double alphaI(size_t index) const;
};

#endif /* SPECULARDETECTOR1D_H_ */
