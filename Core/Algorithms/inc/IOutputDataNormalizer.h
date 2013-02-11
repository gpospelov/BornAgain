#ifndef IOUTPUTDATANORMALIZER_H
#define IOUTPUTDATANORMALIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IOutputDataNormalizer.h
//! @brief  Definition of IOutputDataNormalizer class
//! @author Scientific Computing Group at FRM II
//! @date   26.11.2012

#include "IParameterized.h"
#include "OutputData.h"

/* ************************************************************************* */
// Normalize output data
/* ************************************************************************* */
class IOutputDataNormalizer : public IParameterized
{
public:
    virtual ~IOutputDataNormalizer() {}
    virtual IOutputDataNormalizer*clone() const=0;

    virtual OutputData<double> *createNormalizedData(const OutputData<double > &data) const=0;

    virtual void setMaximumIntensity(double ) = 0;

};


class OutputDataNormalizer : public IOutputDataNormalizer
{
public:
    OutputDataNormalizer(double scale=1.0, double shift=0.0);
    virtual ~OutputDataNormalizer() {}

    virtual OutputDataNormalizer *clone() const;

    virtual OutputData<double> *createNormalizedData(const OutputData<double > &data) const;

    virtual void setMaximumIntensity(double max_intensity) { m_max_intensity = max_intensity; }

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    double m_scale;
    double m_shift;
    double m_max_intensity;
};


class OutputDataSimpleNormalizer : public OutputDataNormalizer
{
public:
    OutputDataSimpleNormalizer(double scale=1.0, double shift=0.0) : OutputDataNormalizer(scale, shift) {
        m_max_intensity = 1.0;
    }

    virtual ~OutputDataSimpleNormalizer(){}
    virtual void setMaximumIntensity(double max_intensity) {  (void)max_intensity; }
    virtual OutputDataSimpleNormalizer *clone() const
    {
        return new OutputDataSimpleNormalizer(m_scale, m_shift);
    }

};



#endif // IOUTPUTDATANORMALIZER_H
