#include "JobModel.h"

#include "Simulation.h"
#include "TH2D.h"
#include "TStyle.h"

#include <QDateTime>

JobModel::JobModel(Simulation *p_simulation)
    : m_name("")
    , mp_simulation(p_simulation)
    , mp_job_watcher(0)
    , m_is_finished(false)
    , mp_cached_histogram(0)
{
    m_name = getJobTimeStamp();
    mp_job_watcher = new QFutureWatcher<void>;
    connect(mp_job_watcher, SIGNAL(finished()), this, SLOT(onJobFinished()));
}

JobModel::~JobModel()
{
    delete mp_simulation;
    delete mp_job_watcher;
    delete mp_cached_histogram;
}

void JobModel::run()
{
    if (!m_is_finished) {
        mp_simulation->runSimulation();
    }
}

TH2D *JobModel::getHistogram()
{
    if (!m_is_finished) {
        return 0;
    }
    if (mp_cached_histogram) {
        return mp_cached_histogram;
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
    mp_cached_histogram = new TH2D(name_array.data(), name_array.data(),
                           (int)axis_sizes[0], &binvectors[0][0],
                           (int)axis_sizes[1], &binvectors[1][0]);
    mp_cached_histogram->GetXaxis()->SetTitle( axis_names[0].c_str() );
    mp_cached_histogram->GetYaxis()->SetTitle( axis_names[1].c_str() );

    OutputData<double>::const_iterator it = output->begin();
    while (it != output->end())
    {
        double x = output->getValueOfAxis( axis_names[0].c_str(), it.getIndex() );
        double y = output->getValueOfAxis( axis_names[1].c_str(), it.getIndex() );
        double value = *it++;
        mp_cached_histogram->Fill(x, y, value);
    }
    mp_cached_histogram->SetContour(50);
    mp_cached_histogram->SetStats(0);
    mp_cached_histogram->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    return mp_cached_histogram;
}

void JobModel::onJobFinished()
{
    m_is_finished = true;
}

QString JobModel::getJobTimeStamp() const
{
    QString result = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh:mm:ss-zzz");
    return result;
}
