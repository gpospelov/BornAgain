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
#include <algorithm>

double IsGISAXSTools::m_hist_min = 0;
double IsGISAXSTools::m_hist_max = 0;
bool   IsGISAXSTools::m_has_min = false;
bool   IsGISAXSTools::m_has_max = false;


/* ************************************************************************* */
// draw 2D histogram representing logarithm of OutputData (in new canvas)
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

/* ************************************************************************* */
// draw 2D histogram representing OutputData (in new canvas)
/* ************************************************************************* */
void IsGISAXSTools::drawOutputData(const OutputData<double>& output,
        const std::string& canvas_name, const std::string& canvas_title,
        const std::string& draw_options, const std::string &histogram_title)
{
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), canvas_title.c_str(), 0, 0, 1024, 768);
    c1->cd();
    drawOutputDataInPad(output, draw_options, histogram_title);
}

/* ************************************************************************* */
// draw 2D histogram representing OutputData (in current gPad)
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataInPad(const OutputData<double>& output,
        const std::string& draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataInPad() -> Error! No canvas exists.");
    }

//    if (output.getDimension() != 2) return;

//    // creation of 2D histogram from calculated intensities
//    output.resetIndex();
//    const NamedVector<double> *p_y_axis = reinterpret_cast<const NamedVector<double>*>(output.getAxes()[0]);
//    const NamedVector<double> *p_z_axis = reinterpret_cast<const NamedVector<double>*>(output.getAxes()[1]);
//    std::string y_axis_name = p_y_axis->getName();
//    std::string z_axis_name = p_z_axis->getName();
//    size_t y_size = p_y_axis->getSize();
//    size_t z_size = p_z_axis->getSize();
//    double y_start = (*p_y_axis)[0]/Units::degree;
//    double y_end = (*p_y_axis)[y_size-1]/Units::degree;
//    double z_start = (*p_z_axis)[0]/Units::degree;
//    double z_end = (*p_z_axis)[z_size-1]/Units::degree;
//    std::string histo_name = histogram_title;
//    if (histo_name.empty()) {
//        histo_name = gPad->GetTitle();
//    }
//    TH2D p_hist2D("p_hist2D", histo_name.c_str(), y_size, y_start, y_end, z_size, z_start, z_end);
//    //p_hist2D->UseCurrentStyle();
//    p_hist2D.GetXaxis()->SetTitle(y_axis_name.c_str());
//    p_hist2D.GetYaxis()->SetTitle(z_axis_name.c_str());

//    while (output.hasNext())
//    {
//        size_t index_y = output.getCurrentIndexOfAxis(y_axis_name.c_str());
//        size_t index_z = output.getCurrentIndexOfAxis(z_axis_name.c_str());
//        //std::cout << "!!! " << index_y << " " << index_z << std::endl;
//        double x_value = (*p_y_axis)[index_y]/Units::degree;
//        double y_value = (*p_z_axis)[index_z]/Units::degree;
//        double z_value = output.next();
//        p_hist2D.Fill(x_value, y_value, z_value);
//    }
//    p_hist2D.SetContour(50);
//    p_hist2D.SetStats(0);
//    p_hist2D.GetYaxis()->SetTitleOffset(1.3);

//    gStyle->SetPalette(1);
//    gStyle->SetOptStat(0);
////    gPad->SetLogz();
//    gPad->SetRightMargin(0.115);
//    gPad->SetLeftMargin(0.115);
//    if( hasMinimum() ) p_hist2D.SetMinimum(m_hist_min);
//    if( hasMaximum() ) p_hist2D.SetMaximum(m_hist_max);

//    p_hist2D.DrawCopy(draw_options.c_str());
//    //delete p_output;

    TH2D *h2 = IsGISAXSTools::getOutputDataTH2D(output, "p_hist2D");
    h2->SetContour(99);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
//    gPad->SetRightMargin(0.115);
//    gPad->SetLeftMargin(0.115);
    if( hasMinimum() ) h2->SetMinimum(m_hist_min);
    if( hasMaximum() ) h2->SetMaximum(m_hist_max);
    h2->SetTitle(histogram_title.c_str());
    h2->DrawCopy(draw_options.c_str());
    delete h2;
}


/* ************************************************************************* */
// create TH2D from OutputData
/* ************************************************************************* */
TH2D *IsGISAXSTools::getOutputDataTH2D(const OutputData<double>& output, const std::string &histo_name)
{
    if (output.getDimension() != 2) {
        std::cout << "IsGISAXSTools::getOutputDataTH2D() -> Warning! Wrong number of dimensions " << std::endl;
        return 0;
    }

    // we assume variable bin size and prepare [nbins+1] array of low edges of each bin
    std::vector<double> histo_axises[2]; // arrays describing x and y histogram axis
    for(int i_axis=0; i_axis<2; ++i_axis) {
        const NamedVector<double> *axis = reinterpret_cast<const NamedVector<double>*>(output.getAxes()[i_axis]);
        double dx(0);
        for(size_t i_bin=0; i_bin<axis->getSize(); ++i_bin) {
            if(i_bin == 0) {
                dx = (*axis)[1]-(*axis)[0];
            } else {
                dx = (*axis)[i_bin] - (*axis)[i_bin-1];
            }
            histo_axises[i_axis].push_back( (*axis)[i_bin] - dx/2.);
        }
        histo_axises[i_axis].push_back((*axis)[axis->getSize()-1] + dx/2.); // right bin edge of last bin, so for 100 bins size of vector will be 101
    }

//    for(size_t i_axis=0; i_axis<2; ++i_axis) {
//        std::cout << "axis " << i_axis << " size:" << histo_axises[i_axis].size() << std::endl;
//        for(size_t i_bin=0; i_bin<histo_axises[i_axis].size(); ++i_bin) {
//            std::cout << histo_axises[i_axis][i_bin] << " ";
//        }
//        std::cout << std::endl;
//    }

    // creation of 2D histogram with variable bin size
    const NamedVector<double> *axis0 = reinterpret_cast<const NamedVector<double>*>(output.getAxes()[0]);
    const NamedVector<double> *axis1 = reinterpret_cast<const NamedVector<double>*>(output.getAxes()[1]);
    TH2D *h2 = new TH2D(histo_name.c_str(), histo_name.c_str(), axis0->getSize(), &histo_axises[0][0], axis1->getSize(), &histo_axises[1][0]);
    h2->GetXaxis()->SetTitle( axis0->getName().c_str() );
    h2->GetYaxis()->SetTitle( axis1->getName().c_str() );

    output.resetIndex();
    while (output.hasNext())
    {
        double x_value = output.getCurrentValueOfAxis<double>( axis0->getName().c_str() );
        double y_value = output.getCurrentValueOfAxis<double>( axis1->getName().c_str() );
        double z_value = output.next();
        h2->Fill(x_value, y_value, z_value);
    }
    h2->SetContour(50);
    h2->SetStats(0);
    h2->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    return h2;
}


/* ************************************************************************* */
// draw 1D distribution over values stored in OutputData
// binning of histogram is calculated on the fly
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataDistribution1D(const OutputData<double> &output, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDistribution1D() -> Error! No canvas exists.");
    }

    std::string histo_name = histogram_title;
    if (histo_name.empty()) {
        histo_name = gPad->GetTitle();
    }

    // creating histogram with automatic binning
    TH1::SetDefaultBufferSize(5000);
    TH1D h1_spect("h1_spect", histo_name.c_str(), 200, 1.0, -1.0); // xmin > xmax as a sign of automatic binning

    output.resetIndex();
    while (output.hasNext())
    {
        h1_spect.Fill( output.next() );
    }

    h1_spect.DrawCopy(draw_options.c_str());
}


/* ************************************************************************* */
// draw 1D distribution over relative difference in two OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataDifference1D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDifference1D() -> Error! No canvas exists.");
    }

    OutputData<double> *left_clone = left.clone();
    OutputData<double> *right_clone = right.clone();

    *left_clone -= *right_clone;
    *left_clone /= *right_clone;

    std::string histo_name = histogram_title;
    if (histo_name.empty()) {
        histo_name = gPad->GetTitle();
    }

    TH1D h1_spect("difference", histo_name.c_str(), 40, -20.0, 20.0);
    h1_spect.GetXaxis()->SetTitle("log10( (we-isgi)/isgi )");

    left_clone->resetIndex();
    while (left_clone->hasNext())
    {
        double x = left_clone->next();
        if(x!=0) {
            x = log10(fabs(x));
        } else {
            // lets put the cases then the difference is exactly 0 to underflow bin
            x = -21.;
        }
        h1_spect.Fill( x );
    }

    gPad->SetLogy();
    gPad->SetRightMargin(0.115);
    gPad->SetLeftMargin(0.115);
    h1_spect.SetStats(1);
    gStyle->SetOptStat(111111);
    if( hasMinimum() ) h1_spect.SetMinimum(m_hist_min);
    if( hasMaximum() ) h1_spect.SetMaximum(m_hist_max);

    h1_spect.DrawCopy(draw_options.c_str());
    delete left_clone;
    delete right_clone;
}


/* ************************************************************************* */
// draw relative difference of two 2D OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataRelativeDifference2D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDifference2D -> Error! No canvas exists.");
    }
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
// draw relative chi2 difference of two 2D OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataChi2Difference2D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDifference2D -> Error! No canvas exists.");
    }
    OutputData<double> *left_clone = left.clone();
    OutputData<double> *right_clone = right.clone();

    *left_clone -= *right_clone;
    OutputData<double> *tmp = left_clone->clone();

    *left_clone *= *tmp;
    left_clone->scaleAll(1./left_clone->totalSum());

    IsGISAXSTools::drawOutputDataInPad(*left_clone, draw_options, histogram_title);

    delete left_clone;
    delete right_clone;
    delete tmp;
}


/* ************************************************************************* */
// write output data (1D or 2D) in ASCII file
/* ************************************************************************* */
void IsGISAXSTools::writeOutputDataToFile(const OutputData<double>& output,
        const std::string &filename, int precision)
{
    std::ofstream file;
    file.open(filename.c_str(), std::ios::out);
    if( !file.is_open() ) {
        std::cout << "IsGISAXSTools::writeOutputDataToFile() -> Error. Can't open file '"+filename+"' for writing." << std::endl;
        return;
        //throw FileNotIsOpenException("IsGISAXSTools::writeOutputDataToFile() -> Error. Can't open file '"+filename+"' for writing.");
    }
    output.resetIndex();
    size_t row_length = output.getAxes()[1]->getSize();
    int counter = 1;
    while(output.hasNext()) {
        double z_value = output.next();
        file << std::scientific << std::setprecision(precision) << z_value << "    ";
        if(counter%row_length==0) {
            file << std::endl;
        }
        ++counter;
    }
    if ( file.bad() ) {
        throw FileIsBadException("IsGISAXSTools::writeOutputDataToFile() -> Error! File is bad, probably it is a directory.");
    }
    file.close();
    std::cout << "IsGISAXSTools::writeOutputDataToFile() -> Info. File '" << filename << "' successfully created." << std::endl;
}


/* ************************************************************************* */
// read data from ASCII file (2D assumed) and fill newly created OutputData with it
/* ************************************************************************* */
OutputData<double> *IsGISAXSTools::readOutputDataFromFile(const std::string &filename, int precision)
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
        // here we mimic different precision in numbers contained in string, if precision is say 6, than 7.2908527770e+03 -> 7.290853e+03
        if(precision > 0) {
            std::string newline;
            std::istringstream is0(sline.c_str());
            double number;
            while( is0 >> number ) {
                std::ostringstream os;
                os << std::scientific << std::setprecision(precision) << number;
                newline += os.str() + std::string("    ");
            }
            sline = newline;
        }

        double1d_t buff_1d;
        std::istringstream iss(sline);
        std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(), back_inserter(buff_1d));
        if( !buff_1d.size() ) LogicErrorException("IsGISAXSTools::readOutputDataFromFile() -> Error. Null size of vector");
        buff_2d.push_back(buff_1d);
    }
    if ( fin.bad() ) {
        throw FileIsBadException("IsGISAXSTools::readOutputDataFromFile() -> Error! File is bad after readline(), probably it is a directory.");
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


void IsGISAXSTools::exportOutputDataInVectors2D(const OutputData<double> &output_data
                                        , std::vector<std::vector<double > > &v_data
                                        , std::vector<std::vector<double > > &v_axis0
                                        , std::vector<std::vector<double > > &v_axis1)
{
    if (output_data.getDimension() != 2) return;

    output_data.resetIndex();
    const NamedVector<double> *p_axis0 = dynamic_cast<const NamedVector<double>*>(output_data.getAxes()[0]);
    const NamedVector<double> *p_axis1 = dynamic_cast<const NamedVector<double>*>(output_data.getAxes()[1]);
    std::string axis0_name = p_axis0->getName();
    std::string axis1_name = p_axis1->getName();
    size_t axis0_size = p_axis0->getSize();
    size_t axis1_size = p_axis1->getSize();

    v_data.clear();
    v_axis0.clear();
    v_axis1.clear();

    v_data.resize(axis0_size);
    v_axis0.resize(axis0_size);
    v_axis1.resize(axis0_size);

    for(size_t i=0; i<axis0_size; ++i) {
        v_data[i].resize(axis1_size,0.0);
        v_axis0[i].resize(axis1_size,0.0);
        v_axis1[i].resize(axis1_size,0.0);
    }

    while (output_data.hasNext())
    {
        size_t axis0_index = output_data.getCurrentIndexOfAxis(axis0_name.c_str());
        size_t axis1_index = output_data.getCurrentIndexOfAxis(axis1_name.c_str());
        double axis0_value = (*p_axis0)[axis0_index];
        double axis1_value = (*p_axis1)[axis1_index];
        double intensity = output_data.next();

        v_data[axis0_index][axis1_index] = intensity;
        v_axis0[axis0_index][axis1_index] = axis0_value;
        v_axis1[axis0_index][axis1_index] = axis1_value;
    }

}


