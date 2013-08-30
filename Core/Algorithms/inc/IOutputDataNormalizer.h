// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IOutputDataNormalizer.h
//! @brief     Defines classes IOutputDataNormalizer,
//!              OutputDataNormalizer, OutputDataSimpleNormalizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IOUTPUTDATANORMALIZER_H
#define IOUTPUTDATANORMALIZER_H

#include "IParameterized.h"
#include "OutputData.h"

//! Interface to OutputData normalizers.

class IOutputDataNormalizer : public IParameterized
{
 public:
    virtual ~IOutputDataNormalizer() {}

    virtual IOutputDataNormalizer*clone() const=0;

    virtual OutputData<double> *createNormalizedData(
            const OutputData<double>& data) const=0;

    virtual void setMaximumIntensity(double ) = 0;
};

//! Standard OutputData normalizer, with configurable max_intensity.

class BA_CORE_API_ OutputDataNormalizer : public IOutputDataNormalizer
{
 public:
    OutputDataNormalizer(double scale=1.0, double shift=0.0)
        : m_scale(scale), m_shift(shift), m_max_intensity(0.0)
    {
        setName("Normalizer");
        init_parameters();
    }

    virtual ~OutputDataNormalizer() {}

    virtual OutputDataNormalizer *clone() const;

    virtual OutputData<double> *createNormalizedData(const OutputData<double >& data) const;

    virtual void setMaximumIntensity(double max_intensity) {
        m_max_intensity = max_intensity; }

 protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    double m_scale;
    double m_shift;
    double m_max_intensity;
};

//! Simplified OutputData normalizer, with max_intensity=1.

class OutputDataSimpleNormalizer : public OutputDataNormalizer
{
 public:
    OutputDataSimpleNormalizer(double scale=1.0, double shift=0.0)
    : OutputDataNormalizer(scale, shift) { m_max_intensity = 1.0; }

    virtual ~OutputDataSimpleNormalizer() {}

    virtual void setMaximumIntensity(double max_intensity)
    { (void)max_intensity; }

    virtual OutputDataSimpleNormalizer *clone() const
    { return new OutputDataSimpleNormalizer(m_scale, m_shift); }
};

#endif // IOUTPUTDATANORMALIZER_H


