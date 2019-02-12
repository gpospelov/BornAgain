#ifndef IKZCOMPUTATION_H
#define IKZCOMPUTATION_H

#include "Complex.h"
#include "ICloneable.h"
#include "Vectors3D.h"
#include <vector>

class MultiLayer;

class BA_CORE_API_ IKzComputation : public ICloneable
{
public:
    ~IKzComputation() override;

    //! Calculate refraction angle, expressed as k_z, for each layer.
    virtual std::vector<complex_t> compute(const MultiLayer& sample) const = 0;
    IKzComputation* clone() const override = 0;
};

class BA_CORE_API_ ReducedKzComputation
{
public:
    //! Calculate refraction angle, expressed as k_z, for each layer.
    static std::vector<complex_t> compute(const MultiLayer& sample, kvector_t k);
};

class BA_CORE_API_ KzComputation : public IKzComputation
{
public:
    KzComputation(kvector_t k);
    ~KzComputation() override = default;
    std::vector<complex_t> compute(const MultiLayer& sample) const override;
    KzComputation* clone() const override;

private:
    kvector_t m_k;
};

class BA_CORE_API_ KzFromSLDComputation : public IKzComputation
{
public:
    KzFromSLDComputation(double kz);
    ~KzFromSLDComputation() override = default;
    std::vector<complex_t> compute(const MultiLayer& sample) const override;
    KzFromSLDComputation* clone() const override;

private:
    double m_kz;
};

#endif // IKZCOMPUTATION_H
