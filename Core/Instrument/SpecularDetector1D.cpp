#include "IPixel.h"

namespace {
class SpecularPixel : public IPixel
{
public:
    SpecularPixel(double alpha_i) : m_alpha_i(alpha_i) {}
    virtual ~SpecularPixel() = default;

    virtual SpecularPixel* clone() const override {return new SpecularPixel(m_alpha_i);}

    // SpecularPixel already has zero size
    virtual SpecularPixel* createZeroSizePixel(double, double) const override {return clone();}

    virtual kvector_t getK(double, double, double wavelength) const override
    {
        return vecOfLambdaAlphaPhi(wavelength, -m_alpha_i, 0.0);
    }

    virtual double getIntegrationFactor(double, double) const override {return 1;}
    virtual double getSolidAngle() const override {return 1;}

private:
    double m_alpha_i;
};
}
