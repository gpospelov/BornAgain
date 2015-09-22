// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IHistogram.h
//! @brief     Defines class IHistogram.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IHISTOGRAM_H
#define IHISTOGRAM_H

#include "OutputData.h"
#include "CumulativeValue.h"

#ifdef BORNAGAIN_PYTHON
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

class Histogram1D;
class Histogram2D;

//! @class IHistogram
//! @ingroup tools
//! @brief Base class for 1D and 2D histograms holding values of double type

class IHistogram
{
public:

    enum DataType {INTEGRAL, AVERAGE, ERROR, NENTRIES};

    IHistogram();
    virtual ~IHistogram(){}

    IHistogram(const IAxis &axis_x);
    IHistogram(const IAxis &axis_x, const IAxis &axis_y);

    //! Returns number of histogram dimensions (1 or 2).
    virtual size_t getRank() const;

    //! Returns total number of histogram bins. For 2D histograms the result will be the product
    //! of bin numbers along X and Y axes.
    size_t getTotalNumberOfBins() const;

    //! returns x-axis
    const IAxis *getXaxis() const;

    //! returns y-axis for 2D histograms
    const IAxis *getYaxis() const;

    //! Returns x-axis min (lower edge of first bin).
    double getXmin() const;

    //! Returns x-axis max (upper edge of last bin).
    double getXmax() const;

    //! Returns number of bins on x-axis
    size_t getNbinsX() const;

    //! Returns y-axis min (lower edge of first bin) for 2D histograms.
    double getYmin() const;

    //! Returns y-axis max (upper edge of last bin) for 2D histograms.
    double getYmax() const;

    //! Returns number of bins on y-axis
    size_t getNbinsY() const;

    //! Returns global bin index for given axes indices. For 1D histogram the global bin
    //! index coinside with axis index.
    //! @param binx X-axis bin index
    //! @param biny Y-axis bin index
    //! @return The global bin index
    int getGlobalBin(int binx, int biny = 0) const;

    //! Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide
    //! with globalbin value
    int getXaxisIndex(size_t globalbin) const;


    //! Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide
    //! with globalbin value
    int getYaxisIndex(size_t globalbin) const;

    //! Returns the value on x-axis corresponding to the global bin index.
    //! @param binGlobalIndex The global bin index
    //! @return The center of axis's corresponding bin
    double getXaxisValue(size_t globalbin);

    //! Returns the value on y-axis corresponding to the global bin index (for 2D histograms).
    //! @param globalbin The global bin index
    //! @return The center of axis's corresponding bin
    double getYaxisValue(size_t globalbin);


    //! Returns content of the bin with given index. For 1D histograms bin index is related
    //! to x-axis. For 2D histograms bin index is global bin index.
    //! @param bin Bin index
    //! @return The content of the bin (which is normally the value accumulated by the bin)
    double getBinContent(int bin) const;

    //! Returns content of the bin of 2D histogram with given axes indices.
    //! @param binx X-axis bin index
    //! @param biny Y-axis bin index
    //! @return The content of the bin (which is normally the value accumulated by the bin)
    double getBinContent(int binx, int biny) const;

    //! Returns error of the bin with given index.
    double getBinError(int bin) const;

    //! Returns error of the bin of 2D histogram with given axes indices.
    double getBinError(int binx, int biny) const;

    //! Returns number of entries in the bin with given index.
    int getBinNumberOfEntries(int bin) const;

    //! Returns number of entries in the bin of 2D histogram with given axes indices.
    int getBinNumberOfEntries(int binx, int biny) const;


#ifdef BORNAGAIN_PYTHON
    PyObject *getArray() const;
#endif

    //! Reset histogram content (axes remains)
    void reset();

//    static Histogram1D *createHistogram1D(const OutputData<double> &source);
//    static Histogram2D *createHistogram2D(const OutputData<double> &source);

    void setDataType(DataType data_type);

protected:
    DataType m_data_type;

    void check_x_axis() const;
    void check_y_axis() const;
    void init_from_data(const OutputData<double> &source);

    OutputData<CumulativeValue> m_data;
};

#endif

