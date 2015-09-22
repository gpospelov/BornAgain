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
#include "Types.h"
class Histogram1D;

#ifdef BORNAGAIN_PYTHON
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

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

    //! Constructor for 2D histograms from basic OutputData object
    Histogram2D(const OutputData<double> &data);

    size_t getRank() const { return 2;}

    //! Increment bin with abscissa x and ordinate y with a weight.
    int fill(double x, double y, double weight = 1.0);


    //! Project a 2D histogram into 1D histogram along X. The projection is made
    //! from all bins along y-axis.
    Histogram1D *projectionX();

    //! Project a 2D histogram into 1D histogram along X. The projection is made
    //! from the y-bin closest to given ordinate yvalue.
    //! @param yvalue the value on y-axis at which projection is taken
    Histogram1D *projectionX(double yvalue);

    //! Project a 2D histogram into 1D histogram along X. The projection is made from
    //! all y-bins corresponding to ordinate between ylow and yup.
    //! @param ylow lower edje on y-axis
    //! @param yup upper edje on y-axis
    Histogram1D *projectionX(double ylow, double yup);


    //! Project a 2D histogram into 1D histogram along Y. The projection is made
    //! from all bins along x-axis.
    Histogram1D *projectionY();

    //! Project a 2D histogram into 1D histogram along Y. The projection is made
    //! from the x-bin closest to given abscissa xvalue.
    //! @param xvalue the value on x-axis at which projection is taken
    Histogram1D *projectionY(double xvalue);

    //! Project a 2D histogram into 1D histogram along Y. The projection is made from
    //! all x-bins corresponding to abscissa between xlow and xup.
    //! @param xlow lower edje on x-axis
    //! @param xup upper edje on x-axis
    Histogram1D *projectionY(double xlow, double xup);


    //! Create new histogram by applying rectangular clip.
    Histogram2D *crop(double xmin, double ymin, double xmax, double ymax);


//    vdouble2d_t getData() const;



//    //!
//    //! The function returns the corresponding global bin number which has its content
//    //! incremented by weight.
//    int fill(double x, double y, double weight);

//    PyObject *getArray(DataType dataType = INTENSITY) const;

//    //! Reset this object (intensities, masks, etc)
//    void reset();

protected:
    //! Creates projection along X. The projections is made by collecting the data in the range
    //! between [ybinlow, ybinup].
    Histogram1D *create_projectionX(int ybinlow, int ybinup);

    //! Creates projection along Y. The projections is made by collecting the data in the range
    //! between [xbinlow, xbinup].
    Histogram1D *create_projectionY(int xbinlow, int xbinup);

};


//! Sets mask in rectangular area defined by (xmin, xmax, ymin, ymax) to the mask_value.
//! Mask values outisde this area  will remain unchanged.
//    void setRectangularMask(double xmin, double ymin, double xmax, double ymax, bool mask_value = true);

//! Sets mask in elliptic area defined by (xcenter, ycenter, rx, ry) to the mask_value.
//! Mask values outisde this area  will remain unchanged.
//    void setEllipticMask(double xcenter, double ycenter, double rx, double ry, bool mask_value = true);

//! Sets masks accross whole area to given value
//void setMask(bool mask_value);


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


#endif
