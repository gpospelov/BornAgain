#ifndef SPECULARSIMULATIONELEMENT_H_
#define SPECULARSIMULATIONELEMENT_H_

#include "Complex.h"
#include "Vectors3D.h"
#include "PolarizationHandler.h"
#include <memory>

class IKzComputation;
class MultiLayer;

class BA_CORE_API_ SpecularSimulationElement_
{
public:
    SpecularSimulationElement_(double kz, double d_kz, double dl_l);
    SpecularSimulationElement_(double wavelength, double d_l, double alpha, double d_alpha);

    SpecularSimulationElement_(const SpecularSimulationElement_& other);
    SpecularSimulationElement_(SpecularSimulationElement_&& other) noexcept;

    ~SpecularSimulationElement_();

    SpecularSimulationElement_& operator=(const SpecularSimulationElement_& other);

    //! Assigns PolarizationHandler.
    void setPolarizationHandler(const PolarizationHandler& handler) { m_polarization = handler; }

    //! Returns assigned PolarizationHandler.
    const PolarizationHandler& polarizationHandler() const { return m_polarization; }

    double getIntensity() const {return m_intensity;}
    void setIntensity(double intensity) {m_intensity = intensity;}

    //! Set calculation flag (if it's false, zero intensity is assigned to the element)
    void setCalculationFlag(bool calculation_flag) { m_calculation_flag = calculation_flag; }
    bool isCalculated() const { return m_calculation_flag; }

    std::vector<complex_t> produceKz(const MultiLayer& sample);

private:
    void swapContent(SpecularSimulationElement_& other);

    PolarizationHandler m_polarization;
    double m_intensity; //!< simulated intensity for detector cell
    bool m_calculation_flag;
    std::unique_ptr<IKzComputation> m_kz_computation;
};

#endif // SPECULARSIMULATIONELEMENT_H_
