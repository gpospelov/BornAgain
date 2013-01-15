#ifndef ISGISAXSTOOLS_H_
#define ISGISAXSTOOLS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IsGISAXSTools.h
//! @brief  Definition of functions and classes for IsGISAXS validation
//! @author herck
//! @date   19.06.2012
#include "OutputData.h"

#include <string>

class TH1;
class TH1D;
class TH2D;
class TLine;

//- -------------------------------------------------------------------
//! @class IsGISAXSTools
//! @brief Definition of functions and classes for IsGISAXS validation
//- -------------------------------------------------------------------
class IsGISAXSTools {
public:
    struct AxisStructure {
        size_t nbins;
        std::vector<double> xbins;
        std::string name;
    };

    //! draw 2D histogram representing logarithm of OutputData (in new canvas)
    static void drawLogOutputData(const OutputData<double> &output, const std::string &canvas_name,
            const std::string &canvas_title, const std::string &draw_options,
            const std::string &histogram_title);

    //! draw 2D histogram representing OutputData (in new canvas)
    static void drawOutputData(const OutputData<double> &output, const std::string &canvas_name,
            const std::string &canvas_title, const std::string &draw_options,
            const std::string &histogram_title);

    //! draw 2D histogram representing OutputData (in current gPad)
    static void drawOutputDataInPad(const OutputData<double> &output, const std::string &draw_options, const std::string &histogram_title);

    //! draw 1D distribution over values stored in OutputData
    static void drawOutputDataDistribution1D(const OutputData<double> &output, const std::string &draw_options, const std::string &histogram_title = std::string());

    //! draw 1D distribution over relative difference in two OutputData sets
    static void drawOutputDataDifference1D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title = std::string());

    //! draw relative difference of two 2D OutputData sets
    static void drawOutputDataRelativeDifference2D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title = std::string());

    //! draw relative difference of two 2D OutputData sets
    static void drawOutputDataChi2Difference2D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title = std::string());

//    // write output data (1D or 2D) in ASCII file
//    static void writeOutputDataToFile(const OutputData<double> &output, const std::string &filename, int precision=10);

//    // read data from ASCII file (2D assumed) and fill newly created OutputData with it
//    static OutputData<double> *readOutputDataFromFile(const std::string &filename, int precision=6);

    //! set minimum and maximum values of y-axis (for 1D histogram), or z-axis (for 2D histograms)
    static void setMinimum(double hist_min) { m_hist_min = hist_min; m_has_min = true; }

    //! set minimum and maximum values of y-axis (for 1D histogram), or z-axis (for 2D histograms)
    static void setMaximum(double hist_max) { m_hist_max = hist_max; m_has_max = true; }

    //! return true if user has defined minimum
    static bool hasMinimum()  { return m_has_min; }

    //! return true if user has defined minimum
    static bool hasMaximum()  { return m_has_max; }

    //! reset user defined min values for histograms, they will be calculated automatically
    static void resetMinimum() { m_hist_min = 0; m_has_min = false; }

    //! reset user defined max values for histograms, they will be calculated automatically
    static void resetMaximum() { m_hist_max = 0; m_has_max = false; }

    //! reset user defined min,max values for histograms
    static void resetMinimumAndMaximum() { resetMinimum(); resetMaximum(); }

    //! export 2D output data in std::vectors (used for saving in ROOT tree)
    static void exportOutputDataInVectors2D(const OutputData<double> &output_data
                                            , std::vector<std::vector<double > > &v_data
                                            , std::vector<std::vector<double > > &v_axis0
                                            , std::vector<std::vector<double > > &v_axis1);

    //! create two-dimensional TH2D from OutputData
    static TH2D *getOutputDataTH2D(const OutputData<double>& output, const std::string &histo_name);

    //! create one, two, three-dimensional histograms from OutputData
    static TH1 *getOutputDataTH123D(const OutputData<double>& output, const std::string &histo_name);

    //! Create TLine for displaying of one-dimensional data scan
    static TLine *getOutputDataScanLine(const OutputData<double> &data);

    //! Create TH1D for displaying of one-dimensional data scan
    static TH1D *getOutputDataScanHist(const OutputData<double> &data, const std::string &hname=std::string("scan_hist"));

    //! create noisy data
    static OutputData<double > *createNoisyData(const OutputData<double> &exact_data, double noise_factor = 0.1);
    static OutputData<double > *createDataWithGaussianNoise(const OutputData<double> &exact_data, double sigma);

private:
    static double m_hist_min; // minimum value of y-axis (for 1D histograms), or z-axis (for 2D histograms)
    static double m_hist_max; // maximum value of y-axis (for 1D histograms), or z-axis (for 2D histograms)
    static bool m_has_min;    // if user defined histogram minimum
    static bool m_has_max;    // if user defined histogram maximum
};


///* namespace IsGISAXS Tools */

#endif /* ISGISAXSTOOLS_H_ */
