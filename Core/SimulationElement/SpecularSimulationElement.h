// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/SpecularSimulationElement.h
//! @brief     Declares the class SpecularSimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARSIMULATIONELEMENT_H
#define SPECULARSIMULATIONELEMENT_H

#include "Complex.h"
#include "Vectors3D.h"
#include "PolarizationHandler.h"
#include <memory>

class IKzComputation;
class MultiLayer;

//! Data stucture containing both input and output of a single image pixel
//! for specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulationElement
{
public:
    SpecularSimulationElement(double kz);
    SpecularSimulationElement(double wavelength, double alpha);

    SpecularSimulationElement(const SpecularSimulationElement& other);
    SpecularSimulationElement(SpecularSimulationElement&& other) noexcept;

    ~SpecularSimulationElement();

    SpecularSimulationElement& operator=(const SpecularSimulationElement& other);

    //! Assigns PolarizationHandler.
    void setPolarizationHandler(const PolarizationHandler& handler) { m_polarization = handler; }

    //! Returns assigned PolarizationHandler.
    const PolarizationHandler& polarizationHandler() const { return m_polarization; }

    double getIntensity() const {return m_intensity;}
    void setIntensity(double intensity) {m_intensity = intensity;}

    //! Set calculation flag (if it's false, zero intensity is assigned to the element)
    void setCalculationFlag(bool calculation_flag) { m_calculation_flag = calculation_flag; }
    bool isCalculated() const { return m_calculation_flag; }

    //! Returns kz values for Abeles computation of reflection/transition coefficients
    std::vector<complex_t> produceKz(const MultiLayer& sample);

private:
    void swapContent(SpecularSimulationElement& other);

    PolarizationHandler m_polarization;
    double m_intensity; //!< simulated intensity for detector cell
    bool m_calculation_flag;
    std::function<std::vector<complex_t> (const MultiLayer&)> m_kz_computation;
};

#endif // SPECULARSIMULATIONELEMENT_H
