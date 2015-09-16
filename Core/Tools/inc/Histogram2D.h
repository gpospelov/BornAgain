// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Histogram2D.h
//! @brief     Defines class Histogram2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HISTOGRAM2D_H
#define HISTOGRAM2D_H

#include "IHistogram.h"
class Histogram1D;

////! @class Histogram2D
////! @ingroup tools
////! @brief Two dimensional histogram

class Histogram2D : public IHistogram
{
public:
    //! Constructor for fix bin size histograms.
    //! @param nbinsx number of bins on X-axis
    //! @param xlow low edge of the first bin of X-axis
    //! @param xup upper edge of the last bin of X-axis
    //! @param nbinsy number of bins on Y axis
    //! @param ylow low edge of the first bin of Y-axis
    //! @param yup upper edge of the last bin of Y-axis
    Histogram2D(int nbinsx, double xlow, double xup, int nbinsy, double ylow, double yup);

    //! Constructor for variable bin size histograms.
    //! @param nbinsx number of bins on X-axis
    //! @param xbins Array of size nbins+1 containing low-edges for each
    //! bin and upper edge of last bin.
    //! @param nbinsy number of bins on Y-axis
    //! @param ybins Array of size nbins+1 containing low-edges for each
    //! bin and upper edge of last bin.
    Histogram2D(int nbinsx, const std::vector<double> &xbins, int nbinsy, const std::vector<double> &ybins);

    //! Constructor for 2D histogram with custom axes
    Histogram2D(const IAxis &axis_x, const IAxis &axis_y);

    //! Increment bin with abscissa x and ordinate y with a weight.
    int fill(double x, double y, double weight = 1.0);

    const IAxis *getXaxis() const;

    const IAxis *getYaxis() const;


//    //! Project a 2D histogram into 1D histogram along X.
//    Histogram1D *projectionX(ProjectionType = INTEGRAL);

//    //! Project a 2D histogram into 1D histogram along Y.
//    Histogram1D *projectionY(ProjectionType = INTEGRAL);

//    //! Project a 2D histogram into 1D histogram along X, the projection
//    //! is made from the channels along the Y axis at 'yvalue'.
//    Histogram1D *profileX(double yvalue);

//    //! Project a 2D histogram into 1D histogram along X, the projection
//    //! is made from the channels along the Y axis ranging from ymin to ymax.
//    Histogram1D *profileX(double ymin, double ymax, ProjectionType = INTEGRAL);

//    //! Project a 2D histogram into 1D histogram along X, the projection
//    //! is made from the channels along the Y axis at 'yvalue'.
//    Histogram1D *profileY(double yvalue);

//    //! Project a 2D histogram into 1D histogram along X, the projection
//    //! is made from the channels along the Y axis ranging from ymin to ymax.
//    Histogram1D *profileX(double ymin, double ymax, ProjectionType projectionType = INTEGRAL);

//    //! Create new intensity data by applying rectangular clip.
//    Histogram1D *createClipped(double xmin, double ymin, double xmax, double ymax);

//    //!
//    //! The function returns the corresponding global bin number which has its content
//    //! incremented by weight.
//    int fill(double x, double y, double weight);

//    PyObject *getArray(DataType dataType = INTENSITY) const;

//    //! Reset this object (intensities, masks, etc)
//    void reset();

};


//! Sets mask in rectangular area defined by (xmin, xmax, ymin, ymax) to the mask_value.
//! Mask values outisde this area  will remain unchanged.
//    void setRectangularMask(double xmin, double ymin, double xmax, double ymax, bool mask_value = true);

//! Sets mask in elliptic area defined by (xcenter, ycenter, rx, ry) to the mask_value.
//! Mask values outisde this area  will remain unchanged.
//    void setEllipticMask(double xcenter, double ycenter, double rx, double ry, bool mask_value = true);

//! Sets masks accross whole area to given value
//void setMask(bool mask_value);

#endif
