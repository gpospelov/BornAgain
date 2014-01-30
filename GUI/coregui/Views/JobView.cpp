#include "JobView.h"

#include "SimulationDataModel.h"
#include "rootcanvas.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH2D.h"
#include "TRandom.h"

#include <QHBoxLayout>
#include <QListWidget>

JobView::JobView(SimulationDataModel *p_simulation_data_model, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
//    , mp_canvas(0)
    , m_joblist(0)
    , mp_cached_histo(0)
{
    // initialize joblist
    updateJobList();

    // initialize canvas
//    mp_canvas = new RootCanvas(this);
    mp_canvas = new CustomCanvas(this);
    mp_canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

     // layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_joblist);
    mainLayout->addWidget(mp_canvas);
    setLayout(mainLayout);

    // signals and slots
    connect(m_joblist, SIGNAL(currentRowChanged(int)), this, SLOT(onSelectionChanged()));
}
void JobView::updateJobsAndGraphics()
{
    updateJobList();
    updateGraphics();
}

void JobView::updateJobList()
{
    if (!m_joblist) {
        m_joblist = new QListWidget(this);
        m_joblist->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
    m_joblist->clear();
    if (mp_simulation_data_model) {
        m_joblist->addItems(mp_simulation_data_model->getJobs().keys());
    }
    if (m_joblist->count()>0) {
        setJobSelection();
    }
}

#include <iostream>
void JobView::updateGraphics()
{
    static int ncalls=0;
//    if (mp_canvas) {
//        JobModel *p_current_job = getCurrentJobModel();
//        if (p_current_job==0) return;
//        mp_canvas->cd();
//        gPad->SetLogz();
//        mp_cached_histo = p_current_job->getHistogram();
//        mp_cached_histo->SetContour(99);
//        gStyle->SetPalette(1);
//        gStyle->SetOptStat(0);
//        mp_cached_histo->SetMinimum(1.);
//        //mp_cached_histo->Draw("CONTZ");
//        mp_cached_histo->Draw("COL Z");
//        mp_canvas->Update();
//        std::cout << "XXX update " << (ncalls++) << std::endl;
//    }
    if(mp_canvas) {
        JobModel *p_current_job = getCurrentJobModel();
        if (p_current_job==0) return;
        const OutputData<double> *data = p_current_job->getOutputData();
        if(data == 0) return;
        mp_canvas->Draw(data);

    }
}

void JobView::onSelectionChanged()
{
    if (m_joblist && m_joblist->count()>0 && m_joblist->currentItem()) {
        m_current_job = m_joblist->currentItem()->text();
    } else {
        m_current_job.clear();
    }
    updateGraphics();
}

JobModel *JobView::getCurrentJobModel() const
{
    if (m_joblist && m_joblist->count()>0 && !m_current_job.isEmpty()) {
        JobModel *result = mp_simulation_data_model->getJobs()[m_current_job];
        return result;
    }
    return 0;
}

void JobView::setJobSelection()
{
    if (!m_joblist || m_joblist->count()==0) {
        m_current_job.clear();
        return;
    }
    if (m_current_job.isEmpty() || m_joblist->findItems(m_current_job, Qt::MatchExactly).count()==0) {
        m_joblist->setCurrentRow(0);
        m_current_job = m_joblist->currentItem()->text();
        return;
    }
    m_joblist->setCurrentItem(m_joblist->findItems(m_current_job, Qt::MatchExactly).at(0));
}
