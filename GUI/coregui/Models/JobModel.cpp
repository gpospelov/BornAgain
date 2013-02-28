#include "JobModel.h"

#include "Simulation.h"
#include "TH2D.h"
#include "TStyle.h"

#include <QDateTime>

JobModel::JobModel(Simulation *p_simulation)
    : m_name("")
    , mp_simulation(p_simulation)
    , m_isFinished(false)
{
    m_name = getJobTimeStamp();
}

JobModel::~JobModel()
{
    delete mp_simulation;
}

TH2D *JobModel::getHistogram()
{
    if (!m_isFinished) {
        return 0;
    }
    const OutputData<double> *output = mp_simulation->getOutputData();
    if (output->getNdimensions() !=2) {
        return 0;
    }
    std::vector<size_t> axis_sizes;
    std::vector<std::string> axis_names;
    std::vector<std::vector<double> > binvectors;

    // we assume variable bin size and prepare [nbins+1] array of left edges of each bin plus right edge of the last bin
    for(size_t i_axis=0; i_axis<output->getNdimensions(); ++i_axis) {
        const IAxis *axis = output->getAxis(i_axis);
        if( !axis ) return 0;
        double dx(0);
        axis_sizes.push_back(axis->getSize());
        axis_names.push_back(axis->getName());
        std::vector<double> bins;
        if( axis->getSize() == 0) {
            return 0;
        } else if( axis->getSize() == 1 ) {
            // only one bin, let's invent fake bin size
            dx = 0.1*(*axis)[0];
            bins.push_back((*axis)[0]-dx/2.);
            bins.push_back((*axis)[0]+dx/2.);
        }else {
            for(size_t i_bin=0; i_bin<axis->getSize(); ++i_bin) {
                if(i_bin == 0) {
                    dx = (*axis)[1]-(*axis)[0];
                } else {
                    dx = (*axis)[i_bin] - (*axis)[i_bin-1];
                }
                bins.push_back( (*axis)[i_bin] - dx/2.);
            }
        bins.push_back((*axis)[axis->getSize()-1] + dx/2.); // right bin edge of last bin, so for 100 bins size of vector will be 101
        binvectors.push_back(bins);
        }
    }
    QByteArray name_array = m_name.toLocal8Bit();
    TH2D *hist2 = new TH2D(name_array.data(), name_array.data(),
                           (int)axis_sizes[0], &binvectors[0][0],
                           (int)axis_sizes[1], &binvectors[1][0]);
    hist2->GetXaxis()->SetTitle( axis_names[0].c_str() );
    hist2->GetYaxis()->SetTitle( axis_names[1].c_str() );

    OutputData<double>::const_iterator it = output->begin();
    while (it != output->end())
    {
        double x = output->getValueOfAxis( axis_names[0].c_str(), it.getIndex() );
        double y = output->getValueOfAxis( axis_names[1].c_str(), it.getIndex() );
        double value = *it++;
        hist2->Fill(x, y, value);
    }
    hist2->SetContour(50);
    hist2->SetStats(0);
    hist2->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    return hist2;
}

void JobModel::run()
{
    mp_simulation->runSimulation();
    m_isFinished = true;
}

QString JobModel::getJobTimeStamp() const
{
    QString result = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh:mm:ss-zzz");
    return result;
}
