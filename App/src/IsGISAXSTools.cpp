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


//! draw 2D histogram representing OutputData (in new canvas)
void IsGISAXSTools::drawLogOutputData(const OutputData<double>& output,
        const std::string& canvas_name, const std::string& canvas_title,
        const std::string& draw_options, const std::string &histogram_title)
{
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), canvas_title.c_str(), 0, 0, 1024, 768);
    c1->cd();
    drawLogOutputDataInCurrentPad(output, draw_options, histogram_title);
}


//! draw 2D histogram representing OutputData (in current gPad)
void IsGISAXSTools::drawLogOutputDataInCurrentPad(const OutputData<double>& output,
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
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    gPad->SetLogz();
    gPad->SetRightMargin(0.12);
    p_hist2D.SetMinimum(1.0e13);
//  p_hist2D.SetMaximum(10.0);
    p_hist2D.DrawCopy(draw_options.c_str());
    delete p_output;
}


//! write output data (1D or 2D) in ASCII file
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


//! read data from ASCII file (2D assumed) and fill newly created OutputData with it
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


