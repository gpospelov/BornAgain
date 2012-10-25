#ifndef OPTICALFRESNEL_H
#define OPTICALFRESNEL_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OpticalFresnel.h
//! @brief  Definition of OpticalFresnel class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include <vector>
#include "Types.h"
#include "ISimulation.h"
#include "MultiLayer.h"



/* ************************************************************************* */
// optical fresnel coefficients
/* ************************************************************************* */
class OpticalFresnel : public ISimulation
{
public:
    OpticalFresnel();

    //! reflection/transmission fresnel coefficients
    class FresnelCoeff {
    public:
        FresnelCoeff() : kz(0), r(0), t(0), rb(0), tb(0), X(0), R(0), T(0) {}
        ~FresnelCoeff() {}
        // A - amplitude of initial wave, R, T - amplitudes of reflected and transmitted waves
        complex_t kz; // z-component of the wavevector in given layer
        complex_t r;  // r = R/A - Fresnel reflection coefficient
        complex_t t;  // t = T/A - Fresnel transmission coefficient
        complex_t rb;  // r = R/A - Fresnel reflection coefficient
        complex_t tb;  // t = T/A - Fresnel transmission coefficient
        complex_t X; //  ratio of amplitudes R/T of the outgoing to the incoming waves in layer
        complex_t R; //  ratio of amplitudes R/T of the outgoing to the incoming waves in layer
        complex_t T; //  ratio of amplitudes R/T of the outgoing to the incoming waves in layer

        //! operator is necessary to make pyplusplus/boost happy during exposing of FresnelCoeff to python using boost::vector_indexing_suite
        bool operator==(FresnelCoeff const &other) const;
    };

    //! collection of fresnel coefficients for multi layer
    class MultiLayerCoeff
    {
    public:
        inline FresnelCoeff &operator[](size_t i) { return m_data[i]; }
        inline const FresnelCoeff &operator[](size_t i) const { return m_data[i]; }
        inline size_t size() const { return m_data.size(); }
        inline void clear() { m_data.clear(); }
        inline void resize(size_t size) { m_data.resize(size); }
    private:
        std::vector<FresnelCoeff > m_data;
    };

    //typedef std::vector<FresnelCoeff > MultiLayerCoeff_t; // set of Fresnel coefficients for set of layers, [nlayer]
    typedef MultiLayerCoeff MultiLayerCoeff_t; // set of Fresnel coefficients for set of layers, [nlayer]

    //! calculate fresnel coefficients for given multi layer and kvector
    int execute(const MultiLayer &sample, const kvector_t &k, MultiLayerCoeff_t &coeff);

private:
    bool m_use_roughness;

    void calculateKZ(const MultiLayer &sample, const kvector_t &k, MultiLayerCoeff_t &coeff);
    void calculateFresnelCoefficients(MultiLayerCoeff_t &coeff);
    void calculateFresnelCoefficientsWithRoughness(const MultiLayer &sample, MultiLayerCoeff_t &coeff);
    void calculateX(const MultiLayer &sample, MultiLayerCoeff_t &coeff);
    void calculateX2(const MultiLayer &sample, MultiLayerCoeff_t &coeff);
    void calculateRT(const MultiLayer &sample, MultiLayerCoeff_t &coeff);
    void calculateRT2(const MultiLayer &sample, MultiLayerCoeff_t &coeff);
};


#endif // OPTICALFRESNEL_H
