// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorSphereGaussianRadius.h
//! @brief     Defines and implements (WHY ??) class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHEREGAUSSIANRADIUS_H_
#define FORMFACTORSPHEREGAUSSIANRADIUS_H_
#include "MathFunctions.h"

#include "IFormFactor.h"
#include "FormFactorFullSphere.h"
#include <cassert>

//! Form factor of ??

class BA_CORE_API_ FormFactorSphereGaussianRadius : public IFormFactorBorn
{
 public:
    FormFactorSphereGaussianRadius(double mean, double sigma);
    virtual FormFactorSphereGaussianRadius *clone() const;
    virtual ~FormFactorSphereGaussianRadius();

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const;
    virtual bool isDistributedFormFactor() const { return true; }
    virtual void createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const;

    virtual double getHeight() const { return p_ff_sphere->getHeight(); }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

 private:
    double calculateMeanR3() const;

    double m_mean; //!< This is the mean radius
    double m_sigma;
    double m_mean_r3; //!< This is the radius that gives the mean volume
    FormFactorFullSphere *p_ff_sphere;
    cvector_t m_zero_vector;
};

inline FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean, double sigma)
: m_mean(mean)
, m_sigma(sigma)
, m_mean_r3(0.0)
, p_ff_sphere(0)
, m_zero_vector(0.0, 0.0, 0.0)
{
    setName("FormFactorSphereGaussianRadius");
    m_mean_r3 = calculateMeanR3();
    p_ff_sphere = new FormFactorFullSphere(m_mean_r3);
}

inline FormFactorSphereGaussianRadius* FormFactorSphereGaussianRadius::clone() const
{
    FormFactorSphereGaussianRadius *result =
        new FormFactorSphereGaussianRadius(m_mean, m_sigma);
    result->setName(getName());
    return result;
}

inline FormFactorSphereGaussianRadius::~FormFactorSphereGaussianRadius()
{
    delete p_ff_sphere;
}
inline int FormFactorSphereGaussianRadius::getNumberOfStochasticParameters() const
{
    return 2;
}

inline complex_t FormFactorSphereGaussianRadius::evaluate_for_q(const cvector_t& q) const
{
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double dw = std::exp(-q2*m_sigma*m_sigma/2.0);
    return dw*p_ff_sphere->evaluate_for_q(q);
}

inline double FormFactorSphereGaussianRadius::calculateMeanR3() const
{
    return std::pow(m_mean*(m_mean*m_mean+3.0*m_sigma*m_sigma),1.0/3.0);
}

inline void FormFactorSphereGaussianRadius::createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const
{
    double sigma_range = 2.0*m_sigma;
    double step = 2.0*sigma_range/(nbr_samples-1.0);
    double radius_start = m_mean-step*(nbr_samples/2); // 2 and not 2. is on purpose
    double total_prob = 0.0;
    for (size_t i=0; i<nbr_samples; ++i) {
        double radius = radius_start + (double)i*step;
        double probability = MathFunctions::Gaussian(radius, m_mean, m_sigma);
        form_factors.push_back(new FormFactorFullSphere(radius));
        probabilities.push_back(probability);
        total_prob += probability;
    }
    assert(total_prob);
    for (size_t i=0; i<probabilities.size(); ++i) {
        probabilities[i] /= total_prob;
    }
}

#endif /* FORMFACTORSPHEREGAUSSIANRADIUS_H_ */


