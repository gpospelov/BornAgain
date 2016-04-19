// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/IOutputDataNormalizer.h
//! @brief     Declares classes IOutputDataNormalizer,
//!              OutputDataNormalizer, OutputDataSimpleNormalizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IINTENSITYNORMALIZER_H
#define IINTENSITYNORMALIZER_H

#include "IParameterized.h"
#include "OutputData.h"


//! @class IIntensityNormalizer
//! @ingroup algorithms_internal
//! @brief Interface to OutputData normalizers.

class BA_CORE_API_ IIntensityNormalizer : public IParameterized
{
public:
    virtual ~IIntensityNormalizer() {}

    virtual IIntensityNormalizer*clone() const=0;

    virtual OutputData<double> *createNormalizedData(
            const OutputData<double>& data) const=0;

    virtual void apply(OutputData<double> &data) const=0;

    virtual void setMaximumIntensity(double ) = 0;
};


//! @class IntensityNormalizer
//! @ingroup algorithms_internal
//! @brief Standard OutputData normalizer, with configurable max_intensity.

class BA_CORE_API_ IntensityNormalizer : public IIntensityNormalizer
{
public:
    IntensityNormalizer(double scale=1.0, double shift=0.0)
        : m_scale(scale), m_shift(shift), m_max_intensity(0.0)
    {
        setName("Normalizer");
        init_parameters();
    }

    virtual ~IntensityNormalizer() {}

    virtual IntensityNormalizer *clone() const;

    virtual OutputData<double> *createNormalizedData(const OutputData<double >& data) const;

    virtual void apply(OutputData<double> &data) const;

    virtual void setMaximumIntensity(double max_intensity) {
        m_max_intensity = max_intensity; }

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    double m_scale;
    double m_shift;
    double m_max_intensity;
};


//! @class IntensityScaleAndShiftNormalizer
//! @ingroup algorithms_internal
//! @brief Simplified OutputData normalizer, with max_intensity=1.

class BA_CORE_API_ IntensityScaleAndShiftNormalizer : public IntensityNormalizer
{
public:
    IntensityScaleAndShiftNormalizer(double scale=1.0, double shift=0.0)
    : IntensityNormalizer(scale, shift) { m_max_intensity = 1.0; }

    virtual ~IntensityScaleAndShiftNormalizer() {}

    virtual void setMaximumIntensity(double max_intensity)
    { (void)max_intensity; }

    virtual IntensityScaleAndShiftNormalizer *clone() const
    { return new IntensityScaleAndShiftNormalizer(m_scale, m_shift); }
};

#endif // IINTENSITYNORMALIZER_H
