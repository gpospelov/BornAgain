// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/SpecularSimulationElement.h
//! @brief     Defines class SpecularSimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARSIMULATIONELEMENT_H_
#define SPECULARSIMULATIONELEMENT_H_

#include "Complex.h"
#include "Vectors3D.h"
#include "PolarizationHandler.h"
#include "SpecularData.h"
#include <memory>

//! Data stucture containing both input and output of a single image pixel
//! for specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulationElement
{
public:
    SpecularSimulationElement(double wavelength, double alpha_i);
    SpecularSimulationElement(const SpecularSimulationElement& other);
    SpecularSimulationElement(SpecularSimulationElement&& other) noexcept;

    ~SpecularSimulationElement();

    SpecularSimulationElement& operator=(const SpecularSimulationElement& other);

    //! Assigns PolarizationHandler.
    void setPolarizationHandler(const PolarizationHandler& handler)
    {
        m_polarization = handler;
    }

    //! Returns assigned PolarizationHandler.
    const PolarizationHandler& polarizationHandler() const
    {
        return m_polarization;
    }

    double getWavelength() const { return m_wavelength; }
    double getAlphaI() const { return m_alpha_i; }
    kvector_t getKi() const;
    void setIntensity(double intensity) { m_intensity = intensity; }
    void addIntensity(double intensity) { m_intensity += intensity; }
    double getIntensity() const { return m_intensity; }

    //! Returns specular data container
    const SpecularData& specularData() const { return m_specular_data; }

    //! Set specular data
    void setSpecular(SpecularData specular_data);

    //! Set calculation flag (if it's false, zero intensity is assigned to the element)
    void setCalculationFlag(bool calculation_flag) {m_calculation_flag = calculation_flag;}
    bool isCalculated() const {return m_calculation_flag;}

private:
    void swapContent(SpecularSimulationElement& other);

    PolarizationHandler m_polarization;
    double m_wavelength, m_alpha_i;  //!< the wavelength and the incident angle of the beam
    double m_intensity;                      //!< simulated intensity for detector cell

    // TODO: remove this when we have a simulation type that generates intensity as a function
    //       of depth and inclination angle
    SpecularData m_specular_data;
    bool m_calculation_flag;
};

#endif /* SPECULARSIMULATIONELEMENT_H_ */
