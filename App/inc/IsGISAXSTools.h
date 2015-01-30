// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/IsGISAXSTools.h
//! @brief     Defines class IsGISAXSTools.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXSTOOLS_H_
#define ISGISAXSTOOLS_H_

#include "OutputData.h"
#include "SafePointerVector.h"

#include <string>
#include "EigenCore.h"

class TH1;
class TH1D;
class TH2D;
class TLine;

//! Histogram management for IsGISAXS validation.

class IsGISAXSTools {
public:
    struct AxisStructure {
        size_t nbins;
        std::vector<double> xbins;
        std::string name;
    };

    //! Draw 2D histogram representing logarithm of OutputData (in new canvas)
    static void drawLogOutputData(
        const OutputData<double>& output,
        const std::string& canvas_name,
        const std::string& canvas_title,
        const std::string& draw_options,
        const std::string& histogram_title);

    //! Draw 4 2D histograms representing logarithm of polarized OutputData
    //! for different combinations of polarization (in new canvas)
    static void drawLogOutputDataPol(
        const OutputData<Eigen::Matrix2d>& output,
        const std::string& canvas_name,
        const std::string& canvas_title,
        const std::string& draw_options,
        const std::string& histogram_title);

    //! Draw 2D histogram representing OutputData (in new canvas)
    static void drawOutputData(
        const OutputData<double>& output,
        const std::string& canvas_name,
        const std::string& canvas_title,
        const std::string& draw_options,
        const std::string& histogram_title);

    //! Draw 2D histogram representing OutputData (in current gPad)
    static void drawOutputDataInPad(
        const OutputData<double>& output,
        const std::string& draw_options,
        const std::string& histogram_title);

    //! Draw 1D distribution over values stored in OutputData
    static void drawOutputDataDistribution1D(
        const OutputData<double>& output,
        const std::string& draw_options,
        const std::string& histogram_title = std::string());

    //! Draw 1D distribution over relative difference in two OutputData sets.
    static void drawOutputDataDifference1D(
        const OutputData<double>& left,
        const OutputData<double>& right,
        const std::string& draw_options,
        const std::string& histogram_title = std::string());

    //! Draw relative difference of two 2D OutputData sets.
    static void drawOutputDataRelativeDifference2D(
        const OutputData<double>& left,
        const OutputData<double>& right,
        const std::string& draw_options,
        const std::string& histogram_title = std::string());

    //! Draw relative difference of two 2D OutputData sets
    static void drawOutputDataChi2Difference2D(
        const OutputData<double>& left,
        const OutputData<double>& right,
        const std::string& draw_options,
        const std::string& histogram_title = std::string());

    //! Sets minimum of y-axis (for 1D histogram), or z-axis (2D histograms).
    static void setMinimum(double hist_min)
    { m_hist_min = hist_min; m_has_min = true; }

    //! Sets maximum of y-axis (for 1D histogram), or z-axis (2D histograms).
    static void setMaximum(double hist_max)
    { m_hist_max = hist_max; m_has_max = true; }

    //! Returns true if user has defined minimum
    static bool hasMinimum()  { return m_has_min; }

    //! Returns true if user has defined minimum
    static bool hasMaximum()  { return m_has_max; }

    //! Reset user defined min values for histograms, they will be calculated automatically
    static void resetMinimum() { m_hist_min = 0; m_has_min = false; }

    //! Reset user defined max values for histograms, they will be calculated automatically
    static void resetMaximum() { m_hist_max = 0; m_has_max = false; }

    //! Reset user defined min,max values for histograms
    static void resetMinimumAndMaximum() { resetMinimum(); resetMaximum(); }

    //! Export 2D output data in std::vectors (used for saving in ROOT tree).
    static void exportOutputDataInVectors2D(
        const OutputData<double>& input_data,
        std::vector<std::vector<double > >& v_data,
        std::vector<std::vector<double > >& v_axis0,
        std::vector<std::vector<double > >& v_axis1);

    //! Creates two-dimensional TH2D from OutputData.
    static TH2D *getOutputDataTH2D(
        const OutputData<double>& output,
        const std::string& histo_name);

    //! Creates one, two, three-dimensional histograms from OutputData.
    static TH1 *getOutputDataTH123D(
        const OutputData<double>& output,
        const std::string& histo_name);

    //! Creates TLine for displaying of one-dimensional data scan.
    static TLine *getOutputDataScanLine(const OutputData<double>& data);

    //! Creates TH1D for displaying of one-dimensional data scan.
    static TH1D *getOutputDataScanHist(
        const OutputData<double>& data,
        const std::string& hname=std::string("scan_hist"));

    //! Creates noisy data.
    static OutputData<double > *createNoisyData(
        const OutputData<double>& exact_data,
        double noise_factor = 0.1);
    static OutputData<double > *createDataWithGaussianNoise(
        const OutputData<double>& exact_data, double sigma);

    //! Draw standard IsGISAXS comparison canvas.
    static void drawOutputDataComparisonResults(
        const OutputData<double>& data,
        const OutputData<double>& reference,
        const std::string& name=std::string("no name"),
        const std::string& title=std::string("no title"),
        double hmin=1.,
        double hmax = -1.,
        double hdiff=0.0001 );

private:
    //! selects specific matrix elements from polarized output data and puts
    //! these in a non-polarized output data structure
    static void copyElementsWithPosition(
            const OutputData<Eigen::Matrix2d> &source,
            OutputData<double> &destination, int pos_x, int pos_y);
    //! lower bound of y-axis (for 1D histograms), or z-axis (for 2D histograms)
    static double m_hist_min;
    //! upper bound of y-axis (for 1D histograms), or z-axis (for 2D histograms)
    static double m_hist_max;
    //! user defined histogram minimum ?
    static bool m_has_min;
    //! user defined histogram maximum
    static bool m_has_max;
};

#endif /* ISGISAXSTOOLS_H_ */


