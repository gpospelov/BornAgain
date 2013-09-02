// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/MultiLayerDWBASimulation.cpp
//! @brief     Implements class MultiLayerDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerDWBASimulation.h"

#include "SpecularMatrix.h"
#include "SpecularMagnetic.h"
#include "MultiLayer.h"
#include "DoubleToComplexInterpolatingFunction.h"
#include "MultiLayerRoughnessDWBASimulation.h"
#include "DoubleToComplexMap.h"
#include "MessageService.h"
#include "MagneticCoefficientsMap.h"

#include <boost/scoped_ptr.hpp>


MultiLayerDWBASimulation::MultiLayerDWBASimulation(
        const MultiLayer* p_multi_layer)
  : mp_roughness_dwba_simulation(0)
{
    mp_multi_layer = p_multi_layer->clone();
}

MultiLayerDWBASimulation::~MultiLayerDWBASimulation()
{
    delete mp_multi_layer;
    for(std::map<size_t, LayerDWBASimulation*>::iterator it =
            m_layer_dwba_simulation_map.begin();
        it!=m_layer_dwba_simulation_map.end(); ++it)
    {
        delete (*it).second;
    }
    delete mp_roughness_dwba_simulation;
}

void MultiLayerDWBASimulation::init(const Simulation& simulation)
{
    msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::init()";
    DWBASimulation::init(simulation);
    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        LayerDWBASimulation *p_layer_dwba_sim =
            mp_multi_layer->getLayer(i)->createDWBASimulation();
        if (p_layer_dwba_sim) {
            m_layer_dwba_simulation_map[i] = p_layer_dwba_sim;
            p_layer_dwba_sim->init(simulation);
        }
    }
    // scattering from rough surfaces in DWBA
    for (size_t i=0; i<mp_multi_layer->getNumberOfInterfaces(); ++i) {
        if(mp_multi_layer->getLayerInterface(i)->getRoughness() ) {
            mp_roughness_dwba_simulation =
                new MultiLayerRoughnessDWBASimulation(mp_multi_layer);
            mp_roughness_dwba_simulation->init(simulation);
            break;
        }
    }
}

void MultiLayerDWBASimulation::setThreadInfo(const ThreadInfo& thread_info)
{
    DWBASimulation::setThreadInfo(thread_info);
    for (std::map<size_t, LayerDWBASimulation*>::iterator it =
             m_layer_dwba_simulation_map.begin();
         it != m_layer_dwba_simulation_map.end(); ++it) {
        it->second->setThreadInfo(thread_info);
    }
    if (mp_roughness_dwba_simulation) {
        mp_roughness_dwba_simulation->setThreadInfo(thread_info);
    }
}

void MultiLayerDWBASimulation::run()
{
    msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run() -> Running thread "
                       << m_thread_info.current_thread;
    if (mp_polarization_output) {
        runMagnetic();
        return;
    }
    SpecularMatrix specularCalculator;

    kvector_t m_ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());

    m_dwba_intensity.setAllTo(0.0);
    double lambda = 2*M_PI/m_ki_real.mag();

    // collect all alpha angles and calculate reflection/transmission
    // coefficients
    typedef std::pair<double, SpecularMatrix::MultiLayerCoeff_t>
        doubleRTCoeffPair_t;
    std::vector<doubleRTCoeffPair_t> doubleRTCoeff_buffer;
    std::set<double> alpha_set = getAlphaList();
    // also add incoming alpha
    alpha_set.insert(-m_alpha_i);
    doubleRTCoeff_buffer.reserve(alpha_set.size());

    double angle;
    kvector_t kvec;
    SpecularMatrix::MultiLayerCoeff_t coeffs;
    for (std::set<double>::const_iterator it =
             alpha_set.begin(); it != alpha_set.end(); ++it) {
        angle = *it;
        kvec.setLambdaAlphaPhi(lambda, -angle, 0.0);
        specularCalculator.execute(*mp_multi_layer, kvec, coeffs);
        doubleRTCoeff_buffer.push_back( doubleRTCoeffPair_t(angle,coeffs) );
    }

    // run through layers and construct T,R functions
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run() -> Layer " << i_layer;
        DoubleToPairOfComplexMap RT_map;
        DoubleToComplexMap Kz_map;

        for(std::vector<doubleRTCoeffPair_t >::const_iterator it=
                doubleRTCoeff_buffer.begin();
            it!=doubleRTCoeff_buffer.end(); ++it) {
            double angle = (*it).first;
            const ScalarRTCoefficients& coeff = (*it).second[i_layer];
            RT_map[angle] = complexpair_t(coeff.R(), coeff.T());
            Kz_map[angle] = coeff.kz;
        }

        // layer DWBA simulation
        std::map<size_t, LayerDWBASimulation*>::const_iterator pos =
            m_layer_dwba_simulation_map.find(i_layer);
        if(pos != m_layer_dwba_simulation_map.end() ) {
            LayerDWBASimulation *p_layer_dwba_sim = pos->second;
            p_layer_dwba_sim->setKzAndRTFunctions(Kz_map, RT_map);
            p_layer_dwba_sim->run();
            addDWBAIntensity( p_layer_dwba_sim->getDWBAIntensity() );
        }

        // layer roughness DWBA
        if(mp_roughness_dwba_simulation) {
            mp_roughness_dwba_simulation->setReflectionTransmissionFunction
                (i_layer, RT_map);
        }

    } // i_layer

    if(mp_roughness_dwba_simulation) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run() -> roughness";
        mp_roughness_dwba_simulation->run();
        addDWBAIntensity( mp_roughness_dwba_simulation->getDWBAIntensity() );
    }
}

void MultiLayerDWBASimulation::runMagnetic()
{
    SpecularMagnetic specularCalculator;

    kvector_t m_ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());

    m_dwba_intensity.setAllTo(0.0);
    mp_polarization_output->setAllTo(Eigen::Matrix2d::Zero());
    double lambda = 2*M_PI/m_ki_real.mag();

    // collect all (alpha, phi) angles and calculate reflection/transmission
    // coefficients (also one set of coefficients for the incoming wavevector)
    typedef Utils::UnorderedMap<double, SpecularMagnetic::MultiLayerCoeff_t>
        container_phi_t;
    typedef Utils::UnorderedMap<double, container_phi_t> container_t;

    container_t multi_layer_coeff_buffer;
    std::set<double> alpha_set = getAlphaList();
    std::set<double> phi_set = getPhiList();

    double alpha, phi;
    kvector_t kvec;
    container_phi_t phi_coeffs;
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    // the coefficients for the incoming wavevector are calculated on the
    // sample with inverted magnetic field:
    boost::scoped_ptr<MultiLayer> P_inverted_B_multi_layer(
            mp_multi_layer->cloneInvertB());
    for (std::set<double>::const_iterator it_alpha =
             alpha_set.begin(); it_alpha != alpha_set.end(); ++it_alpha) {
        alpha = *it_alpha;
        phi_coeffs.clear();
        for (std::set<double>::const_iterator it_phi =
             phi_set.begin(); it_phi != phi_set.end(); ++it_phi) {
            phi = *it_phi;
            kvec.setLambdaAlphaPhi(lambda, alpha, phi);
            specularCalculator.execute(*P_inverted_B_multi_layer, -kvec, coeffs);
            phi_coeffs[phi] = coeffs;
        }
        multi_layer_coeff_buffer[alpha] = phi_coeffs;
    }
    // the coefficients for the incoming wavevector are calculated on the
    // original sample
    specularCalculator.execute(*mp_multi_layer, m_ki_real, coeffs);

    // run through layers and add DWBA from each layer
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::runMagnetic()"
                "-> Layer " << i_layer;
        MagneticCoefficientsMap coeff_map;

        // construct the reflection/transmission coefficients for this layer
        for(Utils::UnorderedMap<double, container_phi_t>::const_iterator
                it_alpha = multi_layer_coeff_buffer.begin();
                it_alpha!=multi_layer_coeff_buffer.end(); ++it_alpha) {
            alpha = (*it_alpha).first;
            MagneticCoefficientsMap::container_phi_t phi_layer_coeffs;
            phi_layer_coeffs.clear();
            for (Utils::UnorderedMap<double, SpecularMagnetic::
                    MultiLayerCoeff_t>::const_iterator it_phi =
                            (*it_alpha).second.begin();
                    it_phi != (*it_alpha).second.end(); ++it_phi) {
                phi = (*it_phi).first;
                const MatrixRTCoefficients& coeff =
                        (*it_phi).second[i_layer];
                phi_layer_coeffs[phi] = coeff;
            }
            coeff_map[alpha] = phi_layer_coeffs;
        }
        // add reflection/transmission coeffs from incoming beam
        coeff_map.incomingCoeff() = coeffs[i_layer];

        // layer DWBA simulation
        std::map<size_t, LayerDWBASimulation*>::const_iterator pos =
            m_layer_dwba_simulation_map.find(i_layer);
        if(pos != m_layer_dwba_simulation_map.end() ) {
            LayerDWBASimulation *p_layer_dwba_sim = pos->second;
            p_layer_dwba_sim->setMagneticCoefficientsMap(coeff_map);
            p_layer_dwba_sim->run();
            addPolarizedDWBAIntensity(
                    p_layer_dwba_sim->getPolarizedDWBAIntensity() );
        }
    } // i_layer
}

std::set<double> MultiLayerDWBASimulation::getAlphaList() const
{
    std::set<double> result;
    const IAxis *p_alpha_axis = getDWBAIntensity().getAxis("alpha_f");
    for (size_t i=0; i<p_alpha_axis->getSize(); ++i) {
        Bin1D alpha_bin = p_alpha_axis->getBin(i);
        result.insert(alpha_bin.m_lower);
        result.insert(alpha_bin.getMidPoint());
        result.insert(alpha_bin.m_upper);
    }
    return result;
}

std::set<double> MultiLayerDWBASimulation::getPhiList() const
{
    std::set<double> result;
    const IAxis *p_phi_axis = getDWBAIntensity().getAxis("phi_f");
    for (size_t i=0; i<p_phi_axis->getSize(); ++i) {
        Bin1D phi_bin = p_phi_axis->getBin(i);
        result.insert(phi_bin.m_lower);
        result.insert(phi_bin.getMidPoint());
        result.insert(phi_bin.m_upper);
    }
    return result;
}
