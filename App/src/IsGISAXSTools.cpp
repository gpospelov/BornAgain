#include "IsGISAXSTools.h"
#include "Units.h"
#include "Exceptions.h"

#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <cmath>

double IsGISAXSTools::m_hist_min = 0;
double IsGISAXSTools::m_hist_max = 0;
bool   IsGISAXSTools::m_has_min = false;
bool   IsGISAXSTools::m_has_max = false;


/* ************************************************************************* */
// draw 2D histogram representing OutputData (in new canvas)
/* ************************************************************************* */
void IsGISAXSTools::drawLogOutputData(const OutputData<double>& output,
        const std::string& canvas_name, const std::string& canvas_title,
        const std::string& draw_options, const std::string &histogram_title)
{
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), canvas_title.c_str(), 0, 0, 1024, 768);
    IsGISAXSTools::setMinimum(1.);
    c1->cd();
    gPad->SetLogz();
    drawOutputDataInPad(output, draw_options, histogram_title);
}


// draw 2D histogram representing OutputData (in current gPad)
void IsGISAXSTools::drawOutputDataInPad(const OutputData<double>& output,
        const std::string& draw_options, const std::string &histogram_title)
{
    OutputData<double> *p_output = output.clone();
    if (p_output->getDimension() != 2) return;
    // creation of 2D histogram from calculated intensities

    p_output->resetIndex();
    NamedVector<double> *p_y_axis = dynamic_cast<NamedVector<double>*>(p_output->getAxes()[0]);
    NamedVector<double> *p_z_axis = dynamic_cast<NamedVector<double>*>(p_output->getAxes()[1]);
    std::string y_axis_name = p_y_axis->getName();
    std::string z_axis_name = p_z_axis->getName();
    size_t y_size = p_y_axis->getSize();
    size_t z_size = p_z_axis->getSize();
    double y_start = (*p_y_axis)[0]/Units::degree;
    double y_end = (*p_y_axis)[y_size-1]/Units::degree;
    double z_start = (*p_z_axis)[0]/Units::degree;
    double z_end = (*p_z_axis)[z_size-1]/Units::degree;
    std::string histo_name = histogram_title;
    if (histo_name.empty()) {
        histo_name = gPad->GetTitle();
    }
    TH2D p_hist2D("p_hist2D", histo_name.c_str(), y_size, y_start, y_end, z_size, z_start, z_end);
    //p_hist2D->UseCurrentStyle();
    p_hist2D.GetXaxis()->SetTitle(y_axis_name.c_str());
    p_hist2D.GetYaxis()->SetTitle(z_axis_name.c_str());

    while (p_output->hasNext())
    {
        size_t index_y = p_output->getCurrentIndexOfAxis(y_axis_name.c_str());
        size_t index_z = p_output->getCurrentIndexOfAxis(z_axis_name.c_str());
        double x_value = (*p_y_axis)[index_y]/Units::degree;
        double y_value = (*p_z_axis)[index_z]/Units::degree;
        double z_value = p_output->next();
        p_hist2D.Fill(x_value, y_value, z_value);
    }
    p_hist2D.SetContour(50);
    p_hist2D.SetStats(0);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
//    gPad->SetLogz();
    gPad->SetRightMargin(0.12);
    if( hasMinimum() ) p_hist2D.SetMinimum(m_hist_min);
    if( hasMaximum() ) p_hist2D.SetMaximum(m_hist_max);

    p_hist2D.DrawCopy(draw_options.c_str());
    delete p_output;
}


/* ************************************************************************* */
// draw 1D distribution over values stored in OutputData
// binning of histogram is calculated on the fly
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataDistribution1D(const OutputData<double> &output, const std::string &draw_options, const std::string &histogram_title)
{
    OutputData<double> *output_clone = output.clone();

    std::string histo_name = histogram_title;
    if (histo_name.empty()) {
        histo_name = gPad->GetTitle();
    }

    // creating histogram with automatic binning
    TH1::SetDefaultBufferSize(5000);
    TH1D h1_spect("h1_spect", histo_name.c_str(), 200, 1.0, -1.0); // xmin > xmax as a sign of automatic binning

    output_clone->resetIndex();
    while (output_clone->hasNext())
    {
        h1_spect.Fill( output_clone->next() );
    }

    h1_spect.DrawCopy(draw_options.c_str());
    delete output_clone;
}


/* ************************************************************************* */
// draw 1D distribution over relative difference in two OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataDifference1D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    OutputData<double> *left_clone = left.clone();
    OutputData<double> *right_clone = right.clone();

    *left_clone -= *right_clone;
    *left_clone /= *right_clone;
    left_clone->scaleAll(100.0);

    std::string histo_name = histogram_title;
    if (histo_name.empty()) {
        histo_name = gPad->GetTitle();
    }

    TH1D h1_spect("difference", histo_name.c_str(), 40, -20.0, 20.0);
    h1_spect.GetXaxis()->SetTitle("log10( 100*(we-isgi)/isgi )");

    left_clone->resetIndex();
    while (left_clone->hasNext())
    {
        double x = left_clone->next();
        if(x!=0) {
            x = log10(fabs(x));
            h1_spect.Fill( x );
        } else {
            // lets put the cases then the difference is exactly 0 to underflow bin
            x = -21.;
        }
    }

    gPad->SetLogy();
    h1_spect.SetStats(1);
    gStyle->SetOptStat(111111);
    h1_spect.DrawCopy(draw_options.c_str());
    delete left_clone;
    delete right_clone;
}


/* ************************************************************************* */
// draw relative difference of two 2D OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataDifference2D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    OutputData<double> *left_clone = left.clone();
    OutputData<double> *right_clone = right.clone();

    *left_clone -= *right_clone;
    *left_clone /= *right_clone;
    left_clone->scaleAll(100.0);

    IsGISAXSTools::drawOutputDataInPad(*left_clone, draw_options, histogram_title);

    delete left_clone;
    delete right_clone;
}


/* ************************************************************************* */
// write output data (1D or 2D) in ASCII file
/* ************************************************************************* */
void IsGISAXSTools::writeOutputDataToFile(const OutputData<double>& output,
        const std::string &filename)
{
    OutputData<double> *p_output = output.clone();
    std::ofstream file;
    file.open(filename.c_str(), std::ios::out);
    if( !file.is_open() ) {
        throw FileNotIsOpenException("IsGISAXSTools::writeOutputDataToFile() -> Error. Can't open file '"+filename+"' for writing.");
    }
    p_output->resetIndex();
    size_t row_length = p_output->getAxes()[0]->getSize();
    int counter = 1;
    while(p_output->hasNext()) {
        double z_value = p_output->next();
        file << std::setprecision(20) << z_value << "    ";
        if(counter%row_length==0) {
            file << std::endl;
        }
        ++counter;
    }
    file.close();
    std::cout << "IsGISAXSTools::writeOutputDataToFile() -> Info. File '" << filename << "' successfully created." << std::endl;
    delete p_output;
}


/* ************************************************************************* */
// read data from ASCII file (2D assumed) and fill newly created OutputData with it
/* ************************************************************************* */
OutputData<double> *IsGISAXSTools::readOutputDataFromFile(const std::string &filename)
{
    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("IsGISAXSTools::writeOutputDataToFile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    typedef std::vector<double > double1d_t;
    typedef std::vector<double1d_t > double2d_t;
    std::string sline;
    double2d_t buff_2d;
    // reading file line by line, every line is parsed into vector of double, so at the end we have buffer_2d of doubles
    while( std::getline(fin, sline))
    {
        double1d_t buff_1d;
        std::istringstream iss(sline);
        std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(), back_inserter(buff_1d));
        if( !buff_1d.size() ) LogicErrorException("IsGISAXSTools::readOutputDataFromFile() -> Error. Null size of vector");
        buff_2d.push_back(buff_1d);
    }
    fin.close();

    // creating new OutputData and filling it with values from buffer_2d
    int y_size = buff_2d.size();
    int x_size = buff_2d.size() ? buff_2d[0].size() : 0;
    OutputData<double> *output = new OutputData<double>;
    output->addAxis(std::string("x-axis"), 0.0, double(x_size), x_size);
    output->addAxis(std::string("y-axis"), 0.0, double(y_size), y_size);
    output->setAllTo(0.0);

    output->resetIndex();
    while (output->hasNext())
    {
        size_t index_x = output->getCurrentIndexOfAxis("x-axis");
        size_t index_y = output->getCurrentIndexOfAxis("y-axis");
        //output->next() = buff_2d[index_y][index_x];
        output->next() = buff_2d[index_x][index_y]; // strange
    }

    return output;
}


