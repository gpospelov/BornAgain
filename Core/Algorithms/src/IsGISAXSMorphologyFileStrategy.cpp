// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IsGISAXSMorphologyFileStrategy.cpp
//! @brief     Implements class IsGISAXSMorphologyFileStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXSMorphologyFileStrategy.h"

#include <algorithm>

IsGISAXSMorphologyFileStrategy::IsGISAXSMorphologyFileStrategy(SimulationParameters sim_params)
    : IInterferenceFunctionStrategy(sim_params), m_win_x(0.), m_win_y(0.)
{
}

void
IsGISAXSMorphologyFileStrategy::init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
                                     const SafePointerVector<IInterferenceFunction> &ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions "
                                           "for IsGISAXS morphology file strategy.");
    }
    initPositions();
}

void IsGISAXSMorphologyFileStrategy::initPositions()
{
    m_x_positions.clear();
    m_y_positions.clear();
    for (SafePointerVector<FormFactorInfo>::const_iterator it = m_ff_infos.begin();
         it != m_ff_infos.end(); ++it) {
        m_x_positions.push_back((*it)->m_pos_x);
        m_y_positions.push_back((*it)->m_pos_y);
    }
    // init window sizes for Hann function
    double x_min = *std::min_element(m_x_positions.begin(), m_x_positions.end());
    double x_max = *std::max_element(m_x_positions.begin(), m_x_positions.end());
    double y_min = *std::min_element(m_y_positions.begin(), m_y_positions.end());
    double y_max = *std::max_element(m_y_positions.begin(), m_y_positions.end());
    m_win_x = x_max - x_min;
    m_win_y = y_max - y_min;
    if (m_win_x <= 0. || m_win_y <= 0.) {
        throw Exceptions::ClassInitializationException(
            "IsGISAXSMorphologyFileStrategy::initPosition -> "
            "Hann-function window sizes should be strictly positive");
    }
}

double IsGISAXSMorphologyFileStrategy::evaluateForList(const cvector_t &k_i,
                                                       const Bin1DCVector &k_f_bin,
                                                       const std::vector<complex_t> &ff_list) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    complex_t mean_ff = complex_t(0., 0.);

    // calculate form factors
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        mean_ff += m_ff_infos[i]->m_abundance * ff_list[i];
    }

    // coherent part
    complex_t coherent_amplitude = complex_t(0., 0.);
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        double fraction = m_ff_infos[i]->m_abundance;
        double hann_value = hannFunction(m_x_positions[i], m_y_positions[i]);
        coherent_amplitude += fraction * ff_list[i] * hann_value;
    }
    double coherent_intensity = std::norm(coherent_amplitude);

    // diffuse part
    double diffuse_intensity = 0.;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        diffuse_intensity += m_ff_infos[i]->m_abundance * std::norm(ff_list[i]);
        for (size_t j = i + 1; j < m_ff_infos.size(); ++j) {
            diffuse_intensity += m_ff_infos[i]->m_abundance * m_ff_infos[j]->m_abundance * 2.0
                                 * (ff_list[i] * std::conj(ff_list[j])).real();
        }
    }
    return coherent_intensity + diffuse_intensity;
}

double IsGISAXSMorphologyFileStrategy::evaluateForMatrixList(const SimulationElement &sim_element,
                                                             const MatrixFFVector &ff_list) const
{
    double wavelength = sim_element.getWavelength();
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(wavelength, alpha_i, phi_i);
    Bin1D alpha_f_bin(sim_element.getAlphaMin(), sim_element.getAlphaMax());
    Bin1D phi_f_bin(sim_element.getPhiMin(), sim_element.getPhiMax());
    Bin1DCVector k_f_bin(wavelength, alpha_f_bin, phi_f_bin);
    cvector_t q = k_i - k_f_bin.getMidPoint();

    // coherent part
    Eigen::Matrix2cd coherent_amplitude = Eigen::Matrix2cd::Zero();
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        double fraction = m_ff_infos[i]->m_abundance;
        double hann_value = hannFunction(m_x_positions[i], m_y_positions[i]);
        coherent_amplitude += fraction * ff_list[i] * hann_value;
    }
    Eigen::Matrix2cd coh_amplitude_matrix = sim_element.getAnalyzerOperator() * coherent_amplitude
                                            * sim_element.getPolarization()
                                            * coherent_amplitude.adjoint();
    double coherent_intensity = std::abs(coh_amplitude_matrix.trace());

    // diffuse part
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    ;
    for (size_t i = 0; i < m_ff_infos.size(); ++i) {
        Eigen::Matrix2cd ff_i = ff_list[i];
        diffuse_matrix += m_ff_infos[i]->m_abundance
                          * (ff_i * sim_element.getPolarization() * ff_i.adjoint());
        for (size_t j = i + 1; j < m_ff_infos.size(); ++j) {
            Eigen::Matrix2cd ff_j = ff_list[j];
            diffuse_matrix += m_ff_infos[i]->m_abundance * m_ff_infos[j]->m_abundance * 2.0
                              * (ff_i * sim_element.getPolarization() * ff_j.adjoint());
        }
    }
    Eigen::Matrix2cd intensity_matrix = sim_element.getAnalyzerOperator() * diffuse_matrix;
    double diffuse_intensity = std::abs(intensity_matrix.trace());
    return coherent_intensity + diffuse_intensity;
}

bool IsGISAXSMorphologyFileStrategy::checkVectorSizes()
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs > 0 && n_ifs == 1);
}

double IsGISAXSMorphologyFileStrategy::hannFunction(double x, double y) const
{
    double result = (Units::PI * Units::PI / 4.0) * std::cos(Units::PI * x / m_win_x)
                    * std::cos(Units::PI * y / m_win_y);
    return result;
}
