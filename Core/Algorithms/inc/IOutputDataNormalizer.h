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
class IOutputDataNormalizer : public IParameterized, public ICloneable
{
public:
    virtual ~IOutputDataNormalizer() {}
    virtual IOutputDataNormalizer*clone() const=0;

    virtual OutputData<double> *createNormalizedData(const OutputData<double > &data) const=0;
};



class OutputDataNormalizerScaleAndShift : public IOutputDataNormalizer
{
public:
    OutputDataNormalizerScaleAndShift();
    OutputDataNormalizerScaleAndShift(double scale, double shift, double max_intensity=0);
    virtual ~OutputDataNormalizerScaleAndShift() {}

    virtual OutputData<double> *createNormalizedData(const OutputData<double > &data) const;

    virtual OutputDataNormalizerScaleAndShift *clone() const;

    void setMaximumIntensity(double max_intensity) { m_max_intensity = max_intensity; }

protected:

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_scale;
    double m_shift;
    double m_max_intensity;
};



#endif // IOUTPUTDATANORMALIZER_H
