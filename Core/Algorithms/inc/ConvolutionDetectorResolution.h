// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ConvolutionDetectorResolution.h
//! @brief     Defines class ConvolutionDetectorResolution.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef CONVOLUTIONDETECTORRESOLUTION_H_
#define CONVOLUTIONDETECTORRESOLUTION_H_

#include "IDetectorResolution.h"
#include "IResolutionFunction2D.h"

//! Convolutes the intensity in 1 or 2 dimensions with a resolution function.

//! Limitation: this class assumes that the data points are evenly
//! distributed on each axis

class ConvolutionDetectorResolution : public IDetectorResolution
{
public:
    typedef double (*cumulative_DF_1d)(double);
    //! Constructor taking a 1 dimensional resolution function as argument
    ConvolutionDetectorResolution(cumulative_DF_1d res_function_1d);
    //! Constructor taking a 2 dimensional resolution function as argument
    ConvolutionDetectorResolution(IResolutionFunction2D *p_res_function_2d);
    //! Destructor
    virtual ~ConvolutionDetectorResolution();

    //! Apply the encapsulated resolution function to the given intensity map by using a convolution
    virtual void applyDetectorResolution(OutputData<double> *p_intensity_map) const;

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

    //! clone object
    virtual ConvolutionDetectorResolution *clone() const;

protected:
    ConvolutionDetectorResolution(const ConvolutionDetectorResolution &other);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
//    //! hiding copy constructor and disabling assignment operator
//    ConvolutionDetectorResolution &operator=(const ConvolutionDetectorResolution &);

    void apply1dConvolution(OutputData<double> *p_intensity_map) const;
    void apply2dConvolution(OutputData<double> *p_intensity_map) const;
    double getIntegratedPDF1d(double x, double step) const;
    double getIntegratedPDF2d(double x, double step_x, double y, double step_y) const;

    size_t m_dimension;
    cumulative_DF_1d m_res_function_1d;
    IResolutionFunction2D *mp_res_function_2d;
};

#endif /* CONVOLUTIONDETECTORRESOLUTION_H_ */
