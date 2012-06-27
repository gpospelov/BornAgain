#include "IsGISAXSTools.h"
#include "Units.h"

#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"

#include <fstream>

void IsGISAXSTools::drawLogOutputData(const OutputData<double>& output,
        const std::string& canvas_name, const std::string& canvas_title,
        const std::string& draw_options, const std::string &histogram_title)
{
    OutputData<double> *p_output = output.clone();
    if (p_output->getDimension() != 2) return;
    // creation of 2D histogram from calculated intensities
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), canvas_title.c_str(), 0, 0, 1024, 768);
    (void)c1;

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
        histo_name = canvas_title;
    }
    TH2D *p_hist2D = new TH2D("p_hist2D", histo_name.c_str(), y_size, y_start, y_end, z_size, z_start, z_end);
    //p_hist2D->UseCurrentStyle();
    p_hist2D->GetXaxis()->SetTitle(y_axis_name.c_str());
    p_hist2D->GetYaxis()->SetTitle(z_axis_name.c_str());

    while (p_output->hasNext())
    {
        size_t index_y = p_output->getCurrentIndexOfAxis(y_axis_name.c_str());
        size_t index_z = p_output->getCurrentIndexOfAxis(z_axis_name.c_str());
        double x_value = (*p_y_axis)[index_y]/Units::degree;
        double y_value = (*p_z_axis)[index_z]/Units::degree;
        double z_value = p_output->next();
        p_hist2D->Fill(x_value, y_value, z_value);
    }
    p_hist2D->SetContour(50);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    gPad->SetLogz();
    gPad->SetRightMargin(0.12);
    p_hist2D->SetMinimum(1.0);
    p_hist2D->Draw(draw_options.c_str());
    delete p_output;
}

void IsGISAXSTools::writeOutputDataToFile(const OutputData<double>& output,
        const std::string &filename)
{
    OutputData<double> *p_output = output.clone();
    std::ofstream file;
    file.open(filename.c_str(), std::ios::out);
    p_output->resetIndex();
    size_t row_length = p_output->getAxes()[0]->getSize();
    int counter = 1;
    while(p_output->hasNext()) {
        double z_value = p_output->next();
        file << z_value << "    ";
        if(counter%row_length==0) {
            file << std::endl;
        }
        ++counter;
    }
    delete p_output;
}
